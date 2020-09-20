#include <yaml-cpp/yaml.h>

#include "iostream"
#include "main.h"
#include "map"
#include "random"
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

string get_random_case() {
  std::mt19937 mt{std::random_device{}()};

  std::uniform_int_distribution<int> dist(1, 100);

  int N = dist(mt);
  int X = dist(mt);
  int M = dist(mt);

  stringstream r;
  r << N << " " << X << " " << X + M << endl;

  return r.str();
}

void random_case_check() {
  for (int i = 0; i < 10; ++i) {
    string c = get_random_case();
    stringbuf in = stringbuf(c);
    streambuf *cinbuf = cin.rdbuf();
    cin.rdbuf(&in);

    stringbuf out;
    streambuf *coutbuf = cout.rdbuf();
    cout.rdbuf(&out);

    solve();

    cin.rdbuf(cinbuf);
    cout.rdbuf(coutbuf);

    stringbuf in2 = stringbuf(c);
    streambuf *cinbuf2 = cin.rdbuf();
    cin.rdbuf(&in2);

    stringbuf out2;
    streambuf *coutbuf2 = cout.rdbuf();
    cout.rdbuf(&out2);

    solve2();

    cin.rdbuf(cinbuf2);
    cout.rdbuf(coutbuf2);

    if (out2.str() != out.str()) {
      cout << "--MIS MATCH--" << endl;
      cout << "input" << endl;
      cout << c << endl;
      cout << "ok" << endl;
      cout << out.str() << endl;
      cout << "ng" << endl;
      cout << out2.str() << endl;
    }
  }
}

int main() {
  auto cases = load_cases();

  map<string, function<void(void)>> function_map = {
      {"solve", solve},
      {"solve2", solve2},
  };

  random_case_check();

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
