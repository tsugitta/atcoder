// https://atcoder.jp/contests/sumitrust2019/tasks/sumitb2019_f

#include "algorithm"
#include "cmath"
#include "functional"
#include "iomanip"
#include "iostream"
#include "numeric"
#include "queue"
#include "set"
#include "string"
#include "vector"
#define rep(i, to) for (ll i = 0; i < (to); ++i)
#define repf(i, from, to) for (ll i = from; i < (to); ++i)
#define repr(i, from) for (ll i = from - 1; i >= 0; --i)
#define all(vec) vec.begin(), vec.end()
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
  ll t1, t2, a1, a2, b1, b2;

  cin >> t1 >> t2 >> a1 >> a2 >> b1 >> b2;

  ll c1 = a1 - b1;
  ll c2 = a2 - b2;

  ll diff = c1 * t1 + c2 * t2;

  if (diff == 0) drop("infinity");
  if (c1 > 0 && diff > 0 || c1 < 0 && diff < 0) drop(0);

  ll adiff = abs(diff);

  if (c1 < 0) {
    c1 *= -1;
    c2 *= -1;
    diff *= -1;
  }

  // c1 > 0 && c2 < 0 かつ diff < 0

  ll highest = c1 * t1;

  ll res = ((highest + adiff - 1) / adiff) * 2;

  if (highest % adiff == 0) {
    // 最後に 1 回だけ触れる
    res++;
  }

  // 最初の 1 回除く
  res--;

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
