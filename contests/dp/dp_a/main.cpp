// https://atcoder.jp/contests/dp/tasks/dp_a

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

  V<ll> hs(N);
  rep(i, 0, N) cin >> hs[i];

  ll INF = 1e18;

  V<ll> dp(N, INF);
  dp[0] = 0;

  rep(i, 0, N) {
    if (i + 1 < N) {
      chmin(dp[i + 1], dp[i] + abs(hs[i + 1] - hs[i]));
    }

    if (i + 2 < N) {
      chmin(dp[i + 2], dp[i] + abs(hs[i + 2] - hs[i]));
    }
  }

  cout << dp[N - 1] << endl;
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
