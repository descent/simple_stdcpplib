#include <ncurses.h>
#include <locale.h>
#include <string>

#include "gdeque.h"
#include "cstring.h"

using namespace std;
using namespace DS;


int main()
{

#if 0
  CString cstr;

  cstr.init("abc");
  cstr.print();
  printf("\n");

  Deque<CString> deque;
  deque.init();

  deque.push_back(cstr);

  CString ps;
  ps = "102";

  cstr.init("def");
  deque.push_back(cstr);

  deque.print();
  deque.back(0, ps);
  ps.print();
  printf("\n");
#endif

#if 1
  setlocale(LC_ALL, "");

  initscr();
  keypad(stdscr,true);
  curs_set(0);
  // KEY_UP
  // KEY_DOWN

  //Deque<string> deque;
  Deque<CString> deque;

  deque.init();

  move(0,0);
  int fail_time=1;
  while(1)
  {
    char str[128];
    getstr(str);
    move(0,0);
    //std::string s(str);
    CString s;
    s.init(str);
    if (deque.push_back(s) == false)
    {
      mvprintw(20, 0, "push back fail ## %d", fail_time++);
      deque.pop_front();
      deque.push_back(s);
    }

    deque.print();

    int index=0;
    noecho();
    //string ps;
    CString ps;
    while(1)
    {
      mvprintw(17, 0, "index: %d", index);
      refresh();
      int ch = getch();
      switch(ch)
      {
        case KEY_UP:
        {
          ++index;
          if (deque.back(index, ps) == true)
          {
            mvprintw(0, 15, "%s", ps.c_str());
          }
          else
            --index;
          break;
        }
        case KEY_DOWN:
        {
          --index;
          if (deque.back(index, ps) == true)
          {
            mvprintw(0, 15, "%s", ps.c_str());
          }
          else
          {
            //mvprintw(17, 5, "back fail");
            ++index;
          }
          break;
        }
        case 'q':
        {
          goto end;
        }
        default:
        {
          ungetch(ch);
          move(0, 0);
          goto outer;
          break;
        }
      }
      mvprintw(17, 0, "index: %d", index);
      refresh();
    }
    outer:
    echo();
  }
end:
  endwin();
#endif
  return 0;
}
