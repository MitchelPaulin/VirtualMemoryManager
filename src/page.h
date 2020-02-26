#ifndef PAGE_H
#define PAGE_H
/*
    Init the page table 
    Put some dummy values in there so there is something to retrieve
*/
void initPageTable();

/*
    Lookup the frame number in the page table
    Return the frame if it is found
*/
int getFrameNumber(unsigned pageNumber);
#endif