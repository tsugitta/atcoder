// https://atcoder.jp/contests/dp/tasks/dp_c

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
  ll N;
  cin >> N;

  ll K = 3;

  V<V<ll>> as(N, V<ll>(K));
  rep(i, 0, N) rep(j, 0, K) cin >> as[i][j];

  V<V<ll>> dp(N + 1, V<ll>(K, 0));

  rep(i, 0, N) rep(lastK, 0, K) rep(nextK, 0, K) {
    if (lastK == nextK) continue;

    chmax(dp[i + 1][nextK], dp[i][lastK] + as[i][nextK]);
  }

  ll res = *max_element(dp[N].begin(), dp[N].end());
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
