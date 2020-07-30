// https://atcoder.jp/contests/abc130/tasks/abc130_f

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

void solve() {
  ll N;
  cin >> N;

  struct Pt {
    double x;
    double y;
    char d;
  };

  V<Pt> ps(N);

  const double MAX_POSITION = 1e9;

  rep(i, N) {
    double x, y;
    char d;
    cin >> x >> y >> d;
    // 0 以上にする
    x += 1e8;
    y += 1e8;

    ps[i] = {x, y, d};
  }

  map<char, char> rotate_map{
      {'U', 'R'},
      {'R', 'D'},
      {'D', 'L'},
      {'L', 'U'},
  };

  auto rotate = [&]() {
    rep(i, N) {
      auto p = ps[i];
      ps[i].x = p.y;
      ps[i].y = MAX_POSITION - p.x;
      ps[i].d = rotate_map[p.d];
    }
  };

  const double INF = 1e18;

  auto area = [&](double t) -> double {
    double top = -INF, right = -INF, bottom = INF, left = INF;

    for (auto p : ps) {
      double x = p.x;
      double y = p.y;
      if (p.d == 'R') x += t;
      if (p.d == 'U') y += t;
      if (p.d == 'D') y -= t;
      if (p.d == 'L') x -= t;
      chmax(top, y);
      chmax(right, x);
      chmin(bottom, y);
      chmin(left, x);
    }

    return (top - bottom) * (right - left);
  };

  V<double> ts;
  ts.push_back(0);

  // x_max が変わりうるタイミングは最右端の R, L, UD だけを見ればわかる
  auto retrieve_timings = [&]() {
    double r = -INF;
    double l = -INF;
    double ud = -INF;

    for (auto p : ps) {
      if (p.d == 'R')
        chmax(r, p.x);
      else if (p.d == 'L')
        chmax(l, p.x);
      else
        chmax(ud, p.x);
    }

    auto exists = [&](double a) -> bool { return a > -INF; };
    if (exists(r) && exists(l)) ts.push_back(abs(r - l) / 2);
    if (exists(r) && exists(ud)) ts.push_back(abs(r - ud));
    if (exists(l) && exists(ud)) ts.push_back(abs(l - ud));
  };

  rep(i, 4) {
    retrieve_timings();
    rotate();
  }

  double res = INF;
  for (auto t : ts) {
    chmin(res, area(t));
  }

  cout << fixed << setprecision(10) << res << endl;
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
