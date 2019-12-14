// https://atcoder.jp/contests/arc054/tasks/arc054_b

#include "algorithm"
#include "bitset"
#include "cmath"
#include "functional"
#include "iomanip"
#include "iostream"
#include "map"
#include "numeric"
#include "queue"
#include "set"
#include "string"
#include "vector"
#define rep(i, to) for (ll i = 0; i < (to); ++i)
#define rep1(i, to) for (ll i = 1; i <= (to); ++i)
#define repf(i, from, to) for (ll i = from; i < (to); ++i)
#define repr(i, from) for (ll i = from - 1; i >= 0; --i)
#define all(vec) vec.begin(), vec.end()
#define unless(cond) if (!(cond))
#define fi first
#define se second
using namespace std;
typedef long long ll;
template <typename T>
using V = vector<T>;
using VL = V<ll>;
using VVL = V<VL>;
template <typename T, typename U>
using P = pair<T, U>;
using PL = P<ll, ll>;
using VPL = V<PL>;
template <typename T>
inline bool chmax(T& a, T b);
template <typename T>
inline bool chmin(T& a, T b);
void print_ints(vector<ll> v);
template <typename T>
void drop(T a);

const ll INF = 1e18;

void solve() {
  double P;
  cin >> P;

  cout << fixed << setprecision(10);

  double x = (3.0 / 2) * log2((2.0 / 3) * P * log(2));
  if (x < 0) drop(P);

  double res = x + P * pow(2, -x / 1.5);
  cout << fixed << setprecision(10) << res << endl;
}

// 三分探索
void solve2() {
  double P;
  cin >> P;

  // 下に凸
  auto f = [&](double t) -> double { return t + P * pow(2, -t / 1.5); };

  double l = 0;
  double r = P + 1;

  while (r - l > 1e-8) {
    double ml = 2 * l / 3 + r / 3;
    double mr = l / 3 + 2 * r / 3;

    if (f(ml) < f(mr)) {
      r = mr;
    } else {
      l = ml;
    }
  }

  cout << fixed << setprecision(10) << f(r) << endl;
}

struct exit_exception : public std::exception {
  const char* what() const throw() { return "Exited"; }
};

#ifndef TEST
int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  try {
    solve2();
  } catch (exit_exception& e) {
  }

  return 0;
}
#endif

template <typename T>
inline bool chmax(T& a, T b) {
  if (a < b) {
    a = b;
    return 1;
  }
  return 0;
}

template <typename T>
inline bool chmin(T& a, T b) {
  if (a > b) {
    a = b;
    return 1;
  }
  return 0;
}

void print_ints(vector<ll> v) {
  rep(i, v.size()) {
    if (i > 0) {
      cout << " ";
    }

    cout << v[i];
  }

  cout << endl;
}

template <typename T>
void drop(T res) {
  cout << res << endl;
  throw exit_exception();
}
