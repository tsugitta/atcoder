// https://atcoder.jp/contests/abc215/tasks/abc215_e

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
  string S;
  ll CONTEST_CT = 10;

  cin >> N >> S;

  // dp[S][last]: 過去の参加履歴が S で最後の出場が last.
  // 末端の要素は未参加を表す
  vector dp(1ll << CONTEST_CT, vector<mint>(CONTEST_CT + 1));

  dp[0][CONTEST_CT] = 1;

  for (char c : S) {
    ll id = c - 'A';
    vector n_dp = dp;

    rep(bit, 1ll << CONTEST_CT) rep(last, CONTEST_CT + 1) {
      if (id != last && (bit & (1 << id))) {
        continue;
      }

      ll n_bit = bit | (1 << id);
      n_dp[n_bit][id] += dp[bit][last];
    }

    swap(dp, n_dp);
  }

  mint res = 0;
  rep(bit, 1ll << CONTEST_CT) rep(last, CONTEST_CT) res += dp[bit][last];

  cout << res.val() << "\n";
}
