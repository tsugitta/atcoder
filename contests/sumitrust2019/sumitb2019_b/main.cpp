// https://atcoder.jp/contests/sumitrust2019/tasks/sumitb2019_b

#include "algorithm"
#include "cmath"
#include "functional"
#include "iomanip"
#include "iostream"
#include "numeric"
#include "queue"
#include "set"
#include "string"
#include "vector"
#define rep(i, to) for (ll i = 0; i < (to); ++i)
#define repf(i, from, to) for (ll i = from; i < (to); ++i)
#define repr(i, from) for (ll i = from - 1; i >= 0; --i)
#define all(vec) vec.begin(), vec.end()
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
  ll N;
  cin >> N;

  rep(num, N + 1) {
    double taxed = num * 1.08;
    if (floor(taxed) == N) drop(num);
  }

  drop(":(");
}

void solve2() {
  ll N;
  cin >> N;

  ll cand1 = floor(N / 1.08);
  ll cand2 = floor((N + 1) / 1.08);

  if (cand1 + cand1 * 8 / 100 == N) drop(cand1);
  if (cand2 + cand2 * 8 / 100 == N) drop(cand2);
  drop(":(");
}

void solve3() {
  ll N;
  cin >> N;

  double l = N / 1.08;
  double h = (N + 1) / 1.08;

  // l <= X < h なる整数があるか

  // l が整数か
  if (floor(l) == ceil(l)) drop(floor(l));

  // l < X <= h なる整数 X がある（l, h の整数部が異なる）かつ X != h か
  if (floor(l) != floor(h) && floor(h) != ceil(h)) {
    drop(floor(h));
  }

  drop(":(");
}

struct exit_exception : public std::exception {
  const char* what() const throw() { return "Exited"; }
};

#ifndef TEST
int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  try {
    solve3();
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
