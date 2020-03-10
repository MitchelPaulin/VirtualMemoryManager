#include "constants.h"
#include <stdlib.h>
#include <stdio.h>

/*
    Implementation of a page table using the FIFO replacement policy 
    To this end the implementation will use a linked list
*/

unsigned int pageTable[PAGE_SIZE];

struct pageNumberEntry
{
    unsigned int pageNumber;
    struct pageNumberEntry *next;
};

struct pageNumberEntry *pageHead;
struct pageNumberEntry *pageTail;

void initPageTable()
{
    for (int i = 0; i < PAGE_SIZE; i++)
    {
        pageTable[i] = SENTINEL;
    }

    pageHead = (struct pageNumberEntry *)malloc(sizeof(struct pageNumberEntry));
    pageTail = pageHead;
}

unsigned int getFramePageTable(unsigned int pageNumber)
{
    return pageTable[pageNumber];
}

unsigned int popPageQueue()
{
    if (pageHead)
    {
        unsigned int invalidPage = pageHead->pageNumber;
        struct pageNumberEntry *temp = pageHead;
        pageHead = pageHead->next;
        free(temp);
        // Invalidate page
        pageTable[invalidPage] = SENTINEL;
        return invalidPage;
    }
    return SENTINEL;
}

void insertIntoPageTable(unsigned int pageNumber, unsigned int frameNumber)
{
    pageTable[pageNumber] = frameNumber;
    pageTail->pageNumber = pageNumber;
    pageTail->next = (struct pageNumberEntry *)malloc(sizeof(struct pageNumberEntry));
    pageTail = pageTail->next;
    pageTail->pageNumber = SENTINEL;
}

void printPageQueue()
{
    struct pageNumberEntry *temp = pageHead;
    while (temp)
    {
        printf("%u, ", temp->pageNumber);
        temp = temp->next;
    }
    printf("\n");
}

void freePageTable()
{
    struct pageNumberEntry *temp;
    while (pageHead != pageTail)
    {
        temp = pageHead;
        pageHead = pageHead->next;
        free(temp);
    }
    free(pageTail);
}