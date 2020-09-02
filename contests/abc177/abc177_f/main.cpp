// https://atcoder.jp/contests/abc177/tasks/abc177_f

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
void solve2();

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

void solve() {
  ll H, W;
  cin >> H >> W;

  map<int, int> pos_to_start;
  multiset<int> min_steps;

  rep(w, W) {
    pos_to_start[w] = w;
    min_steps.insert(0);
  }

  rep(h, H) {
    ll l, r;
    cin >> l >> r;
    --l;

    auto it = pos_to_start.lower_bound(l);

    int most_right = -1;

    while (it != pos_to_start.end()) {
      auto [pos, start] = *it;
      unless(pos <= r) break;

      chmax(most_right, start);
      int diff = pos - start;
      min_steps.erase(min_steps.find(diff));
      pos_to_start.erase(it++);
    }

    if (most_right != -1 && r < W) {
      min_steps.insert(r - most_right);
      pos_to_start[r] = most_right;
    }

    int res = -1;
    if (min_steps.size() > 0) {
      res = *min_steps.begin() + (h + 1);
    }

    cout << res << "\n";
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

// multiset の代わりにセグメントツリーを使う
void solve2() {
  ll H, W;
  cin >> H >> W;

  map<int, int> pos_to_start;

  VL st_default(W);
  SegmentTree<ll> st(st_default, INF, [](ll a, ll b) { return min(a, b); });

  rep(w, W) {
    pos_to_start[w] = w;
    st.update(w, 0);
  }

  rep(h, H) {
    ll l, r;
    cin >> l >> r;
    --l;

    auto it = pos_to_start.lower_bound(l);

    int most_right = -1;

    while (it != pos_to_start.end()) {
      auto [pos, start] = *it;
      unless(pos <= r) break;

      chmax(most_right, start);
      st.update(pos, INF);
      pos_to_start.erase(it++);
    }

    if (most_right != -1 && r < W) {
      st.update(r, r - most_right);
      pos_to_start[r] = most_right;
    }

    ll res = st.query(0, W);

    if (res == INF) {
      cout << -1 << "\n";
      continue;
    }

    cout << res + h + 1 << "\n";
  }
}
