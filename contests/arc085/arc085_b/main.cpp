// https://atcoder.jp/contests/abc078/tasks/arc085_b

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
  ll N, Z, W;
  cin >> N >> Z >> W;

  VL as(N);
  rep(i, N) cin >> as[i];

  VVL dp(N + 1, VL(2));  // dp[i][j] i 枚カードがひかれていて j = 0: 先手, j =
                         // 1: 後手が操作する時の答え

  repr(i, N) {
    // 先手
    {
      ll op = i == 0 ? W : as[i - 1];

      // 全部を取る場合
      chmax(dp[i][0], abs(op - as[N - 1]));

      repf(j, i + 1, N) chmax(dp[i][0], dp[j][1]);
    }

    // 後手
    {
      dp[i][1] = INF;
      ll op = i == 0 ? Z : as[i - 1];

      // 全部を取る場合
      chmin(dp[i][1], abs(op - as[N - 1]));
      repf(j, i + 1, N) chmin(dp[i][1], dp[j][0]);
    }
  }

  ll res = dp[0][0];
  cout << res << endl;
}

void solve2() {
  ll N, Z, W;
  cin >> N >> Z >> W;

  VL as(N);
  rep(i, N) cin >> as[i];

  if (N == 1) drop(abs(as[0] - W));

  ll res = max(abs(as[N - 1] - W), abs(as[N - 1] - as[N - 2]));

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
