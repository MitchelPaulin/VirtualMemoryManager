#ifndef TLB_H
#define TLB_H

#include "common.h"
#include <stdbool.h>

struct tlbEntry
{
    unsigned int pageNumber;
    unsigned int frameNumber;
    struct tlbEntry *next;
};

/*
    Initialize the TLB 
    Must be called before any accessor methods are called
    Returns true upon successful initialization
*/
bool initTlb();

/*
    Determine if a page exists in the TLB table
    If it exists return the frame number, else return the SENTINEL value 
*/
unsigned int getFrameFromTLB(unsigned int pageNumber);

/*
    Insert a value into the TLB using the FIFO replacement algorithim
*/
void insertIntoTLB(unsigned int pageNumber, unsigned int frameNumber);

/*
    Remove a page from the TLB
*/
void invalidatePageTLB(unsigned int pageNumber);

/*
    Deallocate the TLB resources
*/
void freeTLB();

/*
    Print out the TLB, used for debugging
*/
void printTLB();

#endif