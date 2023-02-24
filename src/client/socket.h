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
    int fd=0;
public:
    string url;
	Socket(string nameFIle,string link);
    ~Socket();
	void Connect();
	void setSum(long t);
	long getSum();
	long Receive();
	int Send(string rbuf);
};