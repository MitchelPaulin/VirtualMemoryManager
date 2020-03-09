#include "tlb.h"
#include "constants.h"
#include <stdlib.h>

/*
    Implementation of a TLB suing the FIFO replacement policy 
    To this end the implementation will use a linked list
*/

struct tlbEntry *head;
struct tlbEntry *tail;
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
    head = (struct tlbEntry *)malloc(sizeof(struct tlbEntry));
    tail = head;
    for (int i = 0; i < TLB_SIZE - 1; i++)
    {
        tail->next = (struct tlbEntry *)malloc(sizeof(struct tlbEntry));
        tail = tail->next;
        tail->frameNumber = SENTINEL;
        tail->pageNumber = SENTINEL;
    }
    tail->next = NULL;
    return true;
}

unsigned int getFrameFromTLB(unsigned int pageNumber)
{
    struct tlbEntry *temp = head;
    do
    {
        if (temp->pageNumber == pageNumber)
        {
            return temp->frameNumber;
        }
        temp = temp->next;
    } while (temp);
    //tlb miss
    return SENTINEL;
}

void insertIntoTLB(unsigned int pageNumber, unsigned int frameNumber)
{
    if (TLBSize < TLB_SIZE)
    {
        //there are still empty spots in the TLB, find a place to insert the value
        struct tlbEntry *temp = head;
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
        //tlb is full, pop from queue and create new tlb at the head
        struct tlbEntry *temp = head;
        head = head->next;
        free(temp);
        tail->next = (struct tlbEntry *)malloc(sizeof(struct tlbEntry));
        tail = tail->next;
        tail->frameNumber = frameNumber;
        tail->pageNumber = pageNumber;
        tail->next = NULL;
    }
}

void freeTLB()
{
    struct tlbEntry *temp;
    while (head->next)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
    free(head);
    initialized = false;
}