// https://atcoder.jp/contests/abc142/tasks/abc142_e

#include "algorithm"
#include "iostream"
#include "vector"
#define rep(i, from, to) for (int i = from; i < (to); ++i)
using namespace std;
typedef long long ll;

template <class T>
inline bool chmax(T& a, T b);
template <class T>
inline bool chmin(T& a, T b);

const ll INF = 1ll << 60;

void solve() {
  ll N, M;
  cin >> N;
  cin >> M;

  vector<ll> costs(M), boxes(M, 0);

  rep(i, 0, M) {
    ll box_ct;
    cin >> costs[i] >> box_ct;

    rep(j, 0, box_ct) {
      ll box_num;
      cin >> box_num;
      boxes[i] |= (1 << (box_num - 1));
    }
  }

  ll dp[1 << N];
  rep(i, 0, 1 << N) dp[i] = INF;
  dp[0] = 0;

  rep(i, 0, M) {
    ll box_mask = boxes[i];

    rep(j, 0, 1 << N) { chmin(dp[j | box_mask], dp[j] + costs[i]); }
  }

  if (dp[(1 << N) - 1] == INF) {
    cout << -1 << endl;
    return;
  }

  cout << dp[(1 << N) - 1] << endl;
}

#ifndef TEST
int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  solve();
  return 0;
}
#endif

template <class T>
inline bool chmax(T& a, T b) {
  if (a < b) {
    a = b;
    return 1;
  }
  return 0;
}

template <class T>
inline bool chmin(T& a, T b) {
  if (a > b) {
    a = b;
    return 1;
  }
  return 0;
}
