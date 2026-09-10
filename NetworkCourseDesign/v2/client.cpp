#include <vector>
#include <string>
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <thread>

using namespace std;

#pragma comment(lib, "Ws2_32.lib")

// 编译说明：需链接 Ws2_32.lib，建议使用 MSVC 或 MinGW 并添加 -lws2_32
// 编码：UTF-8（BOM 可选，MSVC 下建议加 /utf-8 编译选项）

int powerFeedbackSensor = 0; // 断电反馈传感器状态

int main()
{
    WSADATA wsaData;
    SOCKET sock = INVALID_SOCKET;
    // 将套接字 sock 初始化为 INVALID_SOCKET，表示无效套接字。
    // 在后续的代码中，使用套接字进行通信。
    struct sockaddr_in server;
    // 存储服务器地址信息。在此结构体中，sockaddr_in 是一个用于表示 IPv4 地址的结构体。
    // 结构体包含了服务器的 IP 地址和端口号等信息。
    char message[1024];

    // 初始化 Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        printf("无法初始化 Winsock，错误码：%d\n", WSAGetLastError());
        return 1;
    }

    // 创建套接字
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) // 无效套接字
    {
        printf("无法创建套接字，错误码：%d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    printf("套接字已创建\n");

    // 设置服务器地址
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); // 服务器的 IP 地址
    server.sin_family = AF_INET;                     // IPv4 地址族。
    server.sin_port = htons(12345);                  // 端口号

    // 连接到服务器
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        printf("连接失败，错误码：%d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    printf("已成功连接到服务器\n");

    // 初始化随机数种子
    srand((unsigned int)time(NULL));

    // 模拟传感器数据并循环上报
    while (1)
    {
        time_t currentTime = time(NULL);   // long long 8字节
        int methaneLevel = rand() % 65536; // 模拟甲烷浓度，16 位，4字节
        int temperature = rand() % 256;    // 模拟温度，8 位，2字节
        int oxygenLevel = rand() % 256;    // 模拟氧气浓度，8 位，2字节
        int fanState = rand() % 4;         // 模拟风扇状态，2 位，高位是主风扇，低位是副风扇，1字节

        sprintf(message, "TIME:%ld,METHANE:%d,TEMP:%d,OXYGEN:%d,FAN:%d,POWER:%d,powerFeedbackSensor:%d\n",
                (long)currentTime, methaneLevel, temperature, oxygenLevel, fanState, powerFeedbackSensor);
        send(sock, message, strlen(message), 0);

        int bytesRead = recv(sock, message, sizeof(message), 0);
        if (bytesRead == SOCKET_ERROR || bytesRead == 0)
        {
            printf("接收超时或出错，错误码：%d\n", WSAGetLastError());
            break;
        }
        cout << "已收到服务器消息" << endl;

        // 解析回复数据（格式：fan#time_correct#relay_main#relay_trans#fan_state#）
        message[bytesRead] = '\0'; // 字符串终止符
        vector<int> reply;
        int begin = 0;
        for (int i = 0; i < bytesRead; i++)
        {
            if (message[i] == '#')
            {
                string str;
                for (int j = begin; j < i; j++)
                    str += message[j];
                reply.push_back(stoi(str));
                begin = i + 1;
            }
        }

        // reply[0] = 风扇状态：0=全关，1=副开，2=主开，3=全开
        if (reply[0] == 2 || reply[0] == 3)
            cout << "主风扇已开启" << endl;
        else
            cout << "主风扇已关闭" << endl;

        if (reply[0] == 1 || reply[0] == 3)
            cout << "副风扇已开启" << endl;
        else
            cout << "副风扇已关闭" << endl;

        // reply[4] = fan_state：2 表示环境适宜，关闭副风机
        if (reply[4] == 2)
        {
            cout << "温度和氧气浓度适宜，已关闭副风机" << endl;
        }

        // reply[1] = 时间校正标志
        if (reply[1] == 1)
            cout << "已校正时钟，与主机保持一致" << endl;

        // 以下为调试用输出（已注释）
        // cout << message << endl;
        // cout << "风扇状态：" << reply[0] << endl;
        // cout << "时间校正：" << reply[1] << endl;
        // cout << "开采设备继电器：" << reply[2] << endl;
        // cout << "传输设备继电器：" << reply[3] << endl;

        int relay_main = rand() % 5;
        int relay_trans = rand() % 5;
        int alarm1 = 0, alarm2 = 0;

        // reply[2] = 开采设备继电器指令（1=保持通电，0=要求断电）
        if (reply[2] == 1)
            cout << "开采设备继续通电运行" << endl;
        else
        {
            if (relay_main == 0)
            {
                alarm1 = 1;
                cout << "警告！开采设备继电器断电失败！" << endl;
            }
            else
                cout << "开采设备已成功断电" << endl;
        }

        // reply[3] = 传输设备继电器指令（1=保持通电，0=要求断电）
        if (reply[3] == 1)
            cout << "传输设备继续通电运行" << endl;
        else
        {
            if (relay_trans == 0)
            {
                alarm2 = 1;
                cout << "警告！传输设备继电器断电失败！" << endl;
            }
            else
                cout << "传输设备已成功断电" << endl;
        }

        if (reply[2] == 1)
            cout << "已断电时钟，与主机同步" << endl;

        char back_message[1024];
        sprintf(back_message, "%d#%d",
                alarm1, alarm2);
        printf("--------------------------------分割线-------------------------------\n");
        send(sock, back_message, strlen(back_message), 0);

        Sleep(5000); // 在发送下一帧之前等待 5 秒
    }

    // 退出前关闭套接字并清理 Winsock
    closesocket(sock);
    WSACleanup();
    return 0;
}
