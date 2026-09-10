from socket import *
import time
import threading
import random

IP = '0.0.0.0'
PORT = 50000
BUF_LEN = 1024

L1 = ['O2', 'CH4', 'temp', 'main_ventilator', 'vice_ventilator', 'time']

main_ventilator = 1
vice_ventilator = 0
relay_mian = 1
relay_trans = 1

alarm1 = 0
alarm2 = 0
alarm3 = 0
alarm4 = 0
last_time = 0


def sever_working(dataSocket):

    global last_time
    global main_ventilator
    global vice_ventilator
    global relay_mian
    global relay_trans
    global alarm1
    global alarm2
    global alarm3
    global alarm4

    main_ventilator = 1
    vice_ventilator = 0
    relay_mian = 1
    relay_trans = 1

    alarm1 = 0
    alarm2 = 0
    alarm3 = 0
    alarm4 = 0

    rec = dataSocket.recv(BUF_LEN)
    data = rec.decode()
    print(f'已获取下位机信息, ', end='获取时间 : ')
    print(time.strftime("%Y-%m-%d-%H-%M-%S", time.localtime()))

    l_t = data.split('#')
    lis = [int(i) for i in l_t]
    dic = dict(zip(L1, lis))

    print('氧气浓度:', end=' ')
    print(dic['O2'])
    print(f'甲烷浓度:', end=' ')
    print(dic['CH4'])
    print(f'温度:', end=' ')
    print(dic['temp'])

    if dic['main_ventilator'] == 1:
        print('主风扇状态: 开启')
    else:
        print('主风扇状态: 关闭')

    if dic['vice_ventilator'] == 1:
        print('副风扇状态: 开启')
    else:
        print('副风扇状态: 关闭')

    if last_time == 0:
        alarm1 = 1
        print('主机与用户机时间差超过两秒!!!立即校正时间与主机一致!!!')
        last_time = int(time.time())
    else:
        timestamp = int(time.time())
        print(f'与上一次获取信息时间间隔:{timestamp-last_time}秒')
        last_time = timestamp
        if abs(timestamp-int(dic['time'])) > 2:
            alarm1 = 1
            print('主机与用户机时间差超过两秒!!!立即校正时间与主机一致!!!')

    if dic['main_ventilator'] == 0 and dic['vice_ventilator'] == 0:
        alarm2 = 1
        print('警告!!! 检测到主风扇与副风扇已停止工作!!!下位机应立即开启主风扇!!!')
        main_ventilator = 1

    if dic['CH4'] >= 20:
        if dic['CH4'] < 40:
            print('警告!!!检测甲烷浓度超标,应立即采取措施!!!')
        else:
            alarm3 = 1
            print('警告!!!甲烷浓度已达危险程度,下位机立即将设备断电!!!')
            relay_mian = 0
            relay_trans = 0

    if dic['O2'] <= 60:
        alarm4 = 1
        vice_ventilator = 1
        print('氧气浓度过低,应立即打开备用风扇')

    if dic['temp'] >= 40:
        alarm4 = 1
        vice_ventilator = 1
        print('温度过高,应立即打开备用风扇')

    sen = ''
    sen += str(main_ventilator) + '#'
    sen += str(vice_ventilator) + '#'
    sen += str(relay_mian) + '#'
    sen += str(relay_trans) + '#'
    sen += str(alarm1)

    dataSocket.send(sen.encode())
    print()

    rec = dataSocket.recv(BUF_LEN)
    data = rec.decode()
    l_t = data.split('#')
    lis = [int(i) for i in l_t]

    if lis[0] == 0 and lis[1] == 0:
        print('下位机已接受命令，并成功执行')
    else:
        if lis[0]:
            print('警告!!!煤矿开采设备继电器未能成功断电,立即采取措施!!!')
        if lis[1]:
            print('警告!!!传输设备继电器未能成功断电,立即采取措施!!!')

    return


listenSocket = socket(AF_INET, SOCK_STREAM)
listenSocket.bind((IP, PORT))
listenSocket.listen(5)

print(f'服务机加载成功, 服务端口号: {PORT}')

while True:

    try:
        dataSocket, addr = listenSocket.accept()
        print('-----------split line-----------------\n')
        th_sever = threading.Thread(target=sever_working, args=(dataSocket,))
        th_sever.start()
    except:
        break

listenSocket.close()

