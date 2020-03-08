#include "tlb.h"
#include "constants.h"
#include <stdlib.h>

/*
    Implementation of a TLB suing the FIFO replacement policy 
    To this end the implementation will use a linked list
*/

struct tlbEntry *tlbEntries[TLB_SIZE] = {};
bool initialized = false;

bool initTlb()
{
    /*
        Protect against multiple initialization
    */
    if (initialized)
    {
        return false;
    }

    initialized = true;

    for (int i = 0; i < TLB_SIZE; i++)
    {
        tlbEntries[i] = (struct tlbEntry *)malloc(sizeof(struct tlbEntry));
        tlbEntries[i]->frameNumber = SENTINEL;
        tlbEntries[i]->pageNumber = SENTINEL;
    }

    return true;
}

int getFrameTLB(unsigned int pageNumber)
{
    for (int i = 0; i < TLB_SIZE; i++)
    {
        if (tlbEntries[i]->pageNumber == pageNumber)
        {
            //tlb hit
            return tlbEntries[i]->frameNumber;
        }
    }
    //tlb miss
    return SENTINEL;
}

void insertIntoTLB(unsigned int pageNumber, unsigned int frameNumber)
{
    //Implement some clever FIFO thing here, for now just look for empty spot
}