#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "main.h"
#include <logeris.h>

int main (int argc, char *argv[])
{
    printf("Program started\n");
    int opt;

    if(argc != 2)
    {
        printHelp();
        return 1;
    }

    while((opt = getopt(argc, argv, "hcipd")) != -1)
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
    printf("Used commands:\n"
            "-h help\n"
            "-c create database\n"
            "-i insert data\n"
            "-p print data\n"
            "-d delete DB\n");
}

void read_write_DB(void)
{
    char level[10];
    char word[50];

    printf("Write data level(1-INFO 2-WARNING 3-ERROR):\n");
    char z;     //Saugo viena chara
    char i = 0; //Saugo masyvo elemento numeri

    while(z = getchar())
    {
        if(z == '\n' || z == '\0')
        {
            break;
        }
        else
        {
            level[i] = z;
            i++;
        }
    }
    i = 0;
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
        }
    }
    //printf("Expected data: %s \n", word); //Testine
    insertData(level, word);

}