// https://atcoder.jp/contests/past202004-open/tasks/past202004_k

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
  string S;
  cin >> N >> S;

  VL cs(N);
  rep(i, N) cin >> cs[i];

  VL ds(N);
  rep(i, N) cin >> ds[i];

  VVL dp(N + 1, VL(N + 1, INF));

  dp[0][0] = 0;

  rep(i, N) rep(open_ct, N) {
    chmin(dp[i + 1][open_ct], dp[i][open_ct] + ds[i]);

    if (S[i] == '(') {
      chmin(dp[i + 1][open_ct + 1], dp[i][open_ct]);
      if (open_ct > 0) chmin(dp[i + 1][open_ct - 1], dp[i][open_ct] + cs[i]);
    } else if (S[i] == ')') {
      if (open_ct > 0) chmin(dp[i + 1][open_ct - 1], dp[i][open_ct]);
      chmin(dp[i + 1][open_ct + 1], dp[i][open_ct] + cs[i]);
    }
  }

  ll res = dp[N][0];
  cout << res << "\n";
}
