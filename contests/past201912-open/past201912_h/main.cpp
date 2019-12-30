// https://atcoder.jp/contests/past201912-open/tasks/past201912_h

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

void solve() {
  ll N;
  cin >> N;

  VL cs(N);
  rep(i, N) cin >> cs[i];

  ll Q;
  cin >> Q;

  VL each_cts(N);
  ll odd_ct = 0;
  ll odd_min = INF;
  ll all_ct = 0;
  ll all_min = INF;

  // 実装は 0-index のため
  auto is_odd = [](ll i) -> bool { return i % 2 == 0; };

  rep(i, N) {
    if (is_odd(i)) chmin(odd_min, cs[i]);
    chmin(all_min, cs[i]);
  }

  ll res = 0;

  rep(i, Q) {
    ll type;
    cin >> type;

    if (type == 1) {
      ll x, a;
      cin >> x >> a;
      x--;

      ll cur_val = cs[x] - all_ct - each_cts[x];
      if (is_odd(x)) cur_val -= odd_ct;

      if (a > cur_val) continue;

      each_cts[x] += a;

      if (is_odd(x)) chmin(odd_min, cur_val - a);
      chmin(all_min, cur_val - a);

      res += a;
    } else if (type == 2) {
      ll a;
      cin >> a;

      if (a > odd_min) continue;

      odd_ct += a;
      odd_min -= a;
      chmin(all_min, odd_min);

      res += a * ((N + 1) / 2);
    } else if (type == 3) {
      ll a;
      cin >> a;

      if (a > all_min) continue;

      all_ct += a;
      odd_min -= a;
      all_min -= a;

      res += a * N;
    }
  }

  cout << res << endl;
}

struct exit_exception : public std::exception {
  const char* what() const throw() { return "Exited"; }
};

#ifndef TEST
int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  try {
    solve();
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
