#include <winsock2.h>
#include <cstdlib> // For exit() and EXIT_FAILURE
#include <iostream> // For cout
#include <ws2tcpip.h>



using namespace std;

int main()
{
    WSADATA wsadata;
    if(WSAStartup(MAKEWORD(2,2), &wsadata) != 0)
    {
        cout << "WSASTART FAILED" << endl;
        return -1;
    }

    SOCKET clientSock = socket(AF_INET, SOCK_STREAM, 0);
    if(clientSock == INVALID_SOCKET)
    {
        cout << "SOCKET creation failed" << WSAGetLastError() <<endl;
        WSACleanup();
        return -1;
    }

    //CONFIGURE SERVER ADDRESS
    int portNum = 55555;
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port =  htons(portNum); //server port

    if(inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr) <= 0)
    {
        cout << "Invalid address/Address not supported" << endl;
        closesocket(clientSock);
        WSACleanup();
        return -1;
    }

    //connect to server
    if(connect(clientSock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        cout << "Connection failed: " << WSAGetLastError() << endl;
        closesocket(clientSock);
        WSACleanup();
        return -1;
    }

    cout << "CONNECTED TO SERVER" << endl;

    //send a message to server
    const char* message = "Hello from client";
    int bytesSent = send(clientSock, message, strlen(message), 0);
        if (bytesSent == SOCKET_ERROR) {
        cout << "Send failed: " << WSAGetLastError() << endl;
    } else {
        cout << "Message sent to server: " << message << endl;
    }

    //recieve a response from server

    char buffer[1024] = {0};
    int bytesReceived = recv(clientSock, buffer, sizeof(buffer),0);
    if(bytesReceived > 0)
    {
        cout << "Server response: " << string(buffer, bytesReceived) << endl;
    }
    else if(bytesReceived == 0)
    {
        cout << "Connection Closed by server." << endl;
    }
    else
    {
        cout << "Recv failed: " << WSAGetLastError() << endl;
    }

    cout << "Press enter to exit...";
    cin.get();

    closesocket(clientSock);
    WSACleanup();
    return 0;
}