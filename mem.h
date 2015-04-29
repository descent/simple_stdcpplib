#ifndef MEM_H
#define MEM_H

typedef unsigned int u32;

void *mymalloc(u32 size);
void myfree(void *ptr);

#endif
