// https://atcoder.jp/contests/abc152/tasks/abc152_f

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

struct Edge {
  ll to, id;

  Edge(ll to, ll id) : to(to), id(id) {}
};

// u から goal までの nodes
bool dfs(ll u, ll goal, V<V<Edge>>& edge_list, VL& path_edge, ll p = -1) {
  if (u == goal) return true;

  for (Edge e : edge_list[u]) {
    if (e.to == p) continue;
    if (dfs(e.to, goal, edge_list, path_edge, u)) {
      path_edge.emplace_back(e.id);
      return true;
    }
  }

  return false;
}

void solve() {
  ll N;
  cin >> N;

  V<V<Edge>> edge_list(N);

  rep(i, N - 1) {
    ll a, b;
    cin >> a >> b;
    --a, --b;
    edge_list[a].emplace_back(b, i);
    edge_list[b].emplace_back(a, i);
  }

  ll M;
  cin >> M;

  // 各制約の点間のパスの bit 配列
  VL edge_bits(M);

  rep(i, M) {
    ll a, b;
    cin >> a >> b;
    --a, --b;

    VL path_edge(0);
    dfs(a, b, edge_list, path_edge);

    for (ll id : path_edge) {
      edge_bits[i] |= 1ll << id;
    }
  }

  // ある制約が満たされない場合の数
  ll not_satisfying = 0;

  // 各制約の組み合わせについて、その制約全てを満たさない（全てが白）ケースを考えて、包除原理により
  // not_satisfying を得る
  rep(i, 1ll << M) {
    if (i == 0) continue;

    ll edge_bit = 0;

    rep(j, M) {
      if (i & (1ll << j)) edge_bit |= edge_bits[j];
    }

    ll white_ct = __builtin_popcountll(edge_bit);
    ll constraint_ct = __builtin_popcountll(i);
    ll case_ct = 1ll << (N - 1 - white_ct);  // 制約の辺が全て白である個数

    if (constraint_ct % 2 == 1) {
      not_satisfying += case_ct;
    } else {
      not_satisfying -= case_ct;
    }
  }

  ll res = (1ll << (N - 1)) - not_satisfying;

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
