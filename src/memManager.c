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
    if (addressesTranslated > 0)
    {
        printf("Page Faults = %d\n", pageFaults);
        printf("Page Fault Rate = %lf\n", (double)pageFaults / (double)addressesTranslated);
        printf("TLB Hits = %d\n", TLBHits);
        printf("TLB Hit Rate = %lf\n", (double)TLBHits / (double)addressesTranslated);
    }

    fclose(fp);
    freeTLB();
    freePageTable();

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
    unsigned int frame = getFrameFromTLB(pageNumber);
    if (frame == SENTINEL)
    {
        frame = getFramePageTable(pageNumber);
        if (frame == SENTINEL)
        {
            pageFaults++;
            frame = loadValueFromBackingStore(pageNumber);
            if (frameOverwritten == 1)
            {
                //most recent load caused a frame to be overwritten, clean page table and TLB
                unsigned int invalidPage = popPageQueue();
                invalidatePageTLB(invalidPage);
            }
            insertIntoPageTable(pageNumber, frame);
        }
        insertIntoTLB(pageNumber, frame);
    }
    else
    {
        TLBHits++;
    }
    return frame * PAGE_SIZE + pageOffset;
}