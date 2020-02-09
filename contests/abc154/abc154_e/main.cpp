// https://atcoder.jp/contests/abc154/tasks/abc154_e

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
typedef long double ld;
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
  string N;
  ll K;
  cin >> N >> K;

  // dp[i][k][strict]: 上から i 桁目までで k 個使った場合
  V<VVL> dp(N.size() + 1, VVL(K + 1, VL(2)));
  dp[0][0][1] = 1;

  ll len = N.size();
  rep(i, len) {
    // 次の桁
    ll num = N[i] - '0';

    // 今の所
    rep(k, K + 1) {
      if (num == 0) {
        // 0 をとる場合
        dp[i + 1][k][1] += dp[i][k][1];
        dp[i + 1][k][0] += dp[i][k][0];

        // 0 以外
        if (k >= K) continue;

        dp[i + 1][k + 1][0] += 9 * dp[i][k][0];
      } else {
        // 0 をとる場合
        dp[i + 1][k][0] += dp[i][k][0] + dp[i][k][1];

        // 0 以外
        if (k >= K) continue;

        dp[i + 1][k + 1][1] += dp[i][k][1];
        dp[i + 1][k + 1][0] += dp[i][k][0] * 9 + dp[i][k][1] * (num - 1);
      }
    }
  }

  ll res = dp[N.size()][K][1] + dp[N.size()][K][0];
  cout << res << endl;
}

void solve2() {
  string N;
  ll K;
  cin >> N >> K;

  // dp[i][k][strict]: 上から i 桁目までで k 個使った場合
  V<VVL> dp(N.size() + 1, VVL(K + 1, VL(2)));
  dp[0][0][1] = 1;

  ll len = N.size();
  // 前の状態 + val から配る DP
  rep(i, len) rep(k, K + 1) rep(strict, 2) rep(num, 10) {
    ll digit_num = N[i] - '0';

    if (strict && num > digit_num) continue;
    ll nk = k + (num != 0);
    if (nk > K) continue;
    dp[i + 1][nk][strict && digit_num == num] += dp[i][k][strict];
  }

  ll res = dp[N.size()][K][1] + dp[N.size()][K][0];
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
