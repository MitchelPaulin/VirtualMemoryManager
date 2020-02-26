#include "common.h"

unsigned int getPageNumber(unsigned int virtualAddress)
{
    return (virtualAddress & PAGE_MASK) >> 8;
}
unsigned int getPageOffset(unsigned int virtualAddress)
{
    return virtualAddress & OFFSET_MASK;
}