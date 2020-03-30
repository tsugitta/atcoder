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
inline bool chmax(T &a, T b);
template <typename T>
inline bool chmin(T &a, T b);
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

  SegmentTree(vector<Monoid> vs, const Monoid &unity, const F f)
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

template <class Monoid, class Action>
struct LazySegTree {
  using FuncMonoid = function<Monoid(Monoid, Monoid)>;
  using FuncAction = function<void(Monoid &, Action)>;
  using FuncLazy = function<void(Action &, Action)>;
  FuncMonoid FM;
  FuncAction FA;
  FuncLazy FL;
  Monoid UNITY_MONOID;
  Action UNITY_LAZY;
  ll SIZE, HEIGHT;
  vector<Monoid> dat;
  vector<Action> lazy;

  LazySegTree(ll n, const FuncMonoid fm, const FuncAction fa, const FuncLazy fl,
              const Monoid &unity_monoid, const Action &unity_lazy)
      : FM(fm),
        FA(fa),
        FL(fl),
        UNITY_MONOID(unity_monoid),
        UNITY_LAZY(unity_lazy) {
    SIZE = 1;
    HEIGHT = 0;
    while (SIZE < n) SIZE <<= 1, ++HEIGHT;
    dat.assign(SIZE * 2, UNITY_MONOID);
    lazy.assign(SIZE * 2, UNITY_LAZY);
  }

  void init(ll n, const FuncMonoid fm, const FuncAction fa, const FuncLazy fl,
            const Monoid &unity_monoid, const Action &unity_lazy) {
    FM = fm;
    FA = fa;
    FL = fl;
    UNITY_MONOID = unity_monoid;
    UNITY_LAZY = unity_lazy;
    SIZE = 1;
    HEIGHT = 0;
    while (SIZE < n) SIZE <<= 1, ++HEIGHT;
    dat.assign(SIZE * 2, UNITY_MONOID);
    lazy.assign(SIZE * 2, UNITY_LAZY);
  }

  void set(ll a, const Monoid &v) { dat[a + SIZE] = v; }

  void build() {
    for (ll k = SIZE - 1; k > 0; --k) dat[k] = FM(dat[k * 2], dat[k * 2 + 1]);
  }

  inline void evaluate(ll k) {
    if (lazy[k] == UNITY_LAZY) return;
    if (k < SIZE) FL(lazy[k * 2], lazy[k]), FL(lazy[k * 2 + 1], lazy[k]);
    FA(dat[k], lazy[k]);
    lazy[k] = UNITY_LAZY;
  }

  inline void update(ll a, ll b, const Action &v, ll k, ll l, ll r) {
    evaluate(k);
    if (a <= l && r <= b)
      FL(lazy[k], v), evaluate(k);
    else if (a < r && l < b) {
      update(a, b, v, k * 2, l, (l + r) >> 1),
          update(a, b, v, k * 2 + 1, (l + r) >> 1, r);
      dat[k] = FM(dat[k * 2], dat[k * 2 + 1]);
    }
  }

  /* [a, b) */
  inline void update(ll a, ll b, const Action &v) {
    update(a, b, v, 1, 0, SIZE);
  }

  inline Monoid get(ll a, ll b, ll k, ll l, ll r) {
    evaluate(k);
    if (a <= l && r <= b)
      return dat[k];
    else if (a < r && l < b)
      return FM(get(a, b, k * 2, l, (l + r) >> 1),
                get(a, b, k * 2 + 1, (l + r) >> 1, r));
    else
      return UNITY_MONOID;
  }

  /* [a, b) */
  inline Monoid get(ll a, ll b) { return get(a, b, 1, 0, SIZE); }

  inline Monoid operator[](ll a) { return get(a, a + 1); }
};

void solve2() {
  ll N;
  cin >> N;

  auto fm = [](ll a, ll b) { return min(a, b); };
  auto fa = [](ll &a, ll b) { a = min(a, b); };
  auto fl = [](ll &a, ll b) { a = min(a, b); };
  LazySegTree<ll, ll> st(N, fm, fa, fl, 0, 0);

  rep(i, N) {
    ll a;
    cin >> a;
    st.set(i, a);
  }

  st.build();

  ll res = 1;

  rep(i, N) { chmax(res, mygcd(st.get(0, i), st.get(i + 1, N))); }

  cout << res << "\n";
}

struct exit_exception : public std::exception {
  const char *what() const throw() { return "Exited"; }
};

#ifndef TEST
int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  try {
    solve2();
  } catch (exit_exception &e) {
  }

  return 0;
}
#endif

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
