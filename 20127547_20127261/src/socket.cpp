#include"socket.h"
Socket::Socket(string nameFIle,string link){
    if (link[link.length()-1]=='/')
        link=link.substr(0,link.length()-1);
    url=link;
    string tmpFile="tmp.txt";
    if (pipe(fd_tmp)<0){
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    path=string((link)+"_"+(nameFIle));
    fd_res=open(path.c_str(),O_RDWR | (O_CREAT) ,S_IRWXU);
    fd_tmp[0]=open(tmpFile.c_str(),O_RDONLY | (O_APPEND |O_CREAT) ,S_IRWXU);
    fd_tmp[1]=open(tmpFile.c_str(),O_WRONLY | (O_APPEND |O_CREAT) ,S_IRWXU);
    Connect();
}
void Socket::Connect(){
    int status,s;
    struct addrinfo hints;
    struct addrinfo *result;
    struct addrinfo *rp;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
    hints.ai_flags = 0;
    hints.ai_protocol = 0;          /* Any protocol */
    s = getaddrinfo(url.c_str(), to_string(PORT).c_str(), &hints, &result);
    for (rp = result; rp != NULL; rp = rp->ai_next) {
               _socket = socket(rp->ai_family, rp->ai_socktype,
                            rp->ai_protocol);
               if (_socket == -1)
                   continue;

               if (connect(_socket, rp->ai_addr, rp->ai_addrlen) != -1)
                   break;                  /* Success */

           }
    freeaddrinfo(result);  
    // int addrlen = sizeof(address);
    // if ((_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    //     perror("socket failed");
    //     exit(EXIT_FAILURE);
    // }
    // Forcefully attaching socket to the port 80
    // if (setsockopt(_socket, SOL_SOCKET,
    //                SO_REUSEADDR | SO_REUSEPORT, &opt,
    //                sizeof(opt))) {
    //     perror("setsockopt");
    //     exit(EXIT_FAILURE);
    // }
    // address.sin_family = AF_INET;
    // address.sin_port = htons(PORT);
    // // address.sin_addr.s_addr = INADDR_ANY;
    // cout<<sizeof(host->h_addr_list[0])<<host->h_length<<endl;
    // memcpy(&address.sin_addr,host->h_addr_list[0],host->h_length);//fill the address.sin_addr with the host address
    // if ((status
    //      = connect(_socket, (struct sockaddr*)&address,
    //               addrlen))	
    //     < 0) {
    //     perror("connect");
    //     exit(EXIT_FAILURE);
    // }
    // endhostent();

}

Socket::~Socket(){
    string new_url="tmp.txt";
    int t= unlink(new_url.c_str());
    close(fd_tmp[0]);
    close(fd_tmp[1]);
    close(fd_res);
    close(_socket);
}

long Socket::Receive(){
    char recv_message[1024]={0};
    int res=recv(_socket,recv_message,1024,0);
    if (res<0){
        perror("Receive");
        exit(EXIT_FAILURE);
    }
    else{
        string tmp=string(recv_message);
        write(fd_tmp[1],recv_message,res);
    }
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
void Socket::setSum(long t){
    sum+=t;
}

long Socket::getSum(){
    return sum;
}
