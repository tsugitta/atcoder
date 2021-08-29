// https://atcoder.jp/contests/abc216/tasks/abc216_f

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

using mint = modint998244353;

void solve() {
  ll N;
  cin >> N;

  VPL ps(N);
  for (auto& p : ps) cin >> p.fi;
  for (auto& p : ps) cin >> p.se;

  sort(all(ps));

  ll max_a = 0;
  for (auto& p : ps) chmax(max_a, p.fi);

  // i 番目 (1-indexed) までの b の部分和についての個数
  V<mint> dp(max_a + 1);
  dp[0] = 1;

  mint res = 0;

  for (auto& [a, b] : ps) {
    V<mint> n_dp = dp;

    rep(b_sum, max_a + 1) {
      if (b_sum + b > max_a) break;
      n_dp[b_sum + b] += dp[b_sum];

      // 重複を防ぐため、この i を選択する場合の個数のみを加算する。
      if (b_sum + b <= a) res += dp[b_sum];
    }

    swap(dp, n_dp);
  }

  cout << res.val() << "\n";
}
