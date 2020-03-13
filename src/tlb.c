#include "tlb.h"
#include "constants.h"
#include <stdlib.h>
#include <stdio.h>

/*
    Implementation of a TLB using the FIFO replacement policy 
    To this end the implementation will use a linked list
*/

struct tlbEntry *tlbHead;
struct tlbEntry *tlbTail;
bool initialized = false;

int TLBSize = 0;

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

    //Create a linked list of TLB blocks
    tlbHead = (struct tlbEntry *)malloc(sizeof(struct tlbEntry));
    tlbTail = tlbHead;
    for (int i = 0; i < TLB_SIZE - 1; i++)
    {
        tlbTail->next = (struct tlbEntry *)malloc(sizeof(struct tlbEntry));
        tlbTail = tlbTail->next;
        tlbTail->frameNumber = SENTINEL;
        tlbTail->pageNumber = SENTINEL;
    }
    tlbTail->next = NULL;
    return true;
}

unsigned int getFrameFromTLB(unsigned int pageNumber)
{
    struct tlbEntry *temp = tlbHead;
    do
    {
        if (temp->pageNumber == pageNumber)
        {
            return temp->frameNumber;
        }
        temp = temp->next;
    } while (temp);
    //TLB miss
    return SENTINEL;
}

void insertIntoTLB(unsigned int pageNumber, unsigned int frameNumber)
{
    if (TLBSize < TLB_SIZE)
    {
        // There are still empty spots in the TLB, find a place to insert the value
        struct tlbEntry *temp = tlbHead;
        do
        {
            if (temp->pageNumber == SENTINEL)
            {
                temp->pageNumber = pageNumber;
                temp->frameNumber = frameNumber;
                break;
            }
            temp = temp->next;
        } while (temp);
        TLBSize++;
    }
    else
    {
        // TLB is full, pop from queue and create new TLB at the tlbHead
        struct tlbEntry *temp = tlbHead;
        tlbHead = tlbHead->next;
        free(temp);
        tlbTail->next = (struct tlbEntry *)malloc(sizeof(struct tlbEntry));
        tlbTail = tlbTail->next;
        tlbTail->frameNumber = frameNumber;
        tlbTail->pageNumber = pageNumber;
        tlbTail->next = NULL;
    }
}

void invalidatePageTLB(unsigned int p)
{
    struct tlbEntry *temp = tlbHead;
    while (temp)
    {
        if (temp->pageNumber == p)
        {
            temp->pageNumber = SENTINEL;
            temp->frameNumber = SENTINEL;
            TLBSize--; // Decrease size so we can insert a new value in this spot
            return;
        }
        temp = temp->next;
    }
}

void printTLB()
{
    struct tlbEntry *temp = tlbHead;
    while (temp)
    {
        printf("%u %u\n", temp->pageNumber, temp->frameNumber);
        temp = temp->next;
    }
}

void freeTLB()
{
    struct tlbEntry *temp;
    while (tlbHead->next)
    {
        temp = tlbHead;
        tlbHead = tlbHead->next;
        free(temp);
    }
    free(tlbHead);
    initialized = false;
}