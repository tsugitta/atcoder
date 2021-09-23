// https://atcoder.jp/contests/abc218/tasks/abc218_g

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

// multiset を 2 つ持つ
void solve() {
  ll N;
  cin >> N;

  VL as(N);
  for (ll& a : as) cin >> a;

  VVL edge_list(N);
  rep(i, N - 1) {
    ll u, v;
    cin >> u >> v;
    --u, --v;
    edge_list[u].push_back(v);
    edge_list[v].push_back(u);
  }

  // 常に lows.size() == highs.size() or highs.size()+1 とする
  multiset<ll> lows;
  multiset<ll> highs;

  auto add = [&](ll val) {
    lows.insert(val);
    auto it = lows.end();
    --it;
    ll num = *it;
    lows.erase(it);
    highs.insert(num);

    unless(lows.size() >= highs.size()) {
      auto it = highs.begin();
      ll num = *it;
      highs.erase(it);
      lows.insert(num);
    }
  };

  auto remove = [&](ll val) {
    if (highs.find(val) != highs.end()) {
      highs.erase(highs.find(val));
    } else {
      lows.erase(lows.find(val));
    }

    if (lows.size() < highs.size()) {
      auto it = highs.begin();
      ll num = *it;
      highs.erase(it);
      lows.insert(num);
    }

    if (lows.size() == highs.size() + 2) {
      auto it = lows.end();
      --it;
      ll num = *it;
      lows.erase(it);
      highs.insert(num);
    }
  };

  auto get_median = [&]() -> ll {
    if (lows.size() == highs.size()) {
      return (*lows.rbegin() + *highs.begin()) / 2;
    } else {
      return *lows.rbegin();
    }
  };

  // その頂点を触る人にとって最善に動かした時の最終値
  VL dp(N);

  auto dfs = [&](auto dfs, ll u, ll p, ll depth) -> void {
    ll mi = INF;
    ll ma = -INF;

    add(as[u]);

    for (ll v : edge_list[u]) {
      if (v == p) continue;
      dfs(dfs, v, u, depth + 1);
      chmin(mi, dp[v]);
      chmax(ma, dp[v]);
    }

    // 葉の場合
    if (mi == INF) {
      dp[u] = get_median();
    } else {
      if (depth % 2 == 0) {  // 先手: 最大化させる
        dp[u] = ma;
      } else {  // 後手: 最小化させる
        dp[u] = mi;
      }
    }

    remove(as[u]);
  };

  dfs(dfs, 0, -1, 0);

  cout << dp[0] << "\n";
}

// 座標圧縮 + BIT 上の二分探索
void solve2() {
  ll N;
  cin >> N;

  VL as(N);
  for (ll& a : as) cin >> a;

  VVL edge_list(N);
  rep(i, N - 1) {
    ll u, v;
    cin >> u >> v;
    --u, --v;
    edge_list[u].push_back(v);
    edge_list[v].push_back(u);
  }

  // 座標圧縮
  VL vals = as;
  sort(all(vals));
  vals.erase(unique(all(vals)), vals.end());

  map<ll, ll> num_to_i;
  rep(i, vals.size()) num_to_i[vals[i]] = i;

  fenwick_tree<ll> bit(vals.size());

  auto add = [&](ll val) { bit.add(num_to_i[val], 1); };

  auto remove = [&](ll val) { bit.add(num_to_i[val], -1); };

  // n: [1, vals.size()]
  auto get_nth_from_lower = [&](ll n) -> ll {
    ll total = bit.sum(0, vals.size());

    assert(n <= total);

    ll ng = -1;
    ll ok = vals.size() - 1;

    while (ok - ng > 1) {
      ll mid = (ok + ng) / 2;

      if (bit.sum(0, mid + 1) >= n) {
        ok = mid;
      } else {
        ng = mid;
      }
    }

    return vals[ok];
  };

  auto get_median = [&]() -> ll {
    ll total = bit.sum(0, vals.size());

    if (total % 2 == 1) {
      return get_nth_from_lower(total / 2 + 1);
    } else {
      return (get_nth_from_lower(total / 2) +
              get_nth_from_lower(total / 2 + 1)) /
             2;
    }
  };

  // その頂点を触る人にとって最善に動かした時の最終値
  VL dp(N);

  auto dfs = [&](auto dfs, ll u, ll p, ll depth) -> void {
    ll mi = INF;
    ll ma = -INF;

    add(as[u]);

    for (ll v : edge_list[u]) {
      if (v == p) continue;
      dfs(dfs, v, u, depth + 1);
      chmin(mi, dp[v]);
      chmax(ma, dp[v]);
    }

    // 葉の場合
    if (mi == INF) {
      dp[u] = get_median();
    } else {
      if (depth % 2 == 0) {  // 先手: 最大化させる
        dp[u] = ma;
      } else {  // 後手: 最小化させる
        dp[u] = mi;
      }
    }

    remove(as[u]);
  };

  dfs(dfs, 0, -1, 0);

  cout << dp[0] << "\n";
}
