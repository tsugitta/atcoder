#include "algorithm"
#include "iostream"
#include "map"
#include "vector"
#define rep(i, to) for (ll i = 0; i < (to); ++i)
using namespace std;
typedef long long ll;

struct BipartiteMatching {
  vector<vector<ll>> edges;
  vector<ll> match;
  vector<bool> used;

  BipartiteMatching(ll n)
      : edges(vector<vector<ll>>(n)), match(vector<ll>(n, -1)) {}

  void add(ll from, ll to) {
    edges[from].push_back(to);
    edges[to].push_back(from);
  }

  bool dfs(ll v) {
    used[v] = true;

    for (auto u : edges[v]) {
      ll w = match[u];
      if (w == -1 || !used[w] && dfs(w)) {
        match[u] = v;
        match[v] = u;
        return true;
      }
    }

    return false;
  }

  ll call() {
    ll res = 0;

    rep(v, edges.size()) {
      if (match[v] == -1) {
        used = vector<bool>(edges.size());

        if (dfs(v)) {
          res++;
        }
      }
    }

    return res;
  }
};
