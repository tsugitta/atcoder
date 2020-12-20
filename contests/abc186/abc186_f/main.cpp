// https://atcoder.jp/contests/abc186/tasks/abc186_f

#include <atcoder/all>

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
using namespace atcoder;
using ll = long long;
using ld = long double;
template <typename T>
using V = vector<T>;
using VL = V<ll>;
template <typename T>
using VV = V<V<T>>;
using VVL = VV<ll>;
template <typename T>
using VVV = VV<V<T>>;
template <typename T, typename U>
using P = pair<T, U>;
using PL = P<ll, ll>;
using VPL = V<PL>;
template <typename T>
using asc_pq = priority_queue<T, V<T>, greater<T>>;

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

template <typename T>
inline ll len(V<T> arr) {
  return arr.size();
}

struct exit_exception : public std::exception {
  const char* what() const throw() { return "Exited"; }
};

template <typename T>
void drop(T res) {
  cout << res << endl;
  throw exit_exception();
}

const ll INF = 1e18;

void solve();

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

ll op(ll a, ll b) { return a + b; }
ll e() { return 0; }

void solve() {
  ll H, W, M;
  cin >> H >> W >> M;

  VL x_to_min_y(W, H - 1);
  VL y_to_min_x(H, W - 1);

  VVL y_to_xs(H, VL(0));

  rep(i, M) {
    ll x, y;
    cin >> y >> x;
    --x, --y;
    chmin(x_to_min_y[x], y - 1);
    chmin(y_to_min_x[y], x - 1);
    y_to_xs[y].push_back(x);
  }

  ll res = 0;

  ll first_right_max = y_to_min_x[0];
  ll first_bottom_max = x_to_min_y[0];

  // 0 手
  res++;

  // 1 手
  res += first_right_max;
  res += first_bottom_max;

  // 2 手
  {
    rep(w, first_right_max + 1) {
      if (w == 0) continue;
      res += x_to_min_y[w];
    }

    // 障害物のあった x が 1, なければ 0
    segtree<ll, op, e> x_has_obstacles(W);

    repf(w, first_right_max + 1, W) x_has_obstacles.set(w, 1);

    rep(h, first_bottom_max + 1) {
      if (h == 0) continue;

      res += x_has_obstacles.prod(0, y_to_min_x[h] + 1);
      for (ll x : y_to_xs[h]) x_has_obstacles.set(x, 1);
    }
  }

  cout << res << "\n";
}
