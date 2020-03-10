#ifndef COMMON_H
#define COMMON_H

/*
    Return the page number encoded in a virtual address
*/
unsigned int getPageNumber(unsigned int virtualAddress);

/*
    Return the page offset encoded in a virtual address
*/
unsigned int getPageOffset(unsigned int virtualAddress);

/*
    Set to 1 if a frame in the page table was overwritten 
    Set to 0 otherwise
*/
char frameOverwritten;

#endif