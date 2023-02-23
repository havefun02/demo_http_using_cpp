#include <bits/stdc++.h>
#include <netinet/in.h>
#include<unistd.h>
#include<thread>
#include<sys/socket.h>
#include<string.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#define PORT 2323
#define maxQue 20
using namespace std;
struct threads{
    int id;
    string name;
    int socket;
    thread thr;
};
vector<threads> clients;
int server_fd;//server

void handleClient(int clientSocket, int id){
    while(1){
		// int recvMes=read(new_socket,recv_message,1024);
		// if (recvMes>0){
        //     cout<<recv_message<<endl;
		// }
        
		char mes[50]="hello" ;
		int sendMes=send(server_fd,mes,1024,0);
		if (sendMes>0){
            cout<<"sent"<<endl;
		}
	}
}

int main()
{
	int new_socket;//client
    int count=0;
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
    struct sockaddr_in client_addr;//{contains AF_INET(internet protocal), Address port }
    while (1){
        if ((new_socket
            = accept(server_fd, (struct sockaddr*)&address,
                    (socklen_t*)&addrlen))
            < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        else{
            cout<<"commingg"<<address.sin_addr.s_addr<<endl;
            count++;
            thread t;
            t=handleClient(new_socket,count);
            clients.push_back({count,string("NONAME"),new_socket,(move(t))});
        }   
    }
	


    // closing the connected socket
    close(new_socket);
    // closing the listening socket
    shutdown(server_fd, SHUT_RDWR);
    return 0;
}


