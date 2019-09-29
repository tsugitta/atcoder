// https://atcoder.jp/contests/abc099/tasks/abc099_a
#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (n); ++i)
using namespace std;
typedef long long ll;

void solve() {
  ll N;
  cin >> N;
  string res;

  if (N >= 1000) {
    res = "ABD";
  } else {
    res = "ABC";
  }

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
