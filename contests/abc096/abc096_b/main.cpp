// https://atcoder.jp/contests/abc096/tasks/abc096_b

#include "algorithm"
#include "cmath"
#include "iostream"
#include "set"
#include "vector"
#define rep(i, from, to) for (ll i = from; i < (to); ++i)
using namespace std;
typedef long long ll;

template <class T>
inline bool chmax(T& a, T b);
template <class T>
inline bool chmin(T& a, T b);

void solve() {
  vector<ll> v(3);
  rep(i, 0, v.size()) cin >> v[i];

  int k;
  cin >> k;

  sort(v.begin(), v.end());
  v[2] <<= k;

  ll res = 0;
  rep(i, 0, v.size()) res += v[i];

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
