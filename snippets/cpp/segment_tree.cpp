#include "algorithm"
#include "iostream"
#include "map"
#include "vector"
#define rep(i, to) for (ll i = 0; i < (to); ++i)
using namespace std;
typedef long long ll;

template <typename Monoid>
struct SegmentTree {
  ll n;  // 最下段の数
  vector<Monoid> nodes;
  using F = function<Monoid(Monoid, Monoid)>;
  const F f;
  const Monoid UNITY;

  SegmentTree(vector<Monoid> vs, const Monoid& unity, const F f)
      : UNITY(unity), f(f) {
    n = 1;

    while (n < vs.size()) {
      n *= 2;
    }

    nodes = vector<ll>(2 * n - 1, UNITY);

    rep(i, vs.size()) nodes[i + n - 1] = vs[i];

    for (ll i = n - 2; i >= 0; i--) {
      nodes[i] = f(nodes[i * 2 + 1], nodes[i * 2 + 2]);
    }
  }

  void update(Monoid i, Monoid val) {
    i += n - 1;
    nodes[i] = val;

    while (i > 0) {
      i = (i - 1) / 2;
      nodes[i] = f(nodes[2 * i + 1], nodes[2 * i + 2]);
    }
  }

  //  [from, to)
  Monoid query(ll from, ll to) {
    ll res = queryInternal(from, to, 0, 0, n);
    return res;
  }

  Monoid queryInternal(ll from, ll to, ll k, ll l, ll r) {
    if (r <= from || to <= l) {
      return UNITY;
    }

    if (from <= l && r <= to) {
      return nodes[k];
    }

    ll vl = queryInternal(from, to, 2 * k + 1, l, (l + r) / 2);
    ll vr = queryInternal(from, to, 2 * k + 2, (l + r) / 2, r);

    return f(vl, vr);
  }
};
