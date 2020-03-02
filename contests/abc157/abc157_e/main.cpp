// https://atcoder.jp/contests/abc157/tasks/abc157_e

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
inline bool chmax(T &a, T b);
template <typename T>
inline bool chmin(T &a, T b);
void print_ints(vector<ll> v);
template <typename T>
void drop(T a);

const ll INF = 1e18;

void solve() {
  ll N, Q;
  string S;
  cin >> N >> S >> Q;

  ll char_ct = 'z' - 'a' + 1;

  V<set<ll>> char_index_set(char_ct);

  rep(i, N) {
    ll c_i = S[i] - 'a';
    char_index_set[c_i].insert(i);
  }

  auto query1 = [&](ll i, char c) {
    i--;
    ll cur_c_i = S[i] - 'a';
    ll new_c_i = c - 'a';

    char_index_set[cur_c_i].erase(i);
    char_index_set[new_c_i].insert(i);
    S[i] = c;
  };

  auto query2 = [&](ll l, ll r) {
    l--, r--;
    ll res = 0;

    rep(i, char_ct) {
      auto first_it = char_index_set[i].lower_bound(l);
      unless(first_it != char_index_set[i].end()) continue;

      ll first_i = *first_it;
      if (first_i <= r) ++res;

      // auto first_it = char_index_set[i].lower_bound(l);
      // auto second_it = char_index_set[i].upper_bound(r);

      // if (first_it != second_it) ++res;
    }

    // 以下でも可
    // rep(i, char_ct) {
    //   auto first_it = char_index_set[i].lower_bound(l);
    //   auto second_it = char_index_set[i].upper_bound(r);

    //   if (first_it != second_it) ++res;
    // }

    cout << res << endl;
  };

  rep(i, Q) {
    ll type;
    cin >> type;

    if (type == 1) {
      ll char_i;
      char c;
      cin >> char_i >> c;
      query1(char_i, c);
    } else if (type == 2) {
      ll from, to;
      cin >> from >> to;
      query2(from, to);
    }
  }
}

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

// セグ木
void solve2() {
  ll N, Q;
  string S;
  cin >> N >> S >> Q;

  ll char_ct = 'z' - 'a' + 1;
  V<SegmentTree<ll>> sts;

  {
    VL default_values(N);

    rep(i, char_ct) {
      sts.emplace_back(SegmentTree<ll>(default_values, 0ll,
                                       [](ll a, ll b) { return a + b; }));
    }
  }

  rep(i, N) {
    ll c_i = S[i] - 'a';
    sts[c_i].update(i, 1);
  }

  auto query1 = [&](ll i, char c) {
    i--;
    ll cur_c_i = S[i] - 'a';
    ll new_c_i = c - 'a';

    sts[cur_c_i].update(i, 0);
    sts[new_c_i].update(i, 1);
    S[i] = c;
  };

  auto query2 = [&](ll l, ll r) {
    l--, r--;
    ll res = 0;

    rep(i, char_ct) if (sts[i].query(l, r + 1) > 0) { ++res; }

    cout << res << endl;
  };

  rep(i, Q) {
    ll type;
    cin >> type;

    if (type == 1) {
      ll char_i;
      char c;
      cin >> char_i >> c;
      query1(char_i, c);
    } else if (type == 2) {
      ll from, to;
      cin >> from >> to;
      query2(from, to);
    }
  }
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

// 遅延セグ木でも可
void solve3() {
  ll N, Q;
  string S;
  cin >> N >> S >> Q;

  auto fm = [](ll a, ll b) { return a + b; };
  auto fa = [](ll &a, ll b) { a = a + b; };
  auto fl = [](ll &a, ll b) { a = a + b; };

  ll char_ct = 'z' - 'a' + 1;
  V<LazySegTree<ll, ll>> sts;

  rep(i, char_ct) {
    sts.emplace_back(LazySegTree<ll, ll>(N, fm, fa, fl, 0ll, 0ll));
  }

  rep(i, N) {
    ll c_i = S[i] - 'a';
    sts[c_i].update(i, i + 1, 1);
  }

  auto query1 = [&](ll i, char c) {
    i--;
    ll cur_c_i = S[i] - 'a';
    ll new_c_i = c - 'a';

    sts[cur_c_i].update(i, i + 1, -1);
    sts[new_c_i].update(i, i + 1, 1);
    S[i] = c;
  };

  auto query2 = [&](ll l, ll r) {
    l--, r--;
    ll res = 0;

    rep(i, char_ct) if (sts[i].get(l, r + 1) > 0) { ++res; }

    cout << res << endl;
  };

  rep(i, Q) {
    ll type;
    cin >> type;

    if (type == 1) {
      ll char_i;
      char c;
      cin >> char_i >> c;
      query1(char_i, c);
    } else if (type == 2) {
      ll from, to;
      cin >> from >> to;
      query2(from, to);
    }
  }
}

struct exit_exception : public std::exception {
  const char *what() const throw() { return "Exited"; }
};

#ifndef TEST
int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  try {
    solve3();
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
