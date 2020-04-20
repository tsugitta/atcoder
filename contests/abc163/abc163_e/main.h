#ifndef MAIN
#define MAIN

void solve();
void solve2();
void solve3();
void solve4();

struct exit_exception : public std::exception {
  const char* what() const throw() { return "Exited"; }
};

#endif
