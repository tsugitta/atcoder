// https://atcoder.jp/contests/abc125/tasks/abc125_c

#include "algorithm"
#include "functional"
#include "iostream"
#include "numeric"
#include "queue"
#include "set"
#include "vector"
#define rep(i, to) for (ll i = 0; i < (to); ++i)
#define repf(i, from, to) for (ll i = from; i < (to); ++i)
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

ll mygcd(ll a, ll b) { return b ? mygcd(b, a % b) : a; }

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

void solve() {
  ll N;
  cin >> N;
  VL as(N);
  rep(i, N) cin >> as[i];

  SegmentTree<ll> st(as, 0ll, mygcd);

  ll res = 0;

  rep(i, N) {
    ll l = st.query(0, i);
    ll r = st.query(i + 1, as.size());
    chmax(res, mygcd(l, r));
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
