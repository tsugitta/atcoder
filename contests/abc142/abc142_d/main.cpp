// https://atcoder.jp/contests/abc142/tasks/abc142_d

#include "algorithm"
#include "iostream"
#include "vector"
#define rep(i, from, to) for (ll i = from; i < (to); ++i)
using namespace std;
typedef long long ll;

template <class T>
inline bool chmax(T& a, T b);
template <class T>
inline bool chmin(T& a, T b);

vector<pair<ll, ll>> factorize(ll n) {
  vector<pair<ll, ll>> res;

  for (ll i = 2; i * i <= n; i++) {
    if (n % i != 0) continue;

    auto r = pair<ll, ll>(i, 0);

    while (n % i == 0) {
      n /= i;
      r.second++;
    }

    res.push_back(r);
  }

  // sqrt(n) 以上の素因数は高々一つ
  if (n != 1) res.emplace_back(n, 1);

  return res;
}

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

void solve() {
  ll A, B;
  cin >> A >> B;

  ll g = gcd(A, B);
  auto f = factorize(g);
  ll res = f.size() + 1;
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
