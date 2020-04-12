// https://atcoder.jp/contests/abc162/tasks/abc162_f

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

  VL as(N);
  rep(i, N) cin >> as[i];

  V<map<ll, ll>> dp(N + 1, map<ll, ll>());

  dp[1][0] = 0;
  dp[1][1] = as[0];

  repf(i, 1, N) {
    for (ll j = (i - 1) / 2; j <= (i + 1) / 2; j++) {
      if (dp[i + 1].count(j) == 0) dp[i + 1][j] = -INF;
      if (dp[i + 1].count(j + 1) == 0) dp[i + 1][j + 1] = -INF;
      chmax(dp[i + 1][j], dp[i][j]);
      chmax(dp[i + 1][j + 1], dp[i - 1][j] + as[i]);
    }
  }

  ll res = dp[N][N / 2];

  cout << res << "\n";
}
