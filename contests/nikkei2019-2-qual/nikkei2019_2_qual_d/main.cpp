// https://atcoder.jp/contests/nikkei2019-2-qual/tasks/nikkei2019_2_qual_d

#include "algorithm"
#include "functional"
#include "iostream"
#include "numeric"
#include "queue"
#include "set"
#include "vector"
#define rep(i, to) for (ll i = 0; i < (to); ++i)
#define repf(i, from, to) for (ll i = from; i < (to); ++i)
#define repr(i, from) for (ll i = from - 1; i >= 0; --i)
#define all(vec) vec.begin(), vec.end()
#define fi first
#define se second
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

const ll INF = 1e18;

// i -> i-1 に戻る辺と、 l -> r
// に進む辺のみ考慮すれば十分。その場合のダイクストラ
void solve() {
  ll N, M;
  cin >> N >> M;

  V<V<PL>> edges(N);
  rep(i, N - 1) edges[i + 1].emplace_back(i, 0);

  rep(i, M) {
    ll l, r, c;
    cin >> l >> r >> c;
    l--, r--;
    edges[l].emplace_back(r, c);
  }

  VL dist(N, INF);
  dist[0] = 0;

  priority_queue<PL, VPL, greater<PL>> q;
  q.push({0, 0});

  while (!q.empty()) {
    auto p = q.top();
    q.pop();

    ll cost = p.first;
    ll u = p.second;

    if (cost > dist[u]) continue;

    for (auto vp : edges[u]) {
      ll v = vp.first;
      ll edge_cost = vp.second;

      ll n_cost = cost + edge_cost;
      if (chmin(dist[v], n_cost)) {
        q.push({n_cost, v});
      }
    }
  }

  ll res = dist[N - 1] == INF ? -1 : dist[N - 1];
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

// 遅延セグ木
void solve2() {
  ll N, M;
  cin >> N >> M;

  VL dist(N, INF);

  auto fm = [](ll a, ll b) { return min(a, b); };
  auto fa = [](ll &a, ll b) { a = min(a, b); };
  auto fl = [](ll &a, ll b) { a = min(a, b); };
  LazySegTree<ll, ll> st(N + 1, fm, fa, fl, INF, INF);
  st.update(0, 1, 0);

  V<tuple<ll, ll, ll>> edges(M);

  rep(i, M) {
    ll l, r, c;
    cin >> l >> r >> c;
    l--, r--;
    edges[i] = {l, r, c};
  }

  sort(all(edges));

  for (auto &e : edges) {
    auto [l, r, c] = e;
    ll min_of_range = st.get(l, r + 1);
    st.update(l, r + 1, min_of_range + c);
  }

  ll res = st.get(N - 1, N);
  if (res == INF) drop(-1);
  cout << res << endl;
}

// イベントソートのようなイメージ
void solve3() {
  ll N, M;
  cin >> N >> M;

  struct E {
    ll l, r, c;
  };

  V<V<E>> ls(N);  // ls[i]: i を左端
  V<V<E>> rs(N);  // rs[i]: i を右端

  rep(i, M) {
    ll l, r, c;
    cin >> l >> r >> c;
    l--, r--;
    ls[l].push_back({l, r, c});
    rs[r].push_back({l, r, c});
  }

  VL dist(N, INF);
  dist[0] = 0;
  multiset<ll> costs;

  rep(i, N) {
    if (!costs.empty()) {
      dist[i] = *costs.cbegin();
    }

    if (dist[i] != INF) {
      for (auto e : ls[i]) {
        costs.insert(dist[i] + e.c);
      }
    }

    for (auto e : rs[i]) {
      if (dist[e.l] + e.c < INF) {
        costs.erase(costs.find(dist[e.l] + e.c));
      }
    }
  }

  ll res = dist[N - 1] == INF ? -1 : dist[N - 1];
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
