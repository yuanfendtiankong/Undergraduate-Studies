from datetime import datetime
from socket import *
import time
import socket
import threading
import random

BUF_LEN = 1024

def client_data(clientSocket,data):
    powerOffThreshold = 0  #断电阈值
    fan_state = 0
    time_correct = 0
    relay_main = 1
    relay_trans = 1
    parts = data.split(',')
    

    
    client_time = int(parts[0].split(':')[1])  # 从数据中获取时间戳
    C_TIME = client_time
    client_time = datetime.fromtimestamp(client_time)
    client_time = client_time.strftime('%Y-%m-%d %H:%M:%S')
    
    server_time = int(time.time())
    S_TIME = server_time + random.randint(0,3)
    #server_time = server_time + server_time % 3 #测试时间错误
    server_time = datetime.fromtimestamp(S_TIME)
    server_time = server_time.strftime('%Y-%m-%d %H:%M:%S') 
       
    methane = int(parts[1].split(':')[1])
    temperature = int(parts[2].split(':')[1])
    oxygen = int(parts[3].split(':')[1])
    fan = int(parts[4].split(':')[1])
    powerFeedbackSensor = int(parts[5].split(':')[1])
    
    
    # 输出变量的值、

    print(f'下位机时间: {client_time}')
    print(f'上位机时间: {server_time}')
    print(f'甲烷浓度: {methane}')
    print(f'温度: {temperature}')
    print(f'氧气浓度: {oxygen}')
    
    # 逻辑处理
    if fan == 3 or fan == 2:
        print('主风扇状态: 开启')
    else:
        print('主风扇状态: 关闭')
    if fan == 3 or fan == 1:
        print('副风扇状态: 开启')
    else:
        print('副风扇状态: 关闭')   
        
    if S_TIME - C_TIME >= 2 :
        print('主机与用户机时间差超过两秒!!!立即校正时间与主机一致!!!')
        time_correct = 1
    
    if fan == 0:
        print('警告! 检测到主风扇与副风扇都已停止工作!请下位机立刻开启风机')
        fan = random.randint(1,2)
        # 这里可以添加发送控制命令到下位机的代码
        
    if methane > 10000:  # 甲烷浓度超过预警阈值
        if methane < 20000:
            print('警告!!!检测甲烷浓度超标!!!')
        else:
            relay_main = 0
            relay_trans = 0
            powerOffThreshold = 1
            print('检测甲烷浓度已经达到断电阈值，下位机的继电器工作应立即采取措施')
 
            
        # 这里可以添加发送断电指令到下位机的代码
    if temperature > 40 or oxygen < 50:  # 温度过高或氧气浓度过低
        print("警告：温度过高或氧气浓度过低！")
        if fan != 3:
            print('下位机需要将两个风机都开启')
            fan = 3
    if temperature <= 40 and oxygen >50 and fan == 3:
        fan_state = 2
        fan = 2
        print('温度和氧气浓度适宜,请关闭备用风机，保持主风机的开启')
        # 这里可以添加发送风机开启指令到下位机的代码
    
    sen = ''
    sen += str(fan) + '#'
    sen += str(time_correct) + '#'
    sen += str(relay_main) + '#'
    sen += str(relay_trans) + '#'
    sen += str(fan_state) + '#'

    
    clientSocket.send(sen.encode()); 
    print()
    print()
    print()
    
    data = clientSocket.recv(BUF_LEN).decode()
    message = data.split('#')
    back_ralay_main = message[0]
    back_ralay_trans = message[1]
    #print(back_ralay_main)
    #print(back_ralay_trans)
    if back_ralay_main == '0' and back_ralay_trans == '0':
            print('下位机已经接受命令,并成功执行')
    else:
        if back_ralay_main == '1':
            print('警告!!!煤矿开采设备继电器未能成功断电,立即采取措施!!!')
        if back_ralay_trans == '1': 
            print('警告!!!传输设备继电器未能成功断电,立即采取措施!!!')
    
    
    return 

# 创建socket对象
server_socket = socket.socket()
host = '127.0.0.1'  # 服务器IP地址，根据实际情况更改
port = 12345  # 服务器端口
server_socket.bind((host, port))


server_socket.listen(5)
print("服务器启动，等待连接...")

while True:
    client, addr = server_socket.accept()
    print("连接地址:", str(addr))
    
    while True:  # 通过增加这个无限循环，服务器可以持续接收数据
        print('--------------------------------分割线-------------------------------\n')
        data = client.recv(BUF_LEN).decode()
        if not data:
            break  # 如果客户端关闭连接，跳出内层循环
        client_data(client,data)

    print("客户端断开连接")
    client.close()

