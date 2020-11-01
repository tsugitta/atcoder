// https://atcoder.jp/contests/abc181/tasks/abc181_f

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

void solve() {
  ll N;
  cin >> N;

  VL xs(N);
  VL ys(N);
  rep(i, N) cin >> xs[i] >> ys[i];

  // N: y = -100
  // N+1: y = 100
  dsu uf(N + 2);

  asc_pq<tuple<ld, ll, ll>> dists;

  rep(i, N) { dists.emplace(ys[i] + 100, i, N); }
  rep(i, N) { dists.emplace(100 - ys[i], i, N + 1); }
  dists.emplace(200, N, N + 1);

  rep(j, N) rep(i, j) {
    ld dx = xs[j] - xs[i];
    ld dy = ys[j] - ys[i];
    ld d = sqrtl(dx * dx + dy * dy);
    dists.emplace(d, i, j);
  }

  cout << fixed << setprecision(10);

  while (true) {
    auto [nd, i, j] = dists.top();
    dists.pop();

    uf.merge(i, j);
    if (uf.same(N, N + 1)) drop(nd / 2);
  }
}
