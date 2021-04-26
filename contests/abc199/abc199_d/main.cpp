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
