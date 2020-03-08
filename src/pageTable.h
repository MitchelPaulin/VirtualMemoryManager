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
void insertIntoPageTable(int pageNumber, int frameNumber);

#endif