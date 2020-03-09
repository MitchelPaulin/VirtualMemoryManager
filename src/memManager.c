#include <stdlib.h>
#include <stdio.h>
#include "common.h"
#include "tlb.h"
#include "pageTable.h"
#include "memory.h"
#include "constants.h"

unsigned int getAddress(unsigned int virtualAddress);

//keep track of metrics
int pageFaults = 0;
int addressesTranslated = 0;
int TLBHits = 0;

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

    //Translate each address in the file
    char line[256];
    while (fgets(line, sizeof(line), fp))
    {
        unsigned int mem = atoi(line);
        unsigned int addr = getAddress(mem);
        char result = getValueAtPhysicalAddress(addr);
        printf("Virtual address: %u Physical address: %u Value: %d\n", mem, addr, result);
        addressesTranslated++;
    }

    //Report some statistics
    printf("Number of Translated Addresses = %d\n", addressesTranslated);
    printf("Page Faults = %d\n", pageFaults);
    if (pageFaults > 0)
    {
        printf("Page Fault Rate = %lf\n", (double)pageFaults / (double)addressesTranslated);
    }
    printf("TLB Hits = %d\n", TLBHits);
    printf("TLB Hit Rate = %lf\n", (double)TLBHits / (double)addressesTranslated);

    fclose(fp);

    return 0;
}

/*
    Attempts to get the physical address from a virtual one by 
    1. Consulting the TLB 
    2. Consulting the PageTable
    3. If both fail, request data be read into memory

    Returns the address of the requested virtual address in physical memory
*/
unsigned int getAddress(unsigned int virtualAddress)
{
    const unsigned int pageNumber = getPageNumber(virtualAddress);
    const unsigned int pageOffset = getPageOffset(virtualAddress);

    // first consult the TLB
    int frame = getFrameFromTLB(pageNumber);
    if (frame != SENTINEL)
    {
        TLBHits++;
        goto TLB_HIT;
    }

    // if a TLB miss occurs, consult page table
    frame = getFramePageTable(pageNumber);
    if (frame != SENTINEL)
    {
        goto PAGE_HIT;
    }

    //miss on tlb and page table, page fault occured
    pageFaults++;
    goto PAGE_FAULT;

PAGE_FAULT:
    //page table miss, value not in memory, request physical memory to load value
    frame = loadValueFromBackingStore(pageNumber);

    //update page table with new frame
    insertIntoPageTable(pageNumber, frame);

PAGE_HIT:
    insertIntoTLB(pageNumber, frame);

TLB_HIT:
    return frame * PAGE_SIZE + pageOffset;
}