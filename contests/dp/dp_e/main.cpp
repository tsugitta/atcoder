// https://atcoder.jp/contests/dp/tasks/dp_e

#include "algorithm"
#include "iostream"
#include "set"
#include "vector"
#define rep(i, from, to) for (ll i = from; i < (to); ++i)
using namespace std;
typedef long long ll;
template <typename T>
using V = vector<T>;
template <typename T>
inline bool chmax(T& a, T b);
template <typename T>
inline bool chmin(T& a, T b);
void print_ints(vector<ll> v);
template <typename T>
void drop(T a);

void solve() {
  ll N, W;
  cin >> N >> W;

  ll v_sum = 0;

  V<pair<ll, ll>> items(N);
  rep(i, 0, N) {
    cin >> items[i].first;
    cin >> items[i].second;
    v_sum += items[i].second;
  }

  ll INF = 1e18;
  // dp[i][j]: i 番目のアイテムまでで価値を j 以上にするために必要な最小の重さ
  V<V<ll>> dp(2, V<ll>(v_sum + 1, INF));
  rep(i, 0, 2) dp[i][0] = 0;

  rep(i, 1, N + 1) {
    auto item = items[i - 1];
    auto w = item.first;
    auto v = item.second;

    rep(j, 0, v_sum + 1) {
      chmin(dp[i & 1][j], dp[(i - 1) & 1][j]);

      if (j - v >= 0) {
        chmin(dp[i & 1][j], dp[(i - 1) & 1][j - v] + w);
      }
    }
  }

  ll res = 0;
  rep(v, 0, v_sum + 1) {
    if (dp[N & 1][v] <= W) chmax(res, v);
  }

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
  rep(i, 0, v.size()) {
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
