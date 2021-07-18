// https://atcoder.jp/contests/abc210/tasks/abc210_d

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
#define rep(i, to) for (ll i = 0; i < ((ll)to); ++i)
#define rep1(i, to) for (ll i = 1; i <= ((ll)to); ++i)
#define repf(i, from, to) for (ll i = from; i < ((ll)to); ++i)
#define repr(i, from) for (ll i = from - 1; i >= 0; --i)
#define all(vec) vec.begin(), vec.end()
#define unless(cond) if (!(cond))
#define fi first
#define se second
#define i128 __int128_t
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
  ll H, W, C;
  cin >> H >> W >> C;

  VVL mat(H, VL(W));
  rep(h, H) rep(w, W) cin >> mat[h][w];

  ll res = INF;

  rep(_, 2) {
    // dp[h][w]: h, w 以前（h, w 含む）で建設した場合の最小値
    VVL dp(H, VL(W, INF));

    rep(h, H) rep(w, W) {
      // そのマス以前で建設する場合を先に処理
      if (h) chmin(dp[h][w], dp[h - 1][w] + C);
      if (w) chmin(dp[h][w], dp[h][w - 1] + C);
      chmin(res, dp[h][w] + mat[h][w]);

      // そのマスで初めて建設する場合は res の更新後に処理
      chmin(dp[h][w], mat[h][w]);
    }

    reverse(all(mat));
  }

  cout << res << "\n";
}
