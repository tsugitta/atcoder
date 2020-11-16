// https://atcoder.jp/contests/abc183/tasks/abc183_e

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

using mint = modint1000000007;

void solve() {
  ll H, W;
  cin >> H >> W;

  V<string> mat(H);
  rep(h, H) cin >> mat[h];

  VV<mint> dp(H, V<mint>(W));
  dp[0][0] = 1;

  VV<mint> acc_r(H, V<mint>(W));
  VV<mint> acc_b(H, V<mint>(W));
  VV<mint> acc_rb(H, V<mint>(W));

  rep(h, H) rep(w, W) {
    unless(mat[h][w] == '.') continue;

    if (w + 1 < W && mat[h][w + 1] == '.') {
      dp[h][w + 1] += dp[h][w] + acc_r[h][w];
      acc_r[h][w + 1] = dp[h][w] + acc_r[h][w];
    }

    if (h + 1 < H && mat[h + 1][w] == '.') {
      dp[h + 1][w] += dp[h][w] + acc_b[h][w];
      acc_b[h + 1][w] = dp[h][w] + acc_b[h][w];
    }

    if (h + 1 < H && w + 1 < W && mat[h + 1][w + 1] == '.') {
      dp[h + 1][w + 1] += dp[h][w] + acc_rb[h][w];
      acc_rb[h + 1][w + 1] = dp[h][w] + acc_rb[h][w];
    }
  }

  ll res = dp[H - 1][W - 1].val();
  cout << res << "\n";
}
