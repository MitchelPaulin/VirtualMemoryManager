#include <stdlib.h>
#include <stdio.h>
#include "common.h"
#include "tlb.h"
#include "pageTable.h"
#include "memory.h"
#include "constants.h"

unsigned int getAddress(unsigned int virtualAddress);

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
    initMemory();

    char line[256];
    while (fgets(line, sizeof(line), fp))
    {
        unsigned int mem = atoi(line);
        unsigned int addr = getAddress(mem);
        char result = getValueAtPhysicalAddress(addr);
        printf("Virtual address: %u Physical address: %u Value: %u\n", mem, addr, result);
    }

    fclose(fp);

    return 0;
}

unsigned int getAddress(unsigned int virtualAddress)
{
    const unsigned int pageNumber = getPageNumber(virtualAddress);
    const unsigned int pageOffset = getPageOffset(virtualAddress);

    // first consult the TLB (TO BE DONE)

    // if a TLB miss occurs, consult page table
    int frame = getFramePageTable(pageNumber);
    if (frame != SENTINEL)
    {
        //page hit, return value from physical memory
        return frame * PAGE_SIZE + pageOffset;
    }
    else
    {
        //page table miss, value not in memory, request physical memory to load value
        frame = loadValueFromBackingStore(pageNumber);
        //update page table with new frame
        insertIntoPageTable(pageNumber, frame);
        //now that the value is in memory we may access it
        return frame * PAGE_SIZE + pageOffset;
    }

    // if a page fault occurs the page we want is not in memory
    // we load the file from the backing store into memory, update the page table, update the TLB

    return 0;
}