#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

sqlite3 *db;
sqlite3_stmt *res;
const char filepath[] = "/var/log/manoLogeris/manoDuombaze.db";

int callback(void *, int, char**, char**);

int createDb(void)
{
    char *err_msg;
    int rc = sqlite3_open(filepath, &db);

    if(rc != SQLITE_OK)
    {
        fprintf(stderr, "Cannot creat database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char *sql = "DROP TABLE IF EXISTS Log;"
                "CREATE TABLE Log(Id INTEGER PRIMARY KEY, Date TEXT, Time TEXT, level TEXT, data TEXT);";
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if(rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }
    sqlite3_close(db);
    printf("Database created\n");
    return 0;

} //End of create DB

int insertData(char *inputLevel, char *data)
{
    int rc = sqlite3_open(filepath, &db);
    char *err_msg;
    char level[8];

    if(rc != SQLITE_OK)
    {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    
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
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if(rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_free(sql);
        sqlite3_close(db);
        return 1;
    }
    sqlite3_free(err_msg);
    sqlite3_free(sql);
    sqlite3_close(db);
    //printf("String inside data is: %s \n", data);
    printf("Inserted data into DB\n");
    return 0;
}
int printData(void)
{
    char *err_msg;

    int rc = sqlite3_open(filepath, &db);

    if(rc != SQLITE_OK)
    {
        fprintf(stderr, "Cannot creat database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    char *sql = "SELECT * FROM Log";
    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);

    if(rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }
    
    sqlite3_close(db);
    printf("Printed out all DB data\n");
    return 0;
}
int deleteAllData(void)
{
    //
    printf("Deleted all DB data\n");
    remove(filepath);
    return 0;
}

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