// https://atcoder.jp/contests/abc181/tasks/abc181_e

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
inline bool chmax(T &a, T b) {
  if (a < b) {
    a = b;
    return 1;
  }
  return 0;
}

template <typename T>
inline bool chmin(T &a, T b) {
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
  const char *what() const throw() { return "Exited"; }
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
  } catch (exit_exception &e) {
  }

  return 0;
}
#endif

void solve() {
  ll N, M;
  cin >> N >> M;

  VL hs(N);
  rep(i, N) cin >> hs[i];

  VL ws(M);
  rep(i, M) cin >> ws[i];

  sort(all(hs));

  VL lsum(N + 1);

  rep(i, N) {
    lsum[i + 1] = lsum[i];

    if (i % 2 == 1) lsum[i + 1] += hs[i] - hs[i - 1];
  }

  VL rsum(N + 1);

  repr(i, N) {
    rsum[i] = rsum[i + 1];

    if (i % 2 == 1 && i < N - 1) rsum[i] += hs[i + 1] - hs[i];
  }

  ll res = INF;

  for (ll w : ws) {
    auto it = lower_bound(all(hs), w);
    ll i = it - hs.begin();

    ll r = lsum[i] + rsum[i];
    if (i % 2 == 1) {
      r += w - hs[i - 1];
    } else {
      r += hs[i] - w;
    }

    chmin(res, r);
  }

  cout << res << "\n";
}
