// https://atcoder.jp/contests/abc199/tasks/abc199_d

#include <atcoder/all>

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
#include "unordered_map"
#include "unordered_set"
#include "vector"
#define rep(i, to) for (ll i = 0; i < (to); ++i)
#define rep1(i, to) for (ll i = 1; i <= (to); ++i)
#define repf(i, from, to) for (ll i = from; i < (to); ++i)
#define repr(i, from) for (ll i = from - 1; i >= 0; --i)
#define all(vec) vec.begin(), vec.end()
#define unless(cond) if (!(cond))
#define fi first
#define se second
#define i128 __int128_t
using namespace std;
using namespace atcoder;
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

// 1. 赤で塗る色を固定
// 2. 残りの各連結成分が二部グラフになっているか判定
// 3. 連結成分の塗り方は 2 通りなので、2^(連結成分数)を加算
void solve() {
  ll N, M;
  cin >> N >> M;

  VVL edge_list(N, VL(0));

  rep(i, M) {
    ll a, b;
    cin >> a >> b;
    --a, --b;

    edge_list[a].push_back(b);
    edge_list[b].push_back(a);
  }

  ll res = 0;

  auto get_count_for_bit = [&](ll bit) {
    V<bool> visited(N);
    ll group_ct = 0;
    bool is_bipartite = true;
    VL colors(N, -1);  // -1: 未, 0, 1: 色

    // 二部グラフか判定
    // u の色を決めてから呼び出す
    auto dfs = [&](auto self, ll u, ll p) {
      if (!is_bipartite) return;
      visited[u] = true;

      for (ll v : edge_list[u]) {
        if (v == p) continue;
        if (bit & (1 << v)) continue;

        if (colors[v] == colors[u]) {
          is_bipartite = false;
          return;
        }

        if (colors[v] != -1) continue;

        colors[v] = 1 - colors[u];
        self(self, v, u);
      }
    };

    rep(i, N) {
      if (!is_bipartite) break;
      if (visited[i]) continue;
      if (bit & (1 << i)) continue;

      colors[i] = 0;
      dfs(dfs, i, -1);
      ++group_ct;
    }

    return is_bipartite ? pow(2, group_ct) : 0;
  };

  // 赤が連続していないか
  auto is_ok_for_red = [&](ll bit) {
    rep(i, N) {
      unless(bit & (1 << i)) continue;

      for (ll j : edge_list[i]) {
        if (bit & (1 << j)) return false;
      }
    }

    return true;
  };

  rep(bit, 1 << N) {
    if (is_ok_for_red(bit)) {
      res += get_count_for_bit(bit);
    }
  }

  cout << res << "\n";
}

// 各連結成分について、一つのノードの色を固定
// 隣接する頂点の色の高々 2 通りを全探索
void solve2() {
  ll N, M;
  cin >> N >> M;

  VVL edge_list(N, VL(0));
  dsu uf(N);

  rep(i, M) {
    ll a, b;
    cin >> a >> b;
    --a, --b;

    edge_list[a].push_back(b);
    edge_list[b].push_back(a);
    uf.merge(a, b);
  }

  // DFS の途中で既に訪れた頂点に再度訪れる時、その頂点の色を知る必要がある
  // → 経路中の頂点の色を持ち、バックトラックで管理する
  VL colors(N, -1);  // -1: 未, 0, 1, 2: 色

  // あるノードが色づけられるルートを１つに固定する。
  VL parent_node(N, -1);

  // `dfs` 内では枝刈りしているため、状況によって通るノード順が変わってしまう
  // そのため、 `dfs` 内で parent_node を埋めず、決定的に埋めるようにする
  auto dfs_to_fill_parent = [&](auto self, ll u) -> void {
    for (ll v : edge_list[u]) {
      unless(parent_node[v] == -1) continue;
      parent_node[v] = u;
      self(self, v);
    }
  };

  // colors[u] を埋めてから呼び出す
  auto dfs = [&](auto dfs, ll u) -> ll {
    for (ll v : edge_list[u]) {
      if (colors[v] == colors[u]) return 0;
    }

    ll res = 1;

    for (ll v : edge_list[u]) {
      unless(colors[v] == -1) continue;

      if (parent_node[v] == -1) parent_node[v] = u;
      unless(parent_node[v] == u) continue;

      ll res_v = 0;

      colors[v] = (colors[u] + 1) % 3;
      res_v += dfs(dfs, v);
      colors[v] = (colors[u] + 2) % 3;
      res_v += dfs(dfs, v);
      colors[v] = -1;

      res *= res_v;
    }

    return res;
  };

  ll res = 1;

  for (auto group : uf.groups()) {
    ll root = group.front();
    parent_node[root] = INF;
    dfs_to_fill_parent(dfs_to_fill_parent, root);
    colors[root] = 0;
    res *= 3 * dfs(dfs, root);
    colors[root] = -1;
  }

  cout << res << "\n";
}
