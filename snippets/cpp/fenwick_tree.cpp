#include "algorithm"
#include "iostream"
#include "map"
#include "vector"
#define rep(i, from, to) for (ll i = from; i < (to); ++i)
using namespace std;
typedef long long ll;

struct Fenwick {
  vector<ll> tree;

  Fenwick(ll n) : tree(vector<ll>(n, 0)) {}

  // sum of [0, i)
  ll sum(ll i) {
    ll res = 0;

    for (i--; i >= 0; i = (i & (i + 1)) - 1) {
      res += tree[i];
    }

    return res;
  }

  void add(ll i, ll n) {
    for (ll len = tree.size(); i < len; i |= i + 1) {
      tree[i] += n;
    }
  }
};
