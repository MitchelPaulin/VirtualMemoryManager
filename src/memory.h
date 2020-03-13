#ifndef MEMORY_H
#define MEMORY_H

#include "constants.h"
#include <stdbool.h>

/*
    Get the value at the specified address
*/
char getValueAtPhysicalAddress(unsigned int address);

/*
    Initialize memory
    Must be called before any accessor methods are called
    Returns true upon successful initialization
*/
bool initMemory();

/*
    Free all resources allocated for main memory
*/
void freeMem();

/*
    If the frame is not currently in memory, load it from the backing store
    Returns the frame number it was loaded into
*/
unsigned int loadValueFromBackingStore(unsigned int frameNumber);


#endif