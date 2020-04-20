#include "algorithm"
#include "iostream"
#include "map"
#include "vector"
#define rep(i, from, to) for (ll i = from; i < (to); ++i)
using namespace std;
template <typename T>
using V = vector<T>;
using VL = V<ll>;
using VVL = V<VL>;
typedef long long ll;

struct LCA {
  VVL parent;  // parent[d][v] := 2^d-th parent of v
  VL depth;

  LCA() {}
  LCA(const VVL& edge_list, ll r = 0) { init(edge_list, r); }

  void init(const VVL& edge_list, ll r = 0) {
    ll V = edge_list.size();
    ll h = 1;
    while ((1 << h) < V) ++h;
    parent.assign(h, VL(V, -1));
    depth.assign(V, -1);
    dfs(edge_list, r, -1, 0);
    for (ll i = 0; i + 1 < (ll)parent.size(); ++i)
      for (ll v = 0; v < V; ++v)
        if (parent[i][v] != -1) parent[i + 1][v] = parent[i][parent[i][v]];
  }

  void dfs(const VVL& edge_list, ll v, ll p, ll d) {
    parent[0][v] = p;
    depth[v] = d;
    for (auto e : edge_list[v])
      if (e != p) dfs(edge_list, e, v, d + 1);
  }

  ll get(ll u, ll v) {
    if (depth[u] > depth[v]) swap(u, v);
    for (ll i = 0; i < (ll)parent.size(); ++i)
      if ((depth[v] - depth[u]) & (1 << i)) v = parent[i][v];
    if (u == v) return u;
    for (ll i = (ll)parent.size() - 1; i >= 0; --i) {
      if (parent[i][u] != parent[i][v]) {
        u = parent[i][u];
        v = parent[i][v];
      }
    }
    return parent[0][u];
  }
};
