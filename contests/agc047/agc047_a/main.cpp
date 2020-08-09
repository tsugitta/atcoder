// https://atcoder.jp/contests/agc047/tasks/agc047_a

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
  ll N;
  cin >> N;

  VL as(N);

  rep(i, N) {
    ld d;
    cin >> d;
    d *= 1e9;
    as[i] = d + 0.5;
  }

  VVL ct(19, VL(19));  // 0 ~ 18

  for (ll a : as) {
    ll ct2 = 0;
    ll ct5 = 0;

    while (a % 2 == 0) {
      a /= 2;
      ct2++;
    }

    while (a % 5 == 0) {
      a /= 5;
      ct5++;
    }

    ct2 = min(ct2, 18ll);
    ct5 = min(ct5, 18ll);

    ct[ct2][ct5]++;
  }

  ll res = 0;

  rep(i2, 19) rep(i5, 19) rep(j2, 19) rep(j5, 19) {
    unless(i2 + j2 >= 18) continue;
    unless(i5 + j5 >= 18) continue;

    if (i2 == j2 && i5 == j5) {
      res += ct[i2][i5] * (ct[j2][j5] - 1);
    } else {
      res += ct[i2][i5] * ct[j2][j5];
    }
  }

  res /= 2;
  cout << res << "\n";
}
