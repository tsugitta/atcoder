// https://atcoder.jp/contests/abc144/tasks/abc144_d

#include "algorithm"
#include "cmath"
#include "iomanip"
#include "iostream"
#include "queue"
#include "set"
#include "vector"
#define rep(i, to) for (ll i = 0; i < (to); ++i)
#define repf(i, from, to) for (ll i = from; i < (to); ++i)
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

const double PI = 3.14159265358979323846;

double to_deg(double r) { return r * 180 / PI; }

void solve() {
  ll a, b, x;
  cin >> a >> b >> x;

  double res;
  if (x >= a * a * b / 2) {
    res = to_deg(atan2(2 * a * a * b - 2 * x, a * a * a));
  } else {
    res = to_deg(atan2(a * b * b, 2 * x));
  }

  cout << fixed;  // setprecision
                  // が桁全体でなく小数点以下の桁数を指定するようになる
  cout << setprecision(10);
  cout << res << endl;
}

struct exit_exception : public std::exception {
  const char* what() const throw() { return "Exited"; }
};

#ifndef TEST
int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  try {
    solve();
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
