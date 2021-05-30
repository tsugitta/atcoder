// https://atcoder.jp/contests/abc203/tasks/abc203_f

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
  ll N, K;
  cin >> N >> K;

  VL as(N);
  rep(i, N) cin >> as[i];

  sort(all(as));

  // dp[i][j]:
  // 草1から草iまでが最初に庭に生えていると考えた時、j回以下で操作を終了するためにAが抜かなくてはならない最小の本数
  VVL dp(N + 1, VL(31, INF));
  dp[0][0] = 0;

  rep(i, N) rep(t_ct, 31) {
    if (dp[i][t_ct] == INF) continue;

    chmin(dp[i + 1][t_ct], dp[i][t_ct] + 1);  // A が抜く場合

    // i 番目を T が抜く場合、それを一緒に抜く最大の数を抜くのが最適。
    ll next_i = lower_bound(all(as), as[i] * 2) - as.begin();
    chmin(dp[next_i][t_ct + 1], dp[i][t_ct]);
  }

  rep(t_ct, 31) if (dp[N][t_ct] <= K) {
    cout << t_ct << " " << dp[N][t_ct] << "\n";
    break;
  }
}
