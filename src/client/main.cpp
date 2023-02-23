#include"socket.h"
int main(){
    Socket *client_socket=new Socket();
    string get_http = "GET / HTTP/1.1\r\nHost: " + string(client_socket->url) + "\r\nConnection: close\r\n\r\n";
    client_socket->Send(get_http);
   
    while(1){
        client_socket->Receive();
    }
    return 1;
}