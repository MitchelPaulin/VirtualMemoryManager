#include <stdlib.h>
#include <stdio.h>
#include "common.h"
#include "tlb.h"
#include "page.h"
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
    const unsigned int pageNumber = getPageNumber(virtualAddress);
    const unsigned int pageOffset = getPageOffset(virtualAddress); 

    // first consult the TLB (TO BE DONE)

    // if a TLB miss occurs, consult page table
    int frame = getFramePageTable(pageNumber);
    if (frame != SENTINEL)
    {
        //page hit, return value from physical memory

        return 1; 
    }

    // if a page fault occurs the page we want is not in memory 
    // we load the file from the backing store into memory, update the page table, update the TLB 

    return 0;
}