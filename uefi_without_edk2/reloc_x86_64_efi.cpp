/*
 * reloc_x86_64.c - position independent x86_64 ELF shared object relocator
 * Copyright (C) 1999 Hewlett-Packard Co.
 * Contributed by David Mosberger <davidm@hpl.hp.com>.
 * Copyright (C) 2005 Intel Co.
 * Contributed by Fenghua Yu <fenghua.yu@intel.com>.
 *
 * All rights reserved.
 *
 * SPDX-License-Identifier:	BSD-3-Clause
 */

//#include <common.h>
#include "types.h"
#include "efi.h"
#include "efi_api_cpp.h"
#include "elf.h"

#if 0
#define PRINT_NUM_MSG(msg) \
  PRINT(L"\r\n")
  PRINT(msg) \
  PRINT(": ") \
  print_num(sys_table, msg); \
  PRINT(L"\r\n");
#endif

#ifdef __cplusplus
extern "C" efi_status_t _relocate(long ldbase, Elf64_Dyn *dyn, efi_handle_t image, struct efi_system_table *sys_table);
#endif


// sizeof long : 8
efi_status_t _relocate(long ldbase, Elf64_Dyn *dyn, efi_handle_t image,
		       struct efi_system_table *sys_table)
{
	long relsz = 0, relent = 0;
	Elf64_Rel *rel = 0;
	unsigned long *addr;
  //int i=sizeof(long);
  int i=ldbase;
  u8 str[20]={0};
  u16 u16_str[20]={0};


#if 0
// read register value
// https://stackoverflow.com/questions/2114163/reading-a-register-value-into-a-c-variable
  u64 reg;
  asm("\t movl %%rip,%0" : "=r"(reg));
  
  s32_itoa(i, &str, 16);
  for (int i=0 ; str[i] ; ++i)
    u16_str[i]=str[i];
  
  PRINT(L"abc\r\n");
  PRINT(u16_str);
  PRINT(L"\r\n");
  #endif

	for (i = 0; dyn[i].d_tag != DT_NULL; ++i) {
          #if 0
          PRINT(L"\r\ndyn[i].d_tag: ");
          print_num(sys_table, dyn[i].d_tag);
          PRINT(L"\r\n");
          #endif
		switch (dyn[i].d_tag) {
		case DT_RELA:
			rel = (Elf64_Rel *)
				((unsigned long)dyn[i].d_un.d_ptr + ldbase);
			break;
		case DT_RELASZ:
			relsz = dyn[i].d_un.d_val;
			break;
		case DT_RELAENT:
			relent = dyn[i].d_un.d_val;
			break;
		default:
			break;
		}
	}
  #if 0
  PRINT(L"\r\nldbase: ");
  print_num(sys_table, ldbase);
  PRINT(L"\r\n");

  PRINT(L"\r\ndyn: ");
  print_num(sys_table, dyn);
  PRINT(L"\r\n");

  PRINT(L"\r\nrel: ");
  print_num(sys_table, rel);
  PRINT(L"\r\n");

  PRINT(L"\r\nrelsz: ");
  print_num(sys_table, relsz);
  PRINT(L"\r\n");

  PRINT(L"\r\nrelent: ");
  print_num(sys_table, relent);
  PRINT(L"\r\n");
  #endif

	if (!rel && relent == 0)
		return EFI_SUCCESS;

	if (!rel || relent == 0)
		return EFI_LOAD_ERROR;

	while (relsz > 0) {
		/* apply the relocs */
		switch (ELF64_R_TYPE(rel->r_info)) {
		case R_X86_64_NONE:
			break;
		case R_X86_64_RELATIVE:
			addr = (unsigned long *)(ldbase + rel->r_offset);
			*addr += ldbase;
			break;
		default:
			break;
		}
		rel = (Elf64_Rel *)((char *)rel + relent);
		relsz -= relent;
	}

	return EFI_SUCCESS;
}
