#include"db.h"
void CreateDB(db_t* db){
    db->fptr=NULL;
}
db_t db_open(char* name){
    db_t db;
    CreateDB(&db);
    fopen(name,"w+");

    return db;
}
void CreateTable(table_t* table){
    table->fptr=NULL;
    table->colums=NULL;
}
void DestroyTable(table_t* table){
    if(table->fptr!=NULL){
        fclose(table->fptr);
        table->fptr=NULL;
    }
    if(table->colums!=NULL){
        free(table->colums);
        table->colums=NULL;
    }
}
static void NameToNameEx(char* nametable,char* res){
    int sizenametable=strlen(nametable);
    strcpy(res,nametable);
    strcpy(&res[sizenametable],".olxtable");
}
table_t table_createtable(char nametable[150],colum_t* arraycolum,char sizearray){
    table_t table;
    CreateTable(&table);
    char nametableEx[160];//.olxtable
    NameToNameEx(nametable,nametableEx);
    table.fptr=fopen(nametableEx,"w");
    fwrite(&sizearray,1,1,table.fptr);
    for(int i=0;i<sizearray;i++){
        int type_c=arraycolum[i].type_colum;
        int mod=arraycolum[i].mod;
        fwrite(arraycolum[i].name,100,1,table.fptr);
        fwrite(&type_c,1,1,table.fptr);
        fwrite(&arraycolum[i].size,1,4,table.fptr);
        fwrite(&mod,1,1,table.fptr);
    }
    fclose(table.fptr);
}
table_t table_open(char nametable[150]){
    char nametableEx[160];//.olxtable
    NameToNameEx(nametable,nametableEx);
    table_t table;
    CreateTable(&table);
    table.fptr=fopen(nametableEx,"r");
    fseek(table.fptr, 0, SEEK_SET);
    char amount_colum;
    fread(&amount_colum,1,1,table.fptr);
    int size_byte_colums=amount_colum*META_SIZE_COLUM;
    char* byte_colums=malloc(size_byte_colums);
    fread(byte_colums,META_SIZE_COLUM*amount_colum,1,table.fptr);
    colum_t* c=malloc(amount_colum*sizeof(colum_t));
    int n=0;
    char temp;
    for(int i=0;i<amount_colum;i++){
        memcpy(c[i].name,&byte_colums[n],100);
        n+=100;
        memcpy(&c[i].type_colum,&byte_colums[n],1);
        n++;
        memcpy(&c[i].size,&byte_colums[n],4);
        n+=4;
        memcpy(&c[i].mod,&byte_colums[n],1);
        n++;
    }
    table.colums=c;
    printf("AMOUNT_colum: %d\n",amount_colum);
    fclose(table.fptr);
    table.fptr=NULL;
}