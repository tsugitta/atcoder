// https://atcoder.jp/contests/aising2019/tasks/aising2019_c

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

VL dx = {1, 0, -1, 0};
VL dy = {0, 1, 0, -1};

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
  ll H, W;
  cin >> H >> W;

  V<string> mat(H);
  rep(h, H) cin >> mat[h];

  ll N = H * W;
  VVL edge_list(N, VL(0));

  rep(h, H) rep(w, W) {
    ll u = h * W + w;

    rep(di, 4) {
      ll nh = h + dy[di];
      ll nw = w + dx[di];

      unless(0 <= nh && nh < H && 0 <= nw && nw < W) continue;
      unless(mat[h][w] != mat[nh][nw]) continue;

      ll v = nh * W + nw;

      edge_list[u].emplace_back(v);
      edge_list[v].emplace_back(u);
    }
  }

  UnionFind uf(N);

  rep(u, N) {
    for (auto v : edge_list[u]) {
      uf.merge(u, v);
    }
  }

  auto id_to_char = [&](ll id) {
    ll h = id / W;
    ll w = id % W;
    return mat[h][w];
  };

  map<ll, ll> b_ct_map;
  map<ll, ll> w_ct_map;

  rep(i, N) {
    ll r = uf.root(i);
    ll c = id_to_char(i);

    if (c == '#') {
      b_ct_map[r]++;
    } else {
      w_ct_map[r]++;
    }
  }

  ll res = 0;

  for (auto b_pair : b_ct_map) {
    ll r = b_pair.fi;
    ll b_ct = b_pair.se;
    ll w_ct = w_ct_map[r];

    res += b_ct * w_ct;
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
