// https://atcoder.jp/contests/abc156/tasks/abc156_f

#include "algorithm"
#include "bitset"
#include "cmath"
#include "functional"
#include "iomanip"
#include "iostream"
#include "map"
#include "numeric"
#include "queue"
#include "set"
#include "string"
#include "vector"
#define rep(i, to) for (ll i = 0; i < (to); ++i)
#define rep1(i, to) for (ll i = 1; i <= (to); ++i)
#define repf(i, from, to) for (ll i = from; i < (to); ++i)
#define repr(i, from) for (ll i = from - 1; i >= 0; --i)
#define all(vec) vec.begin(), vec.end()
#define unless(cond) if (!(cond))
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef long double ld;
template <typename T>
using V = vector<T>;
using VL = V<ll>;
using VVL = V<VL>;
template <typename T, typename U>
using P = pair<T, U>;
using PL = P<ll, ll>;
using VPL = V<PL>;
template <typename T>
inline bool chmax(T& a, T b);
template <typename T>
inline bool chmin(T& a, T b);
void print_ints(vector<ll> v);
template <typename T>
void drop(T a);

const ll INF = 1e18;

ll div_ceil(ll a, ll b) { return (a + b - 1) / b; }

void solve() {
  ll K, Q;
  cin >> K >> Q;

  VL ds(K);
  rep(i, K) cin >> ds[i];

  auto query = [&](ll n, ll x, ll m) -> ll {
    ll last = x;
    ll zero_ct = 0;

    rep(i, K) {
      // 要素が N -> ds で足されるのは先頭 N-1 個
      ll added_count = div_ceil(n - 1 - i, K);
      last += (ds[i] % m) * added_count;

      if (ds[i] % m == 0) zero_ct += added_count;
    }

    // 商が増えた数 = あまりが減った数
    ll less_ct = last / m - x / m;

    return n - 1 - less_ct - zero_ct;
  };

  rep(i, Q) {
    ll n, x, m;
    cin >> n >> x >> m;
    cout << query(n, x, m) << endl;
  }
}

void solve2() {
  ll K, Q;
  cin >> K >> Q;

  VL ds(K);
  rep(i, K) cin >> ds[i];

  auto query = [&](ll n, ll x, ll m) -> ll {
    ll last = 0;
    ll zero_ct = 0;

    rep(i, K) {
      last += ds[i] % m;
      if (ds[i] % m == 0) zero_ct++;
    }

    // 要素が N -> ds で足されるのは先頭 N-1 個

    last *= (n - 1) / K;
    zero_ct *= (n - 1) / K;

    rep(i, (n - 1) % K) {
      last += ds[i] % m;
      if (ds[i] % m == 0) zero_ct++;
    }

    last += x;

    // 商が増えた数 = あまりが減った数
    ll less_ct = last / m - x / m;

    return n - 1 - less_ct - zero_ct;
  };

  rep(i, Q) {
    ll n, x, m;
    cin >> n >> x >> m;
    cout << query(n, x, m) << endl;
  }
}

struct exit_exception : public std::exception {
  const char* what() const throw() { return "Exited"; }
};

#ifndef TEST
int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  try {
    solve2();
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
  rep(i, v.size()) {
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
