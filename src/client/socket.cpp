#include"socket.h"
Socket::Socket(){
    Connect();
}
void Socket::Connect(){
    int status;
	host=gethostbyname(url);
    int addrlen = sizeof(address);
    if ((_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    // Forcefully attaching socket to the port 80
    if (setsockopt(_socket, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    // address.sin_addr.s_addr = INADDR_ANY;
    memcpy(&address.sin_addr,host->h_addr,host->h_length);//fill the address.sin_addr with the host address
    if ((status
         = connect(_socket, (struct sockaddr*)&address,
                  addrlen))	
        < 0) {
        perror("connect");
        exit(EXIT_FAILURE);
    }
    else{
        cout<<"connected"<<endl;
    }
}

Socket::~Socket(){
    close(_socket);
}

int Socket::Receive(){
    int fd=open("/home/lapphan/Project1/src/client/abc.txt",O_RDWR);
    int res=recv(_socket,recv_message,sizeof(recv_message),0);
    if (res<=0){
        perror("Receive");
        exit(EXIT_FAILURE);
    }
    else{
        string tmp=string(recv_message);
        cout<<tmp.substr(tmp.find("Content-Length: "),30);
        write(fd,recv_message,sizeof(recv_message));
	cout<<tmp<<endl;
        //do something
    }
    close(fd);

    return res;
}
int Socket::Send(string rbuf){
    int res=send(_socket,rbuf.c_str(),strlen(rbuf.c_str()),0);
    if (res<0){
        perror("Send");
        exit(EXIT_FAILURE);
    }
    else{
        //do something
    }
    return res;
}


