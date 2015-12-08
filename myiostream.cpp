#include "myiostream.h"
#include "mystring.h"

#include "k_stdio.h"

namespace DS
{
  //const char *endl="\r\n";

  ofstream cout;
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
