// https://atcoder.jp/contests/hhkb2020/tasks/hhkb2020_e

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
void solve2();

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

using mint = modint1000000007;

void solve() {
  ll H, W;
  cin >> H >> W;

  V<string> mat(H);
  rep(h, H) cin >> mat[h];

  VVL uct(H, VL(W));
  VVL rct(H, VL(W));
  VVL lct(H, VL(W));
  VVL dct(H, VL(W));

  ll K = 0;

  rep(h, H) rep(w, W) {
    if (mat[h][w] == '#') continue;
    K++;

    if (w + 1 < W) lct[h][w + 1] = lct[h][w] + 1;
    if (h + 1 < H) uct[h + 1][w] = uct[h][w] + 1;
  }

  repr(h, H) repr(w, W) {
    if (mat[h][w] == '#') continue;

    if (w - 1 >= 0) rct[h][w - 1] = rct[h][w] + 1;
    if (h - 1 >= 0) dct[h - 1][w] = dct[h][w] + 1;
  }

  mint res = 0;

  mint kp = mint(2).pow(K - 1);

  rep(h, H) rep(w, W) {
    if (mat[h][w] == '#') continue;

    res += kp;  // 自身が光る時

    ll other_ct = rct[h][w] + lct[h][w] + uct[h][w] + dct[h][w];
    res += kp - mint(2).pow(K - 1 - other_ct);
  }

  cout << res.val() << "\n";
}

// 余事象
void solve2() {
  ll H, W;
  cin >> H >> W;

  V<string> mat(H);
  rep(h, H) cin >> mat[h];

  VVL uct(H, VL(W));
  VVL rct(H, VL(W));
  VVL lct(H, VL(W));
  VVL dct(H, VL(W));

  ll K = 0;

  rep(h, H) rep(w, W) {
    if (mat[h][w] == '#') continue;
    K++;

    if (w + 1 < W) lct[h][w + 1] = lct[h][w] + 1;
    if (h + 1 < H) uct[h + 1][w] = uct[h][w] + 1;
  }

  repr(h, H) repr(w, W) {
    if (mat[h][w] == '#') continue;

    if (w - 1 >= 0) rct[h][w - 1] = rct[h][w] + 1;
    if (h - 1 >= 0) dct[h - 1][w] = dct[h][w] + 1;
  }

  mint res = mint(2).pow(K) * K;

  rep(h, H) rep(w, W) {
    if (mat[h][w] == '#') continue;

    ll other_ct = rct[h][w] + lct[h][w] + uct[h][w] + dct[h][w];
    res -= mint(2).pow(K - 1 - other_ct);
  }

  cout << res.val() << "\n";
}
