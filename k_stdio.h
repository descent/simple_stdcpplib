#ifndef K_STDIO_H
#define K_STDIO_H

#include "type.h"
#include "mydeque.h"

void myprint(const char *str);
void myprint(int num);
void send_byte(u8 b);
int ungetch(int c);
int getchar();

extern MyDeque mydeque;

#endif
