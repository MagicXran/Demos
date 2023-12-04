#include <iostream>
#include <string>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cout << "Failed to initialize winsock" << endl;
        return 1;
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        cout << "Failed to create socket" << endl;
        return 1;
    }

    string serverAddress = "192.168.5.5"; // 服务器地址
    int port = 9110; // telnet端口号

    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(serverAddress.c_str());

    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        cout << "Connection failed" << endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

//    string message = "Hello, world!"; // 要发送的消息
//    if (send(sock, message.c_str(), message.length(), 0) == SOCKET_ERROR) {
//        cout << "Failed to send message" << endl;
//        closesocket(sock);
//        WSACleanup();
//        return 1;
//    }

    char buffer[4096];
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytesRead = recv(sock, buffer, sizeof(buffer)-1, 0);
        if (bytesRead == SOCKET_ERROR) {
            cout << "Failed to receive message" << endl;
            break;
        } else if (bytesRead == 0) {
            cout << "Connection closed" << endl;
            break;
        } else {
            cout << "Received message: " << buffer << endl;
        }
    }


    closesocket(sock);
    WSACleanup();
    return 0;
}
