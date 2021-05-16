// https://atcoder.jp/contests/abc201/tasks/abc201_e

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
#include "vector"
#define rep(i, to) for (ll i = 0; i < ((ll)to); ++i)
#define rep1(i, to) for (ll i = 1; i <= ((ll)to); ++i)
#define repf(i, from, to) for (ll i = from; i < ((ll)to); ++i)
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

using mint = modint1000000007;

void solve() {
  ll N;
  cin >> N;

  struct Edge {
    ll to, cost;
  };

  VV<Edge> edge_list(N);

  rep(i, N - 1) {
    ll u, v, w;
    cin >> u >> v >> w;
    --u, --v;

    edge_list[u].push_back({v, w});
    edge_list[v].push_back({u, w});
  }

  VL dist(N);

  {
    auto dfs = [&](auto&& dfs, ll u, ll p, ll& cur_dist) -> void {
      dist[u] = cur_dist;

      for (auto [v, cost] : edge_list[u]) {
        if (v == p) continue;

        cur_dist ^= cost;

        dfs(dfs, v, u, cur_dist);

        cur_dist ^= cost;
      }
    };

    ll cur_dist = 0;
    dfs(dfs, 0, -1, cur_dist);
  }

  mint res = 0;

  rep(bit, 63) {
    VL popcount_to_ct(2);

    rep(i, N) {
      bool popcount = dist[i] & (1ll << bit);

      popcount_to_ct[popcount]++;
    }

    res += mint(1) * popcount_to_ct[0] * popcount_to_ct[1] * (1ll << bit);
  }

  cout << res.val() << "\n";
}
