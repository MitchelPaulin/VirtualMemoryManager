#include <stdlib.h>
#include <stdio.h>
#include "constants.h"

unsigned int getPhysicalAddress(unsigned int virtualAddress);

int main(int argc, const char *argv[])
{

    if (argc != 2)
    {
        printf("Invalid number of arguments\n");
        exit(1);
    }

    const char *fileName = argv[1];
    FILE *fp = fopen(fileName, "r");

    char line[256];
    while (fgets(line, sizeof(line), fp))
    {
        int mem = atoi(line);
        printf("%d\n", mem);
    }

    fclose(fp);

    return 0;
}

unsigned int getPhysicalAddress(unsigned int virtualAddress)
{
    return 0; 
}