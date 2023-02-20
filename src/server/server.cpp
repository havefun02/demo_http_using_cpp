#include<iostream>
#include <netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#define PORT 2323
#define maxQue 20
using namespace std;
int main()
{
	int server_fd;//server
	int new_socket;//client
	int valread;
    struct sockaddr_in address;//{contains AF_INET(internet protocal), Address port }
    int opt = 1;
    int addrlen = sizeof(address);//size of the address socket
    char recv_message[1024] = { 0 };//receive message from client
	const char* hello="Hello from server";
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
 
    // Forcefully attaching socket to the port 2323
    if (setsockopt(server_fd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
	address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
 
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr*)&address,
             addrlen)
        < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, maxQue) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket
         = accept(server_fd, (struct sockaddr*)&address,
                  (socklen_t*)&addrlen))
        < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
	else
	{
		cout<<"connected"<<endl;
	}
	while(1){
		int recvMes=recv(server_fd,recv_message,1024,0);
		if (recvMes>0){

		}
		char mes[50]="hello" ;
		int sendMes=send(server_fd,mes,1024,0);
		if (sendMes>0){

		}
	}


    // closing the connected socket
    close(new_socket);
    // closing the listening socket
    shutdown(server_fd, SHUT_RDWR);
    return 0;
}

