// https://atcoder.jp/contests/abc096/tasks/abc096_d

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

bool is_prime(ll a) {
  if (a == 1) return false;

  for (ll i = 2; i * i <= a; i++) {
    if (a % i == 0) {
      return false;
    }
  }

  return true;
}

void print_ints(vector<ll> v);

void solve() {
  ll N;
  cin >> N;

  // n ≡ 1 mod 5 なる a のみを含めれば、 5 つ選んだ時に必ず 5
  // の倍数となり条件を満たす。

  vector<ll> v;

  ll next = 2;
  while (v.size() < N) {
    if (is_prime(next) && next % 5 == 1) {
      v.push_back(next);
    }

    next++;
  }

  print_ints(v);
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

void print_ints(vector<ll> v) {
  rep(i, 0, v.size()) {
    if (i > 0) {
      cout << " ";
    }

    cout << v[i];
  }

  cout << endl;
}
