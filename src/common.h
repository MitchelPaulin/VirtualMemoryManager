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

#endif