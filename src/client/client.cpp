#include<iostream>
#include <netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#define PORT 2323
using namespace std;
int main()
{
	int socket_client;//client
    int status;
    struct sockaddr_in address;//{contains AF_INET(internet protocal), Address port }
    int opt = 1;
    int addrlen = sizeof(address);//size of the address socket
    char recv_message[1024] = { 0 };//receive message from client
	if ((socket_client = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
 
    // Forcefully attaching socket to the port 2323
    if (setsockopt(socket_client, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
	address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
 
    
    if ((status
         = connect(socket_client, (struct sockaddr*)&address,
                  addrlen))
        < 0) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

	while(1){
		int recvMes=recv(socket_client,recv_message,1024,0);
		if (recvMes>0){

		}
		char mes[50]="hello" ;
		int sendMes=send(socket_client,mes,1024,0);
		if (sendMes>0){

		}
	}


    // closing the connected socket
    close(socket_client);
    // closing the listening socket
    return 0;
}

