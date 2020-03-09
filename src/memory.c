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
    
    /*
        Using modulo here is equivalent to a FIFO replacement approach
        This is because memory was filled in order
    */
    freeFramePointer++;
    freeFramePointer = freeFramePointer % FRAMES;


    fseek(fp, frameNumber * PAGE_SIZE, SEEK_SET);
    for (int i = 0; i < PAGE_SIZE; i++)
    {
        fread(&physicalMemory[freeFramePointer * PAGE_SIZE + i], sizeof(char), 1, fp);
    }
    return freeFramePointer;
}