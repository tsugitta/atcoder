// https://atcoder.jp/contests/abc214/tasks/abc214_f

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
#define repr1(i, from) for (ll i = from; i >= 1; --i)
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

using mint = modint1000000007;

void solve() {
  string S;
  cin >> S;

  ll N = S.size();

  // 部分列 DP
  // dp[i]: [0, i] (1-indexed)の部分列で、i 文字目を使用する場合の個数
  // 隣り合う要素からの遷移ができないことから、便宜的に dp[-1] = 1, dp[0] = 0
  // とする。
  V<mint> dp(N + 1);

  // 1-indexed
  rep1(i, N) {
    // 1-indexed. 先頭の空文字列の index が -1 なのでそこから 2 つ前の要素まで
    for (ll j = i - 2; j >= -1; --j) {
      dp[i] += j == -1 ? 1 : dp[j];

      // S[j] → S[i] は、 j と i の間に S[k] = S[i] なる k
      // が存在しない場合のみ行う。 存在する場合は S[k] → S[j]
      // と同一であるため。
      // ただし、S[k] → S[j] が行えない場合、つまり k, j
      // が隣り合わせの場合は含める必要がある。 よって、S[j-1] でなく S[j]
      // を見ることで、j の一つ前の要素 (j-1) まで dp に加算してから
      // 同一性チェック & break を行う。
      if (j >= 0 && S[j] == S[i - 1]) break;
    }
  }

  mint res = 0;
  rep(i, N) res += dp[i + 1];

  cout << res.val() << "\n";
}
