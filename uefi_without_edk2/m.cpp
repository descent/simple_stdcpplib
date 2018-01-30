#include "efi.h"
#include "efi_api_cpp.h"


#ifdef __cplusplus
extern "C" efi_status_t efi_main(efi_handle_t image, struct efi_system_table *sys_table);
extern "C" void enter_main();
#endif

efi_status_t efi_main(efi_handle_t image, struct efi_system_table *sys_table)
{
  sys_table->con_out->output_string(sys_table->con_out, (efi_string_t)L"\r\nhello simple c++ lib\n\r");
  enter_main();
  return 0;
}
