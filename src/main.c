#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <myLogger.h>
#include "main.h"

int main (int argc, char *argv[])
{
    printf("myLogger: Program started\n");
    int opt;

    if(argc != 2)
    {
        printHelp();
        return 1;
    }

    while((opt = getopt(argc, argv, "hcipda")) != -1)
    {
        switch(opt)
        {
        case 'h':
            printHelp();
            break;
        case 'c':
            createDb();
            break;
        case 'i':
            read_write_DB();
            break;
        case 'p':
            printData();
            break;
        case 'd':
            deleteAllData();
            break;
        case 'a':
            automaticMode();
            break;
        default:
            printHelp();
            return 1;
        }
    }
    printf("Program finished\n");
    return 0;
}

void printHelp()
{
    printf("Program is used to log data into a database.\n"
           "Database is created in /var/log/myLogger.db\n\n");
    printf("Usage:\n"
            "-h help\n"
            "-c create an empty database\n"
            "-i insert data manually\n"
            "-p print data to screen\n"
            "-d delete database\n"
            "-a automatic mode - inserts data every second\n\n");
}

void read_write_DB(void)
{
    char level[20];
    char word[50];

    printf("Write data level(1-INFO 2-WARNING 3-ERROR):\n");
    char z;     
    char i = 0; 

    int ch;

    while(z = getchar())
    {
        if(z == '\n' || z == '\0')
        {
            break;
        }
        else
        {
            level[0] = z;
        }
    }
    z = 0;
    printf("Write data:\n");
    while(z = getchar())
    {
        if(z == '\n' || z == '\0')
        {
            break;
        }
        else
        {
            word[i] = z;
            i++;
            if(i >= 49){
                break;
            }
        }
    }
    openDatabase();
    insertData(level, word);
    closeDatabase();
}

void automaticMode(void)
{
    openDatabase();
    for(int i = 0; i < 10; i++)
    {
        char level[] = {'1'};
        char data[10];
        sprintf(data, "%d", i);
        insertData(level, data);
        sleep(1);
    }
    closeDatabase();
}