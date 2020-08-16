#include <yaml-cpp/yaml.h>

#include "iostream"
#include "main.h"
#include "map"
using namespace std;

struct test_case {
  string in;
  string out;
};

vector<test_case> load_cases() {
  vector<test_case> cases;

  try {
    YAML::Node yaml_cases = YAML::LoadFile("./test.yaml");

    for (size_t i = 0; i < yaml_cases.size(); i++) {
      YAML::Node c = yaml_cases[i];
      cases.push_back({c["in"].as<string>(), c["out"].as<string>()});
    }
  } catch (YAML::Exception &e) {
    cerr << "YAML load error: " << e.what() << endl;
    exit(1);
  }

  return cases;
}

int main() {
  auto cases = load_cases();

  map<string, function<void(void)>> function_map = {
      {"solve", solve},
  };

  bool passed = true;

  for (auto [solve_func_name, solve_func] : function_map) {
    cout << "----- " << solve_func_name << " -----" << endl;

    for (size_t i = 0; i < cases.size(); i++) {
      auto c = cases[i];

      stringbuf in = stringbuf(c.in);
      streambuf *cinbuf = cin.rdbuf();
      cin.rdbuf(&in);

      stringbuf out;
      streambuf *coutbuf = cout.rdbuf();
      cout.rdbuf(&out);

      try {
        solve_func();
      } catch (exit_exception &e) {
      }

      cin.rdbuf(cinbuf);
      cout.rdbuf(coutbuf);

      if (c.out != out.str()) {
        cout << "--- CASE " << i << " ---" << endl;

        cout << "[EXP] \n"
             << c.out << "\n[ACT] \n"
             << out.str() << "\n"
             << endl;
        passed = false;
      }
    }

    if (passed) {
      cout << " PASS" << endl;
    }
  }

  return 0;
}
