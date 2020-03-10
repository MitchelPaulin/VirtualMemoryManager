# VirtualMemoryManager
An implementation of a virtual memory manager in C as specified in Chapter 10 of Operating Systems Concepts Ed 10 (ISBN 9781119320913)

## Building

Run `make` from the top level folder

## Execution

From the `bin` directory run `./a.out ../addresses.txt`
 
## About

This project was intended to mimic how virtual memory is managed in an operating system. In this project I simulate a virtual memory space and a TLB both using a FIFO replacement policy. Memory is populated from `BACKING_STORE.bin` using a demand paging policy. This particular implementation also completes the bonus task of supporting a larger virtual space than physical space.

## Notes
If you would like a version of this project which does not complete the bonus objective, simply change the variable `FRAMES` in `constants.h` to 256 and everything will function normally.
