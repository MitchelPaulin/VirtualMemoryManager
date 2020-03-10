#include "memory.h"
#include "stdio.h"
#include "stdlib.h"
#include "common.h"

char physicalMemory[FRAMES * PAGE_SIZE] = {};

/*
    Points to the current free frame, once this is greater than the number of frames
    we need to start using a replacement algorithim
*/
unsigned int freeFramePointer = 0;

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

char getValueAtPhysicalAddress(unsigned int address)
{
    return physicalMemory[address];
}

unsigned int loadValueFromBackingStore(unsigned int frameNumber)
{

    /*
        Here we use a simple policy to decide what frame should be overwritten 
        Just loop around and start from frame zero

        Note in real memory we would need some kind of table to keep track of free frames
    */

    unsigned int circularFreeFramePointer = freeFramePointer;

    if (freeFramePointer > FRAMES)
    {
        frameOverwritten = 1;
    }
    else
    {
        frameOverwritten = 0;
    }

    circularFreeFramePointer = freeFramePointer % FRAMES;

    fseek(fp, frameNumber * PAGE_SIZE, SEEK_SET);
    for (int i = 0; i < PAGE_SIZE; i++)
    {
        fread(&physicalMemory[circularFreeFramePointer * PAGE_SIZE + i], sizeof(char), 1, fp);
    }
    freeFramePointer++;
    return circularFreeFramePointer;
}