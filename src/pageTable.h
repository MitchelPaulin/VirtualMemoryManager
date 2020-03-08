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
int getFramePageTable(unsigned pageNumber);
#endif