#pragma once
#define DB_OPEN 0
#define DB_ERROR_OPEN 1
#include"stdio.h"
#include"stdlib.h"
#include"string.h"
#define META_SIZE_COLUM 106
typedef struct db{
    FILE* fptr;
    char namedatabase[150];

}db_t;
void CreateDB(db_t* db);
db_t db_open(char* name);
enum type_colum{
    INT,
    TEXT,
    STATIC_TEXT
};
enum mod{
    NONE,
    INTELECT
};
typedef struct colum{
    char name[100];
    enum type_colum type_colum;
    int size;
    enum mod mod;
}colum_t;
typedef struct table{
    FILE* fptr;
    colum_t* colums;
}table_t;
void CreateTable(table_t* table);
table_t table_createtable(char nametable[150],colum_t* arraycolum,char sizearray);
table_t table_open(char nametable[150]);
void DestroyTable(table_t* table);