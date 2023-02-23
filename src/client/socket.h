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
    int sum=0;
    struct hostent *host;
    int PORT=80;
    struct sockaddr_in address;
    int opt=1;
    int fd=open("/home/lapphan/Project1/src/client/bcd.txt",O_RDWR | (O_APPEND |O_CREAT) ,S_IRWXU);
public:
    const char* url="www.example.com";
	Socket();
    ~Socket();
	void Connect();
	void setSum(long t);
	long getSum();
	long Receive();
	int Send(string rbuf);
};