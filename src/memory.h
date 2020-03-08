#ifndef MEMORY_H
#define MEMORY_H

#include "constants.h"
#include <stdbool.h>

/*
    Get the value at the specified frameNumber and offset
*/
char getValueAtPhysicalAddress(int address);

/*
    Initialize memory
    Must be called before any accessor methods are called
    Returns true upon successful initialization
*/
bool initMemory();

/*
    If the frame is not currently in memory, load it from the backing store
    Returns the frame number it was loaded into
*/
int loadValueFromBackingStore(int frameNumber);


#endif