#pragma once
#include"server.h"
#include"db.h"
#define STATUS_OK 102
#define STATUS_NOT_AUTH 101
typedef struct dbclient{
    sv_user_t client;
    bool auth;
    db_t db;
}dbclient_t;
void CreateDBClient(dbclient_t* db);
void ClearDBClient(dbclient_t* db);
typedef struct RES_status{
    sv_packres_t pack;
    int code;
}RES_status_t;
void CreateRES_status(RES_status_t* status);
sv_json_construct_t RES_status_getjson(RES_status_t* pk);
typedef struct REQ_auth{
    sv_packreq_t pack;
    char authcode[200];
}REQ_auth_t;
void CreateREQ_auth(REQ_auth_t* auth);
bool REQ_auth_jsontoobject(REQ_auth_t* auth,json_value* values);
void REQ_auth_process(REQ_auth_t* auth,sv_user_t* user);

bool CheckAuth(sv_user_t* user,sv_packreq_t* pkreq);

typedef struct REQ_setdatabase{
    sv_packreq_t pack;
    char database[100];
}REQ_setdatabase_t;
void CreateREQ_setdatabase(REQ_setdatabase_t* setdb);
bool REQ_setdatabase_jsontoobject(REQ_setdatabase_t* setdb,json_value* values);
void REQ_setdatabase_process(REQ_setdatabase_t* setdb,sv_user_t* user);
void InitREQPack(sv_server_t* server);