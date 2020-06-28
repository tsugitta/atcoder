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

  int failed = 0;

  map<string, function<void(void)>> function_map = {
      {"solve", solve},
      {"solve2", solve2},
  };

  for (auto it = function_map.begin(); it != function_map.end(); it++) {
    auto func_name = it->first;
    cout << "----- " << func_name << " -----" << endl;

    for (size_t i = 0; i < cases.size(); i++) {
      auto c = cases[i];

      stringbuf in = stringbuf(c.in);
      streambuf *cinbuf = cin.rdbuf();
      cin.rdbuf(&in);

      stringbuf out;
      streambuf *coutbuf = cout.rdbuf();
      cout.rdbuf(&out);

      try {
        it->second();
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
        failed = 1;
      }
    }

    if (!failed) {
      cout << " PASS" << endl;
    }
  }

  return 0;
}
