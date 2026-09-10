from socket import *
import time
import threading
import random

IP = '127.0.0.1'
SERVER_PORT = 50000
BUF_LEN = 1024

L1 = ['main_ventilator', 'vice_ventilator', 'relay_mian', 'relay_trans', 'time clock']

# 各个变量
O2 = 60
CH4 = 10
temp = 20
relay_mian = 1
relay_trans = 1
main_ventilator = 1
vice_ventilator = 0

alarm1 = 0
alarm2 = 0

def user_working(dataSocket):
    global relay_mian
    global relay_trans
    global main_ventilator
    global vice_ventilator
    global alarm1
    global alarm2

    alarm1 = 0
    alarm2 = 0

    while True:
        try:
            rec = dataSocket.recv(BUF_LEN)
            if not rec:
                break
            data = rec.decode()
            l_t = data.split('#')
            lis = [int(v) for v in l_t]
            dic = dict(zip(L1, lis))
            print('已收到主机消息')

            p_mian = random.randint(0, 9)
            p_trans = random.randint(0, 9)

            if dic['main_ventilator'] == 1:
                print('主风扇已开启')
            else:
                print('主风扇已关闭')

            if dic['vice_ventilator'] == 1:
                print('备用风扇已开启')
            else:
                print('备用风扇已关闭')

            if dic['relay_mian'] == 1:
                print('开采设备正在通电运行')
            else:
                if p_mian == 0:
                    alarm1 = 1
                    print('开采设备正在通电运行')
                else:
                    print('开采设备已断电')

            if dic['relay_trans'] == 1:
                print('运输设备正在通电运行')
            else:
                if p_trans == 0:
                    alarm2 = 1
                    print('运输设备正在通电运行')
                else:
                    print('传输设备已断电')

            if dic['time clock'] == 1:
                print('已调整时钟, 与主机保持一致')

            f_back = ''
            f_back += str(alarm1) + '#' + str(alarm2)

            print('-----------------split line-------------------\n')

            dataSocket.send(f_back.encode())

        except:
            break

    return


dataSocket = socket(AF_INET, SOCK_STREAM)

while True:
    dataSocket = socket(AF_INET, SOCK_STREAM)
    dataSocket.connect((IP, SERVER_PORT))

    sen = ''
    time.sleep(1)
    for i in range(4):
        time.sleep(1)

        relay_change = 0
        p_envir = random.randint(0, 4)

        p_ven1 = random.randint(0, 19)
        if p_ven1 == 0:
            main_ventilator = 0
            relay_change = 1

        p_ven2 = random.randint(0, 19)
        if p_ven2 == 0:
            vice_ventilator = 0
            relay_change = 1

        if p_envir == 0 or relay_change == 1:
            O2 = random.randint(40, 100)
            CH4 = random.randint(1, 60)
            temp = random.randint(10, 60)
            break

    timestamp = int(time.time())
    sen += str(O2) + '#'
    sen += str(CH4) + '#'
    sen += str(temp) + '#'
    sen += str(main_ventilator) + '#'
    sen += str(vice_ventilator) + '#'
    sen += str(timestamp)

    try:
        dataSocket.send(sen.encode())
        th_user = threading.Thread(target=user_working, args=(dataSocket,))
        th_user.start()
    except:
        break

dataSocket.close()
