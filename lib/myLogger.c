#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include "myLogger.h"

sqlite3 *db;
sqlite3_stmt *res;
const char filepath[] = "/var/log/myLogger.db";

int callback(void *, int, char**, char**);

/*
*   Creates a database in filepath[]
*   Creates a table inside with id, date,time,level,text
*/

int createDb(void)
{
    char *err_msg;
    openDatabase();

    char *sql = "DROP TABLE IF EXISTS Log;"
                "CREATE TABLE Log(Id INTEGER PRIMARY KEY, Date TEXT, Time TEXT, level TEXT, data TEXT);";
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if(rc != SQLITE_OK)
    {
        fprintf(stderr, "myLogger: SQL error %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }
    sqlite3_close(db);
    printf("myLogger: Database created\n");
    return 0;

} //End of create DB

/*
*   Inserts data into filepath[] database
*   Data is inserted inside Log table
*   There are 2 inputs: 1.data level 2.data
*/
int insertData(char *inputLevel, char *data)  //Inserts single line of data, database needs to be opened/close
{
    char *err_msg;
    char level[8];

    switch(inputLevel[0])
    {
        case '1':
        strcpy(level, "INFO");
        break;

        case '2':
        strcpy(level, "WARNING");
        break;

        case '3':
        strcpy(level, "ERROR");
        break;

        default:
        strcpy(level, "INFO");
        break;
    }
    
    char *sql = sqlite3_mprintf("INSERT INTO Log (date, time, level, data) VALUES (CURRENT_DATE, CURRENT_TIME, '%q', '%q');", level, data);
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if(rc != SQLITE_OK)
    {
        fprintf(stderr, "myLogger: SQL error %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_free(sql);
        sqlite3_close(db);
        return 1;
    }
    sqlite3_free(err_msg);
    sqlite3_free(sql);
    printf("myLogger: Inserted data into DB\n");
    return 0;
}

/*
*   Prints all data inside filepath[] database
*   From Log table
*/
int printData(void)  
{
    char *err_msg;

    int rc = sqlite3_open(filepath, &db);

    if(rc != SQLITE_OK)
    {
        fprintf(stderr, "myLogger: Cannot create database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    char *sql = "SELECT * FROM Log";
    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);

    if(rc != SQLITE_OK)
    {
        fprintf(stderr, "myLogger: Failed to select data\n");
        fprintf(stderr, "myLogger: SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }
    
    sqlite3_close(db);
    printf("myLogger: Printed out all DB data\n");
    return 0;
}

/*
*   deleteAllData() used to delete all data from database
*   Automatically opens/closes database
*/
int deleteAllData(void)
{
    char *err_msg;

    int rc = sqlite3_open(filepath, &db);

    if(rc != SQLITE_OK)
    {
        fprintf(stderr, "myLogger: Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    char *sql = "DELETE FROM Log;";
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if(rc != SQLITE_OK)
    {
        fprintf(stderr, "myLogger: SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }
    
    sqlite3_close(db);
    printf("myLogger: Deleted all data from Log column\n");
    return 0;
}

/*
*   callback is used for function printData
*/
int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    NotUsed = 0;
    for(int i = 0; i < argc; i++)
    {
        printf(" %s = %s |", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");

    return 0;
}

/*
*   openDatabase is used to open database externally
*/
void openDatabase(void)
{
    int rc = sqlite3_open(filepath, &db);

    if(rc != SQLITE_OK)
    {
        fprintf(stderr, "myLogger: Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    }
}

/*
*   closeDatabase is used to close database
*/
void closeDatabase(void)
{
    sqlite3_close(db);
}
