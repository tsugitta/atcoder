// https://atcoder.jp/contests/abc140/tasks/abc140_e

#include "algorithm"
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
  ll N;
  cin >> N;

  vector<ll> ps(N), num_to_index(N + 1);
  rep(i, 0, N) cin >> ps[i];

  rep(i, 0, N) num_to_index[ps[i]] = i;

  multiset<ll> large_indices;

  large_indices.insert(-1);
  large_indices.insert(-1);
  large_indices.insert(N);
  large_indices.insert(N);

  ll res = 0;

  for (ll num = N; num >= 1; num--) {
    ll i = num_to_index[num];

    auto it = large_indices.lower_bound(i);
    ll bi = *it++;
    ll bi2 = *it--;
    it--;
    ll si = *it--;
    ll si2 = *it;

    // s を取る場合
    res += (si - si2) * (bi - i) * num;
    // b を取る場合
    res += (bi2 - bi) * (i - si) * num;

    large_indices.insert(i);
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
