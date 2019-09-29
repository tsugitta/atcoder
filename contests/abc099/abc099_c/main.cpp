// https://atcoder.jp/contests/abc099/tasks/abc099_c

#include "algorithm"
#include "iostream"
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define rep(i, from, to) for (int i = from; i < (to); ++i)
using namespace std;
typedef long long ll;

void solve() {
  ll N;
  cin >> N;

  ll dp[N + 1];  // dp[i]: i 円払う時の最小コスト
  rep(i, 1, N + 1) dp[i] = 1ll << 60;
  dp[0] = 0;

  rep(i, 1, N + 1) {
    dp[i] = min(dp[i], dp[i - 1] + 1);

    for (int j = 6; i - j >= 0; j *= 6) {
      dp[i] = min(dp[i], dp[i - j] + 1);
    }

    for (int j = 9; i - j >= 0; j *= 9) {
      dp[i] = min(dp[i], dp[i - j] + 1);
    }
  }

  cout << dp[N] << endl;
}

#ifndef TEST
int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  solve();
  return 0;
}
#endif
