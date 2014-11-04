#include <ncurses.h>
#include <locale.h>
#include <string>

using namespace std;

#include "gdeque.h"

int main()
{
  setlocale(LC_ALL, "");

  initscr();
  keypad(stdscr,true);
  curs_set(0);
  // KEY_UP
  // KEY_DOWN

  Deque<string> deque;

  deque.init();

  move(0,0);
  int fail_time=1;
  while(1)
  {
    char str[128];
    getstr(str);
    move(0,0);
    std::string s(str);
    if (deque.push_back(s) == false)
    {
      mvprintw(20, 0, "push back fail ## %d", fail_time++);
      deque.pop_front();
      deque.push_back(s);
    }

    deque.print();

    int index=0;
    noecho();
    while(1)
    {
      int ch = getch();
      switch(ch)
      {
        case KEY_UP:
        {
          string ps;
          if (deque.back(index, ps) == true)
          {
            ++index;
            mvprintw(0, 15, "%s", ps.c_str());
          }
          break;
        }
        case KEY_DOWN:
        {
          break;
        }
        default:
        {
          ungetch(ch);
          goto outer;
          break;
        }
      }
    }
    outer:
    echo();
  }

  endwin();
  return 0;
}
