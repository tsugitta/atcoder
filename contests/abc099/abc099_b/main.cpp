// https://atcoder.jp/contests/abc099/tasks/abc099_b

#include "iostream"
#define rep(i, n) for (int i = 0; i < (n); ++i)
using namespace std;
typedef long long ll;

void solve() {
  ll a, b;
  cin >> a >> b;
  ll diff = b - a;
  ll a_act = (diff - 1) * diff / 2;
  ll res = a_act - a;
  cout << res << endl;
}

#ifndef TEST
int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  solve();
  return 0;
}
#endif
