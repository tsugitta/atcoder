// https://atcoder.jp/contests/abc075/tasks/abc075_d

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
  ll N, K;
  cin >> N >> K;

  struct Point {
    ll x;
    ll y;
  };

  V<Point> ps(N);

  rep(i, N) {
    ll x, y;
    cin >> x >> y;
    ps[i] = {x, y};
  }

  VL xs(N);
  VL ys(N);

  rep(i, N) {
    xs[i] = ps[i].x;
    ys[i] = ps[i].y;
  }

  sort(all(xs));
  sort(all(ys));

  ll res = numeric_limits<ll>::max();

  rep(right_i, N) rep(left_i, right_i) rep(top_i, N) rep(bottom_i, top_i) {
    ll left = xs[left_i];
    ll right = xs[right_i];
    ll top = ys[top_i];
    ll bottom = ys[bottom_i];

    ll ct = 0;

    for (auto p : ps) {
      unless(left <= p.x && p.x <= right) continue;
      unless(bottom <= p.y && p.y <= top) continue;
      ct++;
    }

    if (ct >= K) chmin(res, (right - left) * (top - bottom));
  }

  cout << res << endl;
}

// 累積和
void solve2() {
  ll N, K;
  cin >> N >> K;

  struct Point {
    ll x;
    ll y;
  };

  V<Point> ps(N);

  rep(i, N) {
    ll x, y;
    cin >> x >> y;
    ps[i] = {x, y};
  }

  VL xs(N);
  VL ys(N);

  rep(i, N) {
    xs[i] = ps[i].x;
    ys[i] = ps[i].y;
  }

  sort(all(xs));
  sort(all(ys));

  VVL acc(N + 1, VL(N + 1));  // acc[x][y]: x, y 未満の数

  rep(right_i, N) rep(top_i, N) {
    ll right = xs[right_i];
    ll top = ys[top_i];

    ll ct = 0;
    for (auto p : ps) {
      if (p.x <= right && p.y <= top) ct++;
    }

    acc[right_i + 1][top_i + 1] = ct;
  }

  ll res = numeric_limits<ll>::max();

  rep(right_i, N) rep(left_i, right_i) rep(top_i, N) rep(bottom_i, top_i) {
    ll ct = acc[right_i + 1][top_i + 1] - acc[left_i][top_i + 1] -
            acc[right_i + 1][bottom_i] + acc[left_i][bottom_i];
    unless(ct >= K) continue;

    ll left = xs[left_i];
    ll right = xs[right_i];
    ll top = ys[top_i];
    ll bottom = ys[bottom_i];

    if (ct >= K) chmin(res, (right - left) * (top - bottom));
  }

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
