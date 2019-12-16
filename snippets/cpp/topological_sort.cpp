#include "algorithm"
#include "iostream"
#include "set"
#include "vector"
#define rep(i, to) for (ll i = 0; i < (to); ++i)
using namespace std;
template <typename T>
using V = vector<T>;
using VL = V<ll>;
using VVL = V<VL>;
typedef long long ll;
template <typename T>
inline bool chmax(T& a, T b);

struct TopologicalSort {
  VVL edges;
  VL sorted, length;

  TopologicalSort(ll n) : edges(VVL(n, VL(0))), length(VL(n, 1)) {}

  void add(ll from, ll to) { edges[from].push_back(to); }

  // 戻り値: isLoop
  bool sort() {
    ll n = edges.size();
    VL in_count(n);

    rep(i, n) {
      for (auto to : edges[n]) in_count[to]++;
    }

    set<ll> in_count_zeros;

    rep(i, n) {
      if (in_count[i] == 0) in_count_zeros.insert(i);
    }

    VL res(0);

    while (in_count_zeros.size() > 0) {
      ll popped = *in_count_zeros.begin();

      res.push_back(popped);
      in_count_zeros.erase(popped);

      for (auto to : edges[popped]) {
        chmax(length[to], length[popped] + 1);

        in_count[to]--;

        if (in_count[to] == 0) in_count_zeros.insert(to);
      }
    }

    sorted = res;

    return res.size() != edges.size();
  }
};

template <typename T>
inline bool chmax(T& a, T b) {
  if (a < b) {
    a = b;
    return 1;
  }
  return 0;
}
