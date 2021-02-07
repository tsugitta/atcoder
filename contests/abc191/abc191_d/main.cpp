// https://atcoder.jp/contests/abc191/tasks/abc191_d

#include <atcoder/all>

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
using namespace atcoder;
using ll = long long;
using ld = long double;
template <typename T>
using V = vector<T>;
using VL = V<ll>;
template <typename T>
using VV = V<V<T>>;
using VVL = VV<ll>;
template <typename T>
using VVV = VV<V<T>>;
template <typename T, typename U>
using P = pair<T, U>;
using PL = P<ll, ll>;
using VPL = V<PL>;
template <typename T>
using asc_pq = priority_queue<T, V<T>, greater<T>>;

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

template <typename T>
inline ll len(V<T> arr) {
  return arr.size();
}

struct exit_exception : public std::exception {
  const char* what() const throw() { return "Exited"; }
};

template <typename T>
void drop(T res) {
  cout << res << endl;
  throw exit_exception();
}

const ll INF = 1e18;

void solve();

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

void solve() {
  ld _X, _Y, _R;
  cin >> _X >> _Y >> _R;

  ll SCALE = 10000;

  ll X = llroundl(_X * SCALE);
  ll Y = llroundl(_Y * SCALE);
  ll R = llroundl(_R * SCALE);

  ll res = 0;

  auto is_included = [&](ll x, ll y) {
    return (X - x) * (X - x) + (Y - y) * (Y - y) <= R * R;
  };

  for (ll x = -2e5 * SCALE; x <= 2e5 * SCALE; x += SCALE) {
    unless(X - R <= x && x <= X + R) continue;
    ll dx = abs(X - x);
    ll dy = llroundl(sqrtl(R * R - dx * dx));

    ll ly = Y - dy - SCALE;
    ly -= ly < 0 ? SCALE - abs(ly) % SCALE : ly % SCALE;

    ll hy = Y + dy + SCALE;
    hy += hy < 0 ? abs(hy) % SCALE : SCALE - hy % SCALE;

    while (ly < hy && !is_included(x, ly)) ly += SCALE;

    if (ly == hy) {
      if (is_included(x, ly)) res++;
      continue;
    }

    while (!is_included(x, hy)) hy -= SCALE;

    res += (hy - ly) / SCALE + 1;
  }

  cout << res << "\n";
}
