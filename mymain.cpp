#include "s_eval.h"
#include "gdeque.h"

using namespace DS;

int mymain()
{ 
  //mydeque.init();
  init_eval();
  Environment *global_env = get_env(0, "global");
  create_primitive_procedure(global_env);
  non_os_repl("simple scheme> ", global_env);
  return 0;
}
