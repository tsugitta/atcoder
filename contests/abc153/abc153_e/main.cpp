// https://atcoder.jp/contests/abc153/tasks/abc153_e

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
  ll H, N;
  cin >> H >> N;

  struct Mg {
    ll h, m;
  };

  V<Mg> mgs(N);

  rep(i, N) {
    ll h, m;
    cin >> h >> m;

    mgs[i] = {h, m};
  }

  // dp[i][h] // i 番目の魔法までで h 減らすのに必要な m
  VVL dp(N + 1, VL(H + 1, INF));
  dp[0][0] = 0;

  // 同じ要素ありのナップサック
  rep(i, N) rep(h, H + 1) {
    auto mg = mgs[i];
    chmin(dp[i + 1][h], dp[i][h]);
    chmin(dp[i + 1][min(H, h + mg.h)], dp[i + 1][h] + mg.m);
  }

  cout << dp[N][H] << endl;
}

void solve2() {
  ll H, N;
  cin >> H >> N;

  struct Mg {
    ll h, m;
  };

  V<Mg> mgs(N);

  rep(i, N) {
    ll h, m;
    cin >> h >> m;

    mgs[i] = {h, m};
  }

  VL dp(H + 1, INF);
  dp[0] = 0;

  rep(i, N) rep(h, H + 1) {
    auto mg = mgs[i];
    chmin(dp[min(H, h + mg.h)], dp[h] + mg.m);
  }

  cout << dp[H] << endl;
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
