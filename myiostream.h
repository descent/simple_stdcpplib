#ifndef MYIOSTREAM_H
#define MYIOSTREAM_H

namespace DS
{
  extern const char *endl;

  class ofstream
  {
    public:
      ofstream& operator<<(char c);
      ofstream& operator<<(const char *str);
      ofstream& operator<<(int num);
      ofstream& operator<<(double num);
    private:
  };


  extern ofstream cout;
}


#endif


