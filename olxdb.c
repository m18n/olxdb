#include"include/olxdb.h"
void CreateDBClient(dbclient_t* db){
    sv_CreateUser(&db->client);
    db->auth=false;
}
void ClearDBClient(dbclient_t* db){

}
void CreateRES_status(RES_status_t* status){
    sv_CreatePackRes(&status->pack);
    status->pack.idpack=2;
    status->code=0;
    status->pack.GetJsonPack=RES_status_getjson;
}
sv_json_construct_t RES_status_getjson(RES_status_t* pk){
    sv_json_construct_t json;
    sv_CreateJson_Construct(&json);
    sv_json_item_t code;
    sv_CreateJson_Item(&code);
    sv_json_item_setname(&code,"code");
    sv_json_item_setintvalue(&code,pk->code);
    sv_json_construct_addelement(&json,code);
    return json;
}
void CreateREQ_auth(REQ_auth_t* auth){
    sv_CreatePackReq(&auth->pack);
    auth->pack.JsonToObject=REQ_auth_jsontoobject;
    auth->pack.ProcessPack=REQ_auth_process;
}
bool REQ_auth_jsontoobject(REQ_auth_t* auth,json_value* values){
    json_object_entry* codeauth=sv_GetNameKey(values,"authcode");
    if(codeauth!=NULL&&codeauth->value->type==json_string){
        strcpy(auth->authcode,codeauth->value->u.string.ptr);
        return true;
    }
    return false;
}
void REQ_auth_process(REQ_auth_t* auth,sv_user_t* user){
    dbclient_t* client=(dbclient_t*)user;
    RES_status_t status;
    CreateRES_status(&status);
    status.code=0;
    if(strcmp(auth->authcode,"niger")==0){
        client->auth=true;
        status.code=1;
        printf("GOOD AUTH\n");
    }

    sv_SendPackRes(user,&status,auth);
}
void InitREQPack(sv_server_t* server){
    sv_serv_adduserpacks(server,CreateREQ_auth,sizeof(REQ_auth_t),1);
}