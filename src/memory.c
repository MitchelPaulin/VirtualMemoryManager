#include "memory.h"
#include "stdio.h"
#include "stdlib.h"

char physicalMemory[FRAMES * PAGE_SIZE] = {};

/*
    Points to the current free frame, once this is greater than the number of frames
    we need to start using a replacement algorithim
*/
int freeFramePointer = -1;

FILE *fp;

bool initMemory()
{
    fp = fopen("../backingStore/BACKING_STORE.bin", "rb");

    if (fp == NULL)
    {
        printf("Could not open the backing store\n");
        exit(0);
    }

    return true;
}

char getValueAtPhysicalAddress(int address)
{
    return physicalMemory[address];
}

int loadValueFromBackingStore(int frameNumber)
{
    if (freeFramePointer < FRAMES)
    {
        //requested a page that is not yet in memory
        freeFramePointer++;
        fseek(fp, frameNumber * PAGE_SIZE, 0);
        fread(&physicalMemory[freeFramePointer * PAGE_SIZE], sizeof(PAGE_SIZE), 1, fp);
        return freeFramePointer;
    }
    else
    {
        //implement page replacement algo here
    }
}