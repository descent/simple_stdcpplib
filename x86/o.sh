#!/bin/sh
# objdump for i8086
#objdump -m i8086 -dSCx start.o
objdump -m i8086 -DSCx start.o # -D dump all section
