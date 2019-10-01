// https://atcoder.jp/contests/abc141/tasks/abc141_d

#include "algorithm"
#include "iostream"
#include "queue"
#include "vector"
#define rep(i, from, to) for (ll i = from; i < (to); ++i)
using namespace std;
typedef long long ll;

template <class T>
inline bool chmax(T& a, T b);
template <class T>
inline bool chmin(T& a, T b);

void solve() {
  ll N, M;
  cin >> N >> M;

  priority_queue<ll> pq;

  rep(i, 0, N) {
    ll a;
    cin >> a;
    pq.push(a);
  }

  rep(i, 0, M) {
    ll popped = pq.top();
    pq.pop();
    pq.push(popped / 2);
  }

  ll res = 0;

  while (!pq.empty()) {
    res += pq.top();
    pq.pop();
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
