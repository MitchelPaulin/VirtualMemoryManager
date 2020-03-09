#include "constants.h"

unsigned int pageTable[PAGE_SIZE];

void initPageTable()
{
    for (int i = 0; i < PAGE_SIZE; i++)
    {
        pageTable[i] = SENTINEL;
    }
}

unsigned int getFramePageTable(unsigned int pageNumber)
{
    return pageTable[pageNumber];
}

void insertIntoPageTable(unsigned int pageNumber, unsigned int frameNumber)
{
    pageTable[pageNumber] = frameNumber;
}