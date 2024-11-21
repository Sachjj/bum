#include <winsock2.h>
#include <cstdlib> // For exit() and EXIT_FAILURE
#include <iostream> // For cout
#include <ws2tcpip.h>



using namespace std;



int main() {
  WORD versionWanted = MAKEWORD(2,2);
  WSADATA wsaData;
  int wsaerr;
  wsaerr = WSAStartup(versionWanted, &wsaData);
  if(wsaerr != 0)
  {
    cout << "WSAStartup Failed: " << wsaerr << endl;
    return -1;
  }
  // Create a socket (IPv4, TCP)
  SOCKET serverSock = socket(AF_INET,SOCK_STREAM, 0);
  if(serverSock == INVALID_SOCKET)
  {
    cout << "Socket creation failed: " << WSAGetLastError() << endl;
    WSACleanup();
    return -1;
  }

  int portnum = 55555;
  sockaddr_in serveraddr;
  serveraddr.sin_family = AF_INET;
  /// WRONG //// serveraddr.sin_addr.s_addr = inet_pton(AF_INET, "127.0.0.1", &serveraddr.sin_addr);
  serveraddr.sin_port = htons(portnum);
  if(inet_pton(AF_INET, "127.0.0.1", &serveraddr.sin_addr) <= 0)
  {
    cout << "Invalid IP ADDR: " << WSAGetLastError() << endl;
    closesocket(serverSock);
    WSACleanup();
    return -1;
  }
  
  if(bind(serverSock,(struct sockaddr*)&serveraddr, sizeof(serveraddr)) == SOCKET_ERROR){
    cout << "bind failed" << WSAGetLastError() << endl;
    closesocket(serverSock);
    WSACleanup();
    return -1;
  }
  cout << "Socket bound successfully!" << endl;

if(listen(serverSock, SOMAXCONN) == SOCKET_ERROR)
{
  cout << "Listen Failed: " << WSAGetLastError() << endl;
  closesocket(serverSock);
  WSACleanup();
  return -1;
}

cout << "Socket is now listening on port: " << portnum << endl;

sockaddr_in clientaddr;
int clientAddrSize = sizeof(clientaddr);
//CREATE A SOCKET FOR THE CLIENT
SOCKET clientSock = accept(serverSock, (sockaddr*)&clientaddr, &clientAddrSize);
if(clientSock == INVALID_SOCKET)
{
  cout << "Accept failed: " << WSAGetLastError() << endl;
  closesocket(serverSock);
  WSACleanup();
  return -1;
}

cout << "Client Connected" << endl;

//recieve message from client
char buffer[1024] = {0};
int bytesRecieved = recv(clientSock, buffer, sizeof(buffer),0);
if(bytesRecieved > 0)
{
  cout << "recieved from client" << string(buffer, bytesRecieved) << endl;

  //send response to client
  const char* response = "Hello from server";
  send(clientSock, response, strlen(response),0);
}
else if(bytesRecieved < 0)
{
  cout << "Client disconnected." << endl;
}
else
{
  cout << "Recv failed: " << WSAGetLastError() << endl;
}
closesocket(clientSock);
cout << "Press enter to exit...";
cin.get();

// Cleanup Winsock
closesocket(serverSock);
WSACleanup();

return 0;

}