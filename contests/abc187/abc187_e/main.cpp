// https://atcoder.jp/contests/abc187/tasks/abc187_e

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

  VVL edge_list(N);
  VPL edges(N - 1);

  rep(i, N - 1) {
    ll a, b;
    cin >> a >> b;
    --a, --b;

    edge_list[a].push_back(b);
    edge_list[b].push_back(a);
    edges[i] = make_pair(a, b);
  }

  VL par(N, -1);

  {
    auto dfs = [&](auto self, ll u, ll p) -> void {
      par[u] = p;

      for (ll v : edge_list[u]) {
        if (v == p) continue;
        self(self, v, u);
      }
    };

    dfs(dfs, 0, -1);
  }

  VL added(N);  // その頂点を含む子孫に加算される値

  ll Q;
  cin >> Q;

  rep(i, Q) {
    ll t, e, x;
    cin >> t >> e >> x;

    --e;
    auto [a, b] = edges[e];
    if (t == 1) swap(a, b);
    // a → b の向きに b 以降の頂点に加算する

    if (par[b] == a) {
      added[b] += x;
    } else {
      added[0] += x;
      added[a] -= x;
    }
  }

  VL res(N);

  {
    auto dfs = [&](auto self, ll u, ll p, ll cur) -> void {
      ll n_cur = cur + added[u];
      res[u] += n_cur;

      for (ll v : edge_list[u]) {
        if (v == p) continue;
        self(self, v, u, n_cur);
      }
    };

    dfs(dfs, 0, -1, 0);
  }

  rep(i, N) cout << res[i] << "\n";
}
