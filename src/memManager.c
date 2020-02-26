#include <stdlib.h>
#include <stdio.h>
#include "common.h"
#include "tlb.h"
#include "page.h"

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

    // Allocate resources
    initTlb();
    initPageTable();

    char line[256];
    while (fgets(line, sizeof(line), fp))
    {
        unsigned int mem = atoi(line);
        printf("%d %d ", mem, getPageNumber(mem));
        printf("%d\n", getPageOffset(mem));
    }

    fclose(fp);

    return 0;
}

unsigned int getPhysicalAddress(unsigned int virtualAddress)
{
    return 0; 
}