#include "constants.h"

int pageTable[PAGE_SIZE];

void initPageTable()
{
    for (int i = 0; i < PAGE_SIZE; i++)
    {
        pageTable[i] = SENTINEL;
    }
}

int getFramePageTable(unsigned int pageNumber)
{
    return pageTable[pageNumber];
}

void insertIntoPageTable(int pageNumber, int frameNumber)
{
    pageTable[pageNumber] = frameNumber;
}