#ifndef CONSTANTS_H
#define CONSTANTS_H

#define PAGE_MASK   0b00000000000000001111111100000000
#define OFFSET_MASK 0b00000000000000000000000011111111
#define PAGE_TABLE_SIZE 256
#define PAGE_SIZE 256
#define TLB_SIZE 16
#define SENTINEL (unsigned int)-1

//Use 128 frames so the physical mem is half the size of virtual
//Change this to 256 to match the project for two students correct.txt file
#define FRAMES 128

#endif