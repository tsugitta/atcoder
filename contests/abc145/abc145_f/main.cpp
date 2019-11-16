// https://atcoder.jp/contests/abc145/tasks/abc145_f

#include "algorithm"
#include "functional"
#include "iostream"
#include "numeric"
#include "queue"
#include "set"
#include "vector"
#define rep(i, to) for (ll i = 0; i < (to); ++i)
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
  ll N, K;
  cin >> N >> K;
  VL hs(N + 1);
  hs[0] = 0;
  rep(i, N) cin >> hs[i + 1];

  // dp[i][j]: 最も右の項が hs[i] 番目で合計 j 本消した場合のコストの最小値
  VVL dp(N + 1, VL(K + 1, INF));
  dp[0][0] = 0;

  repf(i, 1, N + 1) {
    rep(j, i) {
      ll to_be_removed = i - j - 1;
      rep(k, K - to_be_removed + 1) {
        chmin(dp[i][k + to_be_removed], dp[j][k] + max(0ll, hs[i] - hs[j]));
      }
    }
  }

  ll res = INF;
  rep(i, K + 1) chmin(res, dp[N - i][K - i]);
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
    solve();
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
