// https://atcoder.jp/contests/abc175/tasks/abc175_e

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

ll dp[3000][3000][4];
ll val_mat[3000][3000];

void solve() {
  ll R, C, K;
  cin >> R >> C >> K;

  memset(dp, 0, sizeof(dp));
  memset(val_mat, 0, sizeof(val_mat));

  rep(i, K) {
    ll r, c, v;
    cin >> r >> c >> v;
    --r, --c;
    val_mat[r][c] = v;
  }

  rep(r, R) rep(c, C) rep(used, 4) rep(dir, 2) {
    ll nr = dir ? r + 1 : r;
    ll nc = dir ? c : c + 1;

    unless(nr < R && nc < C) continue;

    chmax(dp[nr][nc][r != nr ? 0 : used], dp[r][c][used]);

    if (used < 3) {
      chmax(dp[nr][nc][r != nr ? 0 : used + 1], dp[r][c][used] + val_mat[r][c]);
    }
  }

  ll res = 0;
  rep(i, 4)
      chmax(res, dp[R - 1][C - 1][i] + (i < 3 ? val_mat[R - 1][C - 1] : 0));

  cout << res << "\n";
}
