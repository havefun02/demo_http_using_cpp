#include"socket.h"
int main(int argc, char*argv[]){
 
    string file=argv[2];
    string link=argv[1];
    string empty=argv[0];
    cout<<file << " " <<link<<" "<<argv[2];
    Socket *client_socket=new Socket(file,link);
    string get_http = "GET / HTTP/1.1\r\nHost: " + string(client_socket->url) + "\r\nConnection: close\r\n\r\n";
    client_socket->Send(get_http);
    while(1){
        long t=client_socket->Receive();
        client_socket->setSum(t);
        cout<<client_socket->getSum();
    }
    return 1;
}