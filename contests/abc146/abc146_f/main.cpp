// https://atcoder.jp/contests/abc146/tasks/abc146_f

#include "algorithm"
#include "cmath"
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

void solve() {
  ll N, M;
  cin >> N >> M;
  string S;
  cin >> S;

  VL rev_steps(0);
  ll cur = N;

  while (cur > 0) {
    ll next_step = M;

    while (cur - next_step < 0 || S[cur - next_step] == '1') {
      next_step--;
      if (next_step == 0) drop(-1);
    }

    rev_steps.push_back(next_step);
    cur -= next_step;
  }

  reverse(all(rev_steps));

  print_ints(rev_steps);
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
  ll N, M;
  cin >> N >> M;
  string S;
  cin >> S;

  auto fm = [](ll a, ll b) { return min(a, b); };
  auto fa = [](ll &a, ll b) { a = min(a, b); };
  auto fl = [](ll &a, ll b) { a = min(a, b); };
  // st[i]: i からゴールまでにかかる最小ステップ
  LazySegTree<ll, ll> st(N + 1, fm, fa, fl, INF, INF);
  st.update(N, N + 1, 0);

  repr(i, N) {
    if (S[i] == '1') continue;
    ll last = st.get(i + 1, min(i + M + 1, N + 1));
    st.update(i, i + 1, last + 1);
  }

  if (st[0] == INF) drop(-1);

  VL res(0);

  {
    ll cur = 0;

    while (cur < N) {
      ll next = cur;

      while (st[next] == INF || st[cur] == st[next]) next++;

      res.push_back(next - cur);
      cur = next;
    }
  }

  print_ints(res);
}

void solve3() {
  ll N, M;
  cin >> N >> M;
  string S;
  cin >> S;

  // dp[i]: i からゴールまでにかかる最小ステップ
  VL dp(N + 1, INF);
  dp[N] = 0;

  queue<ll> q;
  q.push(dp[N]);

  repr(i, N) {
    while (1) {
      if (q.size() == 0) drop(-1);

      if (q.front() != INF && q.size() <= M) break;
      q.pop();
    }

    if (S[i] != '1') dp[i] = q.front() + 1;
    q.push(dp[i]);
  }

  VL res(0);

  {
    ll cur = 0;

    while (cur < N) {
      ll next = cur;

      while (dp[next] == INF || dp[cur] == dp[next]) next++;

      res.push_back(next - cur);
      cur = next;
    }
  }

  print_ints(res);
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
