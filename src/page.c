#include "constants.h"

int pageTable[PAGE_SIZE];

void initPageTable()
{
    for (int i = 0; i < PAGE_SIZE; i++)
    {
        pageTable[i] = i;
    }
}

int getFrameNumber(unsigned pageNumber)
{
    return 0;
}