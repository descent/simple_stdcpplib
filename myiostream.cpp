#include "myiostream.h"
#include "mystring.h"
#include "myvec.h"

#define DOBJS_SIZE 3

void *__dso_handle;

static DObjs dobjs[DOBJS_SIZE];
static int obj_count=0;

DS::vector<DObjs> dobjs_vec;

int ex_code;

void g_dtor()
{
#if 0
  for (int i=obj_count-1 ; i >= 0 ; --i)
    dobjs[i].dtor_(dobjs[i].arg_);
#endif

  for (int i=0 ; i < dobjs_vec.length() ; ++i)
  {
    dobjs_vec[i].dtor_(dobjs_vec[i].arg_);
  }
}

extern "C"
{
  int __cxa_atexit(void (*destructor) (void *), void *arg, void *__dso_handle)
  {
    DObjs dobj;

    dobj.dtor_ = destructor;
    dobj.arg_ = arg;
    dobj.dso_handle_ = __dso_handle;

    dobjs_vec.push_back(dobj);

    dobjs[obj_count].dtor_ = destructor;
    dobjs[obj_count].arg_ = arg;
    dobjs[obj_count].dso_handle_ = __dso_handle;
    DS::printf("fill ctor data: obj_count: %d, arg:%d\r\n", obj_count, arg);
    ++obj_count;
  }

  // ref: http://git.opencores.org/?a=viewblob&p=uClibc&h=ebb233b4fce33b04953f1d9158a0479487bb50db&f=libc/sysdeps/linux/arm/aeabi_atexit.c
  /* Register a function to be called by exit or when a shared library
     is unloaded.  This routine is like __cxa_atexit, but uses the
     calling sequence required by the ARM EABI.  */
  int __aeabi_atexit (void *arg, void (*func) (void *), void *d);
  int __aeabi_atexit (void *arg, void (*func) (void *), void *d)
  {
    return __cxa_atexit (func, arg, d);
  }
}

namespace DS
{
  //const char *endl="\r\n";

  ofstream cout;
  ofstream cout1(1);
  ofstream cout2(2);
}

DS::ofstream& DS::ofstream::operator<<(char c)
{
}

DS::ofstream& DS::ofstream::operator<<(const char *str)
{
  myprint(str);
  return *this;
}

DS::ofstream& DS::ofstream::operator<<(unsigned int num)
{
  // fixed me: it is unsigned int, but use signed int to print
  switch (basefield_)
  {
    case HEX:
    {
      //myprint("hex\r\n");
      myprint(num, 16);
      break;
    }
    case OCT:
    {
      myprint(num, 8);
      break;
    }
    case DEC:
    {
    }
    default:
    {
      //myprint("dec\r\n");
      myprint(num);
      break;
    }
  }
  return *this;
}

DS::ofstream& DS::ofstream::operator<<(int num)
{
  switch (basefield_)
  {
    case HEX:
    {
      //myprint("hex\r\n");
      myprint(num, 16);
      break;
    }
    case OCT:
    {
      myprint(num, 8);
      break;
    }
    case DEC:
    {
    }
    default:
    {
      //myprint("dec\r\n");
      myprint(num);
      break;
    }
  }
  return *this;
}

DS::ofstream& DS::ofstream::operator<<(double num)
{
  myprint_float(num);
  return *this;
}

DS::ofstream& DS::ofstream::operator<<(const DS::string& str)
{
  myprint(str.c_str());
  return *this;
}
