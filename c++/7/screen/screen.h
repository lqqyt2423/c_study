#ifndef SCREEN_H
#define SCREEN_H

#include <string>
#include <vector>
#include <iostream>

class Screen {
public:
  typedef std::string::size_type pos;
  Screen() = default;
  Screen(pos ht, pos wd, char c): height(ht), width(wd),
    contents(ht*wd, c) {}
  char get() const { return contents[cursor]; }
  inline char get(pos ht, pos wd) const;
  Screen &move(pos r, pos c);
  void some_member() const;
  Screen &set(char);
  Screen &set(pos, pos, char);
  Screen &display(std::ostream &os) { do_display(os); return *this; }
  const Screen &display(std::ostream &os) const { do_display(os); return *this; }

 private:
  pos cursor = 0;
  pos height = 0, width = 0;
  std::string contents;
  mutable size_t access_ctr;
  void do_display(std::ostream &os) const {
    pos len = height * width;
    for (pos i = 0; i != len; i++) {
      os << contents[i];
      if ((i+1) % width == 0)
        os << '\n';
    }
    os << std::endl;
  }
};


// class Window_mgr {
// private:
//   // 默认情况下，一个window_mgr包含一个标准尺寸的空白screen
//   std::vector<Screen> screens{ Screen(24, 80, ' ') };
// };

#endif
