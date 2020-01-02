// https://atcoder.jp/contests/abc075/tasks/abc075_c

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
  ll N, M;
  cin >> N >> M;

  VVL edge_list(N, VL());

  rep(i, M) {
    ll a, b;
    cin >> a >> b;
    a--, b--;

    edge_list[a].push_back(b);
    edge_list[b].push_back(a);
  }

  ll res = 0;

  rep(edge_from, N) for (auto edge_to : edge_list[edge_from]) {
    unless(edge_from < edge_to) continue;

    UnionFind uf(N);

    rep(u, N) for (auto v : edge_list[u]) {
      unless(u < v) continue;
      if (u == edge_from && v == edge_to) continue;

      uf.merge(u, v);
    }

    if (uf.group_count() == 2) res++;
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
