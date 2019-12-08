// https://atcoder.jp/contests/abc147/tasks/abc147_e

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
  ll H, W;
  cin >> H >> W;

  VVL as(H, VL(W));
  rep(h, H) rep(w, W) cin >> as[h][w];

  VVL bs(H, VL(W));
  rep(h, H) rep(w, W) cin >> bs[h][w];

  ll abs_max = 0;
  rep(h, H) rep(w, W) { chmax(abs_max, abs(as[h][w] - bs[h][w])); }

  ll abs_sum_max = (W + H - 1) * abs_max;

  ll res = INF;

  // dp[h][w][k]: h, w までの経路で偏りが k となるか
  // k はマイナスも扱うために abs_sum_max を足した値としておく
  V<V<V<bool>>> dp(H, V<V<bool>>(W, V<bool>(2 * abs_sum_max + 1)));
  dp[0][0][abs_sum_max + as[0][0] - bs[0][0]] = true;
  dp[0][0][abs_sum_max + bs[0][0] - as[0][0]] = true;

  // 配る DP
  rep(h, H) rep(w, W) rep(k, 2 * abs_sum_max + 1) {
    if (!dp[h][w][k]) continue;

    rep(h_diff, 2) rep(w_diff, 2) {
      if (h_diff == w_diff) continue;
      if (h + h_diff >= H || w + w_diff >= W) continue;

      ll a = as[h + h_diff][w + w_diff];
      ll b = bs[h + h_diff][w + w_diff];

      dp[h + h_diff][w + w_diff][k + a - b] = true;
      dp[h + h_diff][w + w_diff][k + b - a] = true;
    }
  }

  rep(k, abs_sum_max + 1) if (dp[H - 1][W - 1][abs_sum_max + k]) drop(k);
}

// bitset
void solve2() {
  ll H, W;
  cin >> H >> W;

  // abs
  VVL as(H, VL(W));
  rep(h, H) rep(w, W) cin >> as[h][w];

  rep(h, H) rep(w, W) {
    ll b;
    cin >> b;
    as[h][w] = abs(as[h][w] - b);
  }

  ll res = INF;

  // dp[h][w][k]: h, w までの経路で偏りが k となるか
  const ll base = (80 + 80 - 1) * 80;
  using bits = bitset<2 * base + 1>;
  V<V<bits>> dp(H, V<bits>(W, bits()));

  dp[0][0].set(base);
  dp[0][0] = dp[0][0] << as[0][0] | dp[0][0] >> as[0][0];

  // 配る DP
  rep(h, H) rep(w, W) {
    rep(h_diff, 2) rep(w_diff, 2) {
      if (h_diff == w_diff) continue;
      if (h + h_diff >= H || w + w_diff >= W) continue;

      ll a = as[h + h_diff][w + w_diff];

      dp[h + h_diff][w + w_diff] |= dp[h][w] << a | dp[h][w] >> a;
    }
  }

  rep(k, base + 1) if (dp[H - 1][W - 1][base + k]) drop(k);
}

// bitset + 空間計算量を落とす
void solve3() {
  ll H, W;
  cin >> H >> W;

  // abs
  VVL as(H, VL(W));
  rep(h, H) rep(w, W) cin >> as[h][w];

  rep(h, H) rep(w, W) {
    ll b;
    cin >> b;
    as[h][w] = abs(as[h][w] - b);
  }

  ll res = INF;

  // dp[h % 2][w][k]: h, w までの経路で偏りが k となるか
  const ll base = (80 + 80 - 1) * 80;
  using bits = bitset<2 * base + 1>;
  V<V<bits>> dp(2, V<bits>(W, bits()));

  dp[0][0].set(base);
  dp[0][0] = dp[0][0] << as[0][0] | dp[0][0] >> as[0][0];

  // 配る DP
  rep(h, H) {
    rep(w, W) {
      rep(h_diff, 2) rep(w_diff, 2) {
        if (h_diff == w_diff) continue;
        if (h + h_diff >= H || w + w_diff >= W) continue;

        ll a = as[h + h_diff][w + w_diff];

        dp[(h + h_diff) % 2][w + w_diff] |=
            dp[h % 2][w] << a | dp[h % 2][w] >> a;
      }
    }

    if (h != H - 1) rep(w, W) dp[h % 2][w].reset();
  }

  rep(k, base + 1) if (dp[(H - 1) % 2][W - 1][base + k]) drop(k);
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
