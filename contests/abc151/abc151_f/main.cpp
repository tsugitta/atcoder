// https://atcoder.jp/contests/abc151/tasks/abc151_f

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

ld dist(P<ld, ld> a, P<ld, ld> b) {
  return sqrt(pow(a.fi - b.fi, 2) + pow(a.se - b.se, 2));
}

P<ld, ld> middle(P<ld, ld> a, P<ld, ld> b) {
  return {(a.fi + b.fi) / 2, (a.se + b.se) / 2};
}

P<P<ld, ld>, ld> circle(const P<ld, ld> a, const P<ld, ld> b,
                        const P<ld, ld> c) {
  ld ox = (min(min(a.fi, b.fi), c.fi) + max(min(a.fi, b.fi), c.fi)) / 2;
  ld oy = (min(min(a.se, b.se), c.se) + max(min(a.se, b.se), c.se)) / 2;
  ld ax = a.fi - ox, ay = a.se - oy;
  ld bx = b.fi - ox, by = b.se - oy;
  ld cx = c.fi - ox, cy = c.se - oy;
  ld d = (ax * (by - cy) + bx * (cy - ay) + cx * (ay - by)) * 2;
  if (d == 0) {
    return {P<ld, ld>{-1, -1}, -1};
  }

  ld x = ((ax * ax + ay * ay) * (by - cy) + (bx * bx + by * by) * (cy - ay) +
          (cx * cx + cy * cy) * (ay - by)) /
         d;
  ld y = ((ax * ax + ay * ay) * (cx - bx) + (bx * bx + by * by) * (ax - cx) +
          (cx * cx + cy * cy) * (bx - ax)) /
         d;
  P<ld, ld> p = {ox + x, oy + y};
  ld r = max(max(dist(p, a), dist(p, b)), dist(p, c));
  return {p, r};
}

void solve() {
  ll N;
  cin >> N;

  V<P<ld, ld>> ps(N);

  rep(i, N) {
    ld x, y;
    cin >> x >> y;
    ps[i] = {x, y};
  }

  auto is_ok = [&](P<ld, ld> c, ld r) -> bool {
    rep(i, N) {
      PL p = ps[i];
      unless(dist(c, p) <= r + 1e-8) return false;
    }

    return true;
  };

  ld res = 1e18;

  // 2 点を直径に持つ
  rep(j, N) rep(i, j) {
    auto cent = middle(ps[i], ps[j]);
    ld rad = dist(cent, ps[i]);

    if (rad < res && is_ok(cent, rad)) {
      res = rad;
    }
  }

  // 3 点を通る
  rep(k, N) rep(j, k) rep(i, j) {
    auto cir = circle(ps[i], ps[j], ps[k]);

    auto cent = cir.fi;
    auto rad = cir.se;

    if (rad == -1) continue;

    if (rad < res && is_ok(cent, rad)) {
      res = rad;
    }
  }

  cout << fixed << setprecision(18) << res << endl;
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
