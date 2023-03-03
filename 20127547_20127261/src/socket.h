#include<iostream>
#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<netdb.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include <math.h> 
#include <arpa/inet.h>
#include <map>
#include<string.h>
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
public:
    int fd_tmp[2];
    int fd_res;
    string url;
    string path;
	Socket(string nameFIle,string link);
    ~Socket();
	void Connect();
	void setSum(long t);
	long getSum();
	long Receive();
	int Send(string rbuf);
};