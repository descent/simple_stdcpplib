#include "myiostream.h"
#include "mystring.h"
#include "myvec.h"

#if 0
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
#endif

namespace DS
{
  //const char *endl="\r\n";

  ofstream cout;
  ofstream cout1(1);
  ofstream cout2(2);
}

DS::ofstream& DS::ofstream::operator<<(char c)
{
  putchar(c);
  return *this;
}

DS::ofstream& DS::ofstream::operator<<(const char *str)
{
#ifdef TEST
  printf(str);
#else
  myprint(str);
#endif
  return *this;
}

DS::ofstream& DS::ofstream::operator<<(unsigned int num)
{
  int radix=10;
  u8 str[10];

  switch (basefield_)
  {
    case HEX:
    {
      //myprint("hex\r\n");
      radix=16;
      break;
    }
    case OCT:
    {
      //myprint(num, 8);
      radix=8;
      break;
    }
    case DEC:
    {
    }
    default:
    {
      //myprint("dec\r\n");
      //myprint(num);
      radix=10;
      break;
    }
  }

  s32_itoa(num, str, radix);
#ifdef TEST
#else
  myprint((char*)str);
#endif

  return *this;
}

DS::ofstream& DS::ofstream::operator<<(long n)
{
  DS::myprint("long version\n");
  DS::myprint(n);
  return *this;
}

DS::ofstream& DS::ofstream::operator<<(unsigned long n)
{
  DS::myprint("unsigned long version\n");
  DS::myprint(n);
  return *this;
}

DS::ofstream& DS::ofstream::operator<<(int num)
{
  switch (basefield_)
  {
    case HEX:
    {
#ifdef TEST
#else
      //myprint("hex\r\n");
      myprint(num, 16);
#endif
      break;
    }
    case OCT:
    {
#ifdef TEST
#else
      myprint(num, 8);
#endif
      break;
    }
    case DEC:
    {
    }
    default:
    {
      //myprint("dec\r\n");
#ifdef TEST
#else
      myprint(num);
#endif
      break;
    }
  }
  return *this;
}

DS::ofstream& DS::ofstream::operator<<(double num)
{
#ifdef TEST
#else
  myprint_float(num);
#endif
  return *this;
}

DS::ofstream& DS::ofstream::operator<<(const DS::string& str)
{
#ifdef TEST
#else
  myprint(str.c_str());
#endif
  return *this;
}

DS::ofstream& DS::ofstream::operator<<(u32 *ptr)
{
  u32 num = (u32)ptr;
  return operator<<(num);
}

DS::ofstream& DS::ofstream::operator<<(s32 *ptr)
{
  s32 num = (s32)ptr;
  return operator<<(num);
}

#ifdef TEST
int main(int argc, char *argv[])
{
  DS::cout << "abc" << DS::endl;  
  return 0;
}
#endif
