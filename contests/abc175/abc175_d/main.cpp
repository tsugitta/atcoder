// https://atcoder.jp/contests/abc175/tasks/abc175_d

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

struct UnionFind {
  vector<ll> parents;

  UnionFind(ll n) : parents(vector<ll>(n, -1)) {}

  ll root(ll a) {
    if (parents[a] < 0) {
      return a;
    }

    auto r = root(parents[a]);
    parents[a] = r;
    return r;
  }

  bool same(ll a, ll b) { return root(a) == root(b); }

  void merge(ll a, ll b) {
    ll ar = root(a);
    ll br = root(b);

    if (ar == br) {
      return;
    }

    // make less index one as a root
    if (ar > br) {
      swap(ar, br);
    }

    parents[ar] += parents[br];
    parents[br] = ar;
  }

  ll size(ll a) { return -parents[a]; }

  ll group_count() {
    ll res = 0;

    for (auto s : parents) {
      if (s < 0) {
        res++;
      }
    }

    return res;
  }
};

void solve() {
  ll N, K;
  cin >> N >> K;

  VL ps(N);
  rep(i, N) cin >> ps[i];
  rep(i, N) ps[i]--;

  VL cs(N);
  rep(i, N) cin >> cs[i];

  UnionFind uf(N);

  rep(i, N) uf.merge(i, ps[i]);

  VL loop_size(N);
  VL loop_sum(N);

  rep(i, N) {
    ll root = uf.root(i);
    loop_size[root]++;
    loop_sum[root] += cs[i];
  }

  ll res = -INF;

  rep(start, N) {
    ll root = uf.root(start);

    ll max_sum = -INF;
    ll cur_sum = 0;
    ll rest = K;

    // 最後の一周は途中で止めるのがベストなケースもあるため、ループの和がプラスでも１周分シミュレートできるようにする
    if (2 * loop_size[root] <= K && loop_sum[root] > 0) {
      ll loop_ct = K / loop_size[root] - 1;
      cur_sum += loop_sum[root] * loop_ct;
      rest -= loop_ct * loop_size[root];
      chmax(max_sum, cur_sum);
    }

    if (rest == 0) {
      chmax(res, max_sum);
      continue;
    }

    if (rest >= 2 * loop_size[root]) {
      rest %= loop_size[root];
      rest += loop_size[root];
    }

    ll cur = start;

    while (rest--) {
      cur_sum += cs[cur];
      chmax(max_sum, cur_sum);
      cur = ps[cur];
    }

    chmax(res, max_sum);
  }

  cout << res << "\n";
}

void solve2() {
  ll N, K;
  cin >> N >> K;

  VL ps(N);
  rep(i, N) cin >> ps[i];
  rep(i, N) ps[i]--;

  VL cs(N);
  rep(i, N) cin >> cs[i];

  int D = 30;
  VVL nexts(D, VL(N));
  VVL sums(D, VL(N));
  VVL max_sums(D, VL(N));

  rep(i, N) {
    nexts[0][i] = ps[i];
    sums[0][i] = cs[i];
    max_sums[0][i] = cs[i];
  }

  rep(d, D - 1) {
    rep(i, N) {
      nexts[d + 1][i] = nexts[d][nexts[d][i]];
      sums[d + 1][i] = sums[d][i] + sums[d][nexts[d][i]];
      max_sums[d + 1][i] =
          max(max_sums[d][i], sums[d][i] + max_sums[d][nexts[d][i]]);
    }
  }

  ll res = -INF;

  rep(i, N) {
    ll sum = 0;
    ll offset = i;

    repr(d, D) {
      if (K & (1LL << d)) {
        chmax(res, sum + max_sums[d][offset]);
        sum += sums[d][offset];
        offset = nexts[d][offset];
      }
    }
  }

  cout << res << "\n";
}
