CC=gcc
CXX=g++

CXXFLAGS=-Wall -O2 -nostdlib -nostartfiles -ffreestanding -fno-exceptions -fno-rtti  -g -nostdinc -I. -D__KERNEL__ -D__UBOOT__ -Wall -Wno-format-security -fno-builtin -ffreestanding -fshort-wchar -Os -fno-stack-protector -fno-delete-null-pointer-checks -g -fstack-usage -Wno-format-nonliteral -Werror=date-time -fno-strict-aliasing -fomit-frame-pointer -fno-toplevel-reorder -fno-dwarf2-cfi-asm -ffunction-sections -fvisibility=hidden -pipe -fpic -fshort-wchar

all : crt0_x86_64_efi.o reloc_x86_64_efi.o m.o

crt0_x86_64_efi.o: crt0_x86_64_efi.S  
	        $(CC) -nostdinc  -D__UBOOT__ -D__ASSEMBLY__ -g -fno-strict-aliasing -fomit-frame-pointer -fno-toplevel-reorder -fno-dwarf2-cfi-asm -D__I386__ -ffunction-sections -fvisibility=hidden -pipe -fpic -fshort-wchar   -c crt0_x86_64_efi.S


reloc_x86_64_efi.o: reloc_x86_64_efi.cpp
	$(CXX) $(CXXFLAGS) -c $<
m.o: m.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean :
	rm -f *.o
