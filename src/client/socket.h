#include<iostream>
#include <netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<netdb.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
using namespace std;
class Socket
{
private:
    int _socket;
    struct hostent *host;
    int PORT=80;
    struct sockaddr_in address;
    char recv_message[4080] = { 0 };
    int opt=1;
public:
    const char* url="www.example.com";
	Socket();
    ~Socket();
	void Connect();
	int Receive();
	int Send(string rbuf);
};