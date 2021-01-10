// https://atcoder.jp/contests/arc111/tasks/arc111_b

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
#define rep(i, to) for (ll i = 0; i < (to); ++i)
#define rep1(i, to) for (ll i = 1; i <= (to); ++i)
#define repf(i, from, to) for (ll i = from; i < (to); ++i)
#define repr(i, from) for (ll i = from - 1; i >= 0; --i)
#define all(vec) vec.begin(), vec.end()
#define unless(cond) if (!(cond))
#define fi first
#define se second
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

void solve() {
  ll N;
  cin >> N;

  ll color_ct = 4e5;
  VVL edge_list(color_ct);

  rep(i, N) {
    ll a, b;
    cin >> a >> b;
    --a, --b;
    edge_list[a].push_back(b);
    edge_list[b].push_back(a);
  }

  ll res = 0;
  V<bool> visited(color_ct);

  rep(i, color_ct) {
    if (visited[i]) continue;

    ll node_ct = 0;
    ll edge_ct = 0;

    auto dfs = [&](auto self, ll u, ll p) -> void {
      ++node_ct;
      visited[u] = true;

      for (ll v : edge_list[u]) {
        if (v == p) continue;
        ++edge_ct;

        if (!visited[v]) self(self, v, u);
      }
    };

    dfs(dfs, i, -1);

    // 木の場合は連結成分のうち一点を除いて埋められ、木でない場合は全て埋められる
    res += node_ct - (node_ct == edge_ct + 1);
  }

  cout << res << "\n";
}
