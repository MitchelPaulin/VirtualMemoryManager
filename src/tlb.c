#include "tlb.h"
#include "constants.h"
#include <stdlib.h>

#define SENTINEL -1

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

int pageExists(unsigned int pageNumber)
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