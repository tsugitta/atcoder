// https://atcoder.jp/contests/abc197/tasks/abc197_e

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
  ll N;
  cin >> N;

  map<ll, VL> c_to_xs;

  rep(i, N) {
    ll x, c;
    cin >> x >> c;
    c_to_xs[c].push_back(x);
  }

  VVL edges;
  edges.push_back({0, 0});

  for (auto [c, xs] : c_to_xs) {
    sort(all(xs));
    edges.push_back({xs.front(), xs.back()});
  }

  ll P_CT = edges.size();

  // dp[i][right]: i 番目の色を集め終えて、右端にいる時の時間
  VVL dp(edges.size(), VL(2, INF));
  dp[0][0] = 0;
  dp[0][1] = 0;

  rep(i, P_CT - 1) rep(cur_right, 2) rep(next_right, 2) {
    ll diff_to_next_color =
        abs(edges[i + 1][1 - next_right] - edges[i][cur_right]);
    ll next_color_diff = edges[i + 1][1] - edges[i + 1][0];

    chmin(dp[i + 1][next_right],
          dp[i][cur_right] + diff_to_next_color + next_color_diff);
  }

  ll res = INF;
  rep(i, 2) chmin(res, dp.back()[i] + abs(edges.back()[i]));

  cout << res << "\n";
}
