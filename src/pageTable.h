#ifndef PAGE_TABLE_H
#define PAGE_TABLE_H
/*
    Init the page table to sentinel values
*/
void initPageTable();

/*
    Lookup the frame number in the page table
    Return the frame if it is found
*/
int getFramePageTable(unsigned int pageNumber);

/*
    Place a pageNumber, frameNumber pair into the page table
*/
void insertIntoPageTable(unsigned int pageNumber, unsigned int frameNumber);

/*
    Pop the first page from the FIFO queue and invalidate the page table value
    Return the page number that was popped or SENTINEL if no page could be popped
*/
unsigned int popPageQueue();

/*
    Print the page queue, used for debugging
*/
void printPageQueue();

/*
    Free all resources allocated for the page table
*/
void freePageTable();

#endif