#include"socket.h"
#include <map>
#include<string.h>
string getHeader(unsigned int fd);
int findIndexDBRN(string str);
map<string,string> Extract(int s,int e,string mystring);
pair<string,string> ExtractSign(int s,string mystring);
int findIndexSingleRN(string str,int s);
string getContentLength(map<string,string> t);
bool compare2String(string s1,string s2);
string FindTypeTransfer(map<string,string> t);
bool writeFileContentLength(int fd_tmp,int fd_res,int s,int e);
bool writeFileChunked(int fd_tmp,int fd_res,int s,int e);
int main(int argc, char**argv){
    string pathUrl[10];
    string arg[2];
    string FinalPath="";
    string fileExe=*(argv++);
    int ind=0;
    while(*argv!=NULL){
        arg[ind]=*(argv++);
        ind++;
    }
    string tmp(arg[0]);
    if (compare2String(tmp.substr(0,7),"http://")){
        tmp=tmp.substr(7);
    }
    if (tmp[tmp.length()-1]=='/'){
        tmp=tmp.substr(0,tmp.length()-1);
    }

    int lengthOfTmp=tmp.length();

    for (int i=lengthOfTmp-1;i>0;i--){
        if (tmp[i]=='/')
        {
            FinalPath=tmp.substr(i+1)+FinalPath;

            tmp=tmp.substr(0,i);
        }
    }
    Socket *client_socket=new Socket(arg[1],tmp);
    string get_http = "GET /"+FinalPath+" HTTP/1.1\r\nHost: " + string(client_socket->url) + "\r\nConnection: close\r\n\r\n";
    client_socket->Send(get_http);
    while(1){
        long t=client_socket->Receive();
        if (t==0) { break;}
        client_socket->setSum(t);
    }
    string ASTRING=getHeader(client_socket->fd_tmp[0]);
    int end=ASTRING.length();
    cout<<ASTRING<<endl;
    map<string,string> arr=Extract(0,end,ASTRING.substr(0,end));
    map<std::string, string>::iterator it = arr.begin();
    // while (it != arr.end())
    // {
    //     cout << "Key: " << it->first << ", Value: " << it->second << endl;
    //     ++it;
    // }
    string len=(getContentLength(arr));
    if (len==""){
        if (compare2String(FindTypeTransfer(arr),"chunked")){
            writeFileChunked(client_socket->fd_tmp[0],client_socket->fd_res,end,atoi(len.c_str()));
        }
        else{
            cout<<"other type"<<endl;
        }
    }
    else{
        writeFileContentLength(client_socket->fd_tmp[0],client_socket->fd_res,end,atoi(len.c_str()));
    }client_socket->~Socket();
    return 1;
}
string getHeader(unsigned int fd){
    char ret[1]={0};
    string header="";
    int check=0;
    while(1){
        int res=read(fd,ret,1);
        header+=ret;
        if (header.length()>4)
            if (compare2String(header.substr(header.length()-4),"\r\n\r\n")){
                return header;
            }
    }
    return header;
}

int findIndexDBRN(string str){
    for (int i=0;i<str.length()-4;i++){
        if (compare2String(str.substr(i,4),"\r\n\r\n")){
            return i+4;
        }
    }
    return 0;   
}

int findIndexSingleRN(string str,int s){
    for (int i=s;i<str.length();i++){
        if (str.substr(i,2)=="\r\n"){
            return i+2;
        }
    }
    return 0;   
}
pair<string,string> ExtractSign(int s,string mystring){
    for (int i=s;i<mystring.length();i++){
        if (int(mystring[i])==int(':')) {
            return pair<string,string>(mystring.substr(s,i-s),mystring.substr(i+2));
        }
    }
    return pair<string,string>("","");
}
map<string,string> Extract(int s,int e,string mystring){
    map<string,string> res;
    while(s<e){
        int ind=findIndexSingleRN(mystring,s);
        pair<string,string> resFromExtract=ExtractSign(0,mystring.substr(s,ind-2-s));
        if (resFromExtract.first!="" && resFromExtract.second!=""){
            res.insert(resFromExtract);}
        
        s=ind;
    }
    return res;
}

string getContentLength(map<string,string> t){
    map<string, string>::iterator it = t.begin();
    while (it != t.end())
    {
        if (compare2String(it->first,"Content-Length")) return it->second;
        it++;
     }
     return "";
}

string FindTypeTransfer(map<string,string> t){
    map<string, string>::iterator it = t.begin();
    while (it != t.end())
    {
        if ( compare2String(it->first,"Transfer-Encoding")) return it->second;
        it++;
     }
     return "";
}
int hextodec(string t){
    int res=0;
    for (int i=0;i<t.length();i++){ 
        if (t[i]>='0' && t[i]<='9')
            res+=pow(16,t.length()-1-i)*(int(t[i])-48);
        else
            res+=pow(16,t.length()-1-i)*(int(t[i])-87);
    }
    return res;
}

bool writeFileChunked(int fd_tmp,int fd_res,int s,int e){
    char counter[1]={0};
    string byteChunked="";
    while(1){
        int res =read(fd_tmp,counter,1);
        if (res==0) return 1;
        if (res<0) return 0;
        if (!compare2String(counter,"\n") && !compare2String(counter,"\r"))
            byteChunked+=counter;
        else if (compare2String(counter,"\n")){
            char *strTmp=new char[hextodec(byteChunked)];
            int tmp=read(fd_tmp,strTmp,hextodec(byteChunked));
            if (tmp<0){
                delete strTmp;
                return 0;
            }
            if (write(fd_res,strTmp,hextodec(byteChunked))<0) {
                delete strTmp; 
                return 0;
            }
            delete strTmp;
            byteChunked="";
        }

    }
}

bool writeFileContentLength(int fd_tmp,int fd_res,int s,int e){
    char *cont=new char[e];
    int res =read(fd_tmp,cont,e);
    if (res<0) {delete cont; return 0;}
    if (write(fd_res,cont,res)){delete cont;
    return 1;}
    else {delete cont; return 0;}
}

bool compare2String(string s1,string s2){
    if (s1.length()!=s2.length())
        return 0;
    for (int i=0;i<s1.length();i++){
        if (s1[i]!=s2[i]) return 0;
    }
    return 1;
}