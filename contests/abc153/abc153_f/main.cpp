// https://atcoder.jp/contests/abc153/tasks/abc153_f

#include "algorithm"
#include "cmath"
#include "functional"
#include "iostream"
#include "numeric"
#include "queue"
#include "set"
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

void solve() {
  ll N, D, A;
  cin >> N >> D >> A;

  VPL ms(N);
  VL xs(N);

  rep(i, N) {
    ll x, h;
    cin >> x >> h;
    ms[i] = {x, h};
    xs[i] = x;
  }

  sort(all(ms));
  sort(all(xs));

  auto fm = [](ll a, ll b) { return a + b; };
  auto fa = [](ll &a, ll b) { a = a + b; };
  auto fl = [](ll &a, ll b) { a = a + b; };
  LazySegTree<ll, ll> st(N, fm, fa, fl, 0, 0);

  ll res = 0;

  rep(i, N) {
    auto m = ms[i];

    ll added_ct = st[i];
    ll rest = m.se - added_ct * A;

    if (rest <= 0) continue;

    ll need_ct = (rest + A - 1) / A;

    res += need_ct;

    ll right_edge = m.fi + 2 * D;
    ll right_idx = upper_bound(all(xs), right_edge) - xs.begin();
    st.update(i, right_idx, need_ct);
  }

  drop(res);
}

void solve2() {
  ll N, D, A;
  cin >> N >> D >> A;

  VPL ms(N);

  rep(i, N) {
    cin >> ms[i].fi >> ms[i].se;
    ms[i].se = (ms[i].se + A - 1) / A;
  }

  sort(all(ms));

  ll res = 0;
  ll sum_in_range = 0;

  // fi: 無効になる x, se: 回数
  queue<PL> q;

  rep(i, N) {
    auto m = ms[i];

    while (!q.empty() && q.front().fi <= m.fi) {
      sum_in_range -= q.front().se;
      q.pop();
    }

    ll rest = m.se - sum_in_range;

    if (rest <= 0) continue;

    res += rest;
    sum_in_range += rest;

    q.push({m.fi + 2 * D + 1, rest});
  }

  cout << res << endl;
}

void solve3() {
  ll N, D, A;
  cin >> N >> D >> A;

  VPL ms(N);
  VL xs(N);

  rep(i, N) {
    cin >> ms[i].fi >> ms[i].se;
    ms[i].se = (ms[i].se + A - 1) / A;
    xs[i] = ms[i].fi;
  }

  sort(all(ms));
  sort(all(xs));

  ll res = 0;

  // いもす法で、各要素にその直前の要素を加算しておく
  // そうすることで、各要素について、その時点でいくつ足されているかがわかる
  VL imos(N + 1);

  rep(i, N) {
    auto m = ms[i];

    ll rest = m.se - imos[i];

    if (rest > 0) {
      ll non_reach_idx = upper_bound(all(xs), m.fi + 2 * D) - xs.begin();

      res += rest;
      imos[i] += rest;
      imos[non_reach_idx] -= rest;
    }

    imos[i + 1] += imos[i];
  }

  cout << res << endl;
}

void solve4() {
  ll N, D, A;
  cin >> N >> D >> A;

  VPL ms(N);
  VL xs(N);

  rep(i, N) {
    cin >> ms[i].fi >> ms[i].se;
    ms[i].se = (ms[i].se + A - 1) / A;
    xs[i] = ms[i].fi;
  }

  sort(all(ms));
  sort(all(xs));

  ll res = 0;

  // 累積和と、後で加算すべき数を持った配列を持てば十分。いもす法に寄せる必要はない
  VL to_be_added(N + 1);
  ll cur_sum = 0;

  rep(i, N) {
    auto m = ms[i];

    cur_sum += to_be_added[i];
    ll rest = m.se - cur_sum;

    if (rest <= 0) continue;

    ll non_reach_idx = upper_bound(all(xs), m.fi + 2 * D) - xs.begin();

    res += rest;
    cur_sum += rest;
    to_be_added[non_reach_idx] -= rest;
  }

  cout << res << endl;
}

struct exit_exception : public std::exception {
  const char *what() const throw() { return "Exited"; }
};

#ifndef TEST
int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  try {
    solve4();
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
