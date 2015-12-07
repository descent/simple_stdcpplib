#include "myiostream.h"

#include "k_stdio.h"

DS::ofstream& DS::ofstream::operator<<(char c)
{
}

DS::ofstream& DS::ofstream::operator<<(const char *str)
{
  myprint(str);
  return *this;
}

DS::ofstream& DS::ofstream::operator<<(int num)
{
  myprint(num);
  return *this;
}

DS::ofstream& DS::ofstream::operator<<(double num)
{
  myprint_float(num);
  return *this;
}

namespace DS
{
  const char *endl="\r\n";

  ofstream cout;
}
