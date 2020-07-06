#ifndef MAIN
#define MAIN

void solve();

struct exit_exception : public std::exception {
  const char* what() const throw() { return "Exited"; }
};

#endif
