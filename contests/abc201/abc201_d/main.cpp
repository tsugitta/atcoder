// https://atcoder.jp/contests/abc201/tasks/abc201_d

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
  ll H, W;
  cin >> H >> W;

  V<string> mat(H);
  rep(h, H) cin >> mat[h];

  // dp[h][w]: mat[h][w] にコマがある状態で先手が得られる得点差
  VVL dp(H, VL(W));
  rep(h, H) rep(w, W) { dp[h][w] = (h + w) % 2 == 0 ? -INF : INF; }
  dp[H - 1][W - 1] = 0;

  repr(h, H) repr(w, W) {
    // このマスに来る操作を行うのが先手か
    bool is_prev_first_move = (h + w) % 2 == 1;

    ll getting_score = mat[h][w] == '+' ? 1 : -1;
    if (!is_prev_first_move) getting_score *= -1;

    for (auto [nh, nw] : VPL{{h - 1, w}, {h, w - 1}}) {
      unless(nh >= 0 && nw >= 0) continue;

      if (is_prev_first_move) {
        chmax(dp[nh][nw], dp[h][w] + getting_score);
      } else {
        chmin(dp[nh][nw], dp[h][w] + getting_score);
      }
    }
  }

  if (dp[0][0] > 0) drop("Takahashi");
  if (dp[0][0] < 0) drop("Aoki");

  cout << "Draw"
       << "\n";
}
