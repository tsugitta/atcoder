// https://atcoder.jp/contests/abc199/tasks/abc199_e

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
  ll N, M;
  cin >> N >> M;

  struct Cond {
    ll y, z;
  };

  VV<Cond> x_to_conds(N + 1);

  rep(i, M) {
    ll x, y, z;
    cin >> x >> y >> z;
    x_to_conds[x].push_back({y, z});
  }

  // その bit 集合を先頭に持つケースの個数
  VL dp(1 << N);
  dp[0] = 1;

  rep(bit, 1 << N) {
    VL acc_cts(N + 1);

    {
      VL cts(N + 1);

      rep(i, N) {
        if (bit & (1 << i)) cts[i + 1]++;
      }

      rep(i, N + 1) acc_cts[i] = cts[i] + (i > 0 ? acc_cts[i - 1] : 0);
    }

    ll digit_ct = __builtin_popcountll(bit);

    if (bit > 0) {
      rep(i, N) {
        for (auto cond : x_to_conds[digit_ct]) {
          unless(acc_cts[cond.y] <= cond.z) dp[bit] = 0;
        }
      }
    }

    // 次の桁
    rep(i, N) {
      if (bit & (1 << i)) continue;

      dp[bit | (1 << i)] += dp[bit];
    }
  }

  ll res = dp[(1 << N) - 1];
  cout << res << "\n";
}
