#include"stdio.h"
#include"stdlib.h"
#include"olxdb.h"
int main(){
    printf("HELLO SERVER START BD\n");
    // sv_server_t serv;
    // sv_ServerInit(&serv,9997,10);
    // InitREQPack(&serv);
    // sv_ServerStart(&serv,sizeof(dbclient_t),CreateDBClient,ClearDBClient);
    colum_t c[3];
    c[1].mod=INTELECT;
    strcpy(c[1].name,"id");
    c[1].size=4;
    c[1].type_colum=INT;
    
    table_createtable("data_table",&c,1);
    // table_open("data_table");
    sleep(2000);
    return 0;
}