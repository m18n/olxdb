#include"stdio.h"
#include"stdlib.h"
#include"olxdb.h"
int main(){
    printf("HELLO SERVER START BD\n");
    sv_server_t serv;
    sv_ServerInit(&serv,9997,10);
    InitREQPack(&serv);
    sv_ServerStart(&serv,sizeof(dbclient_t),CreateDBClient,ClearDBClient);
   
    return 0;
}