// https://atcoder.jp/contests/abc202/tasks/abc202_e

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

// マージテク
// 各頂点について、その部分木における深さごとの個数を map で計算していく
// DFS で葉から順にこれを行う
void solve() {
  ll N;
  cin >> N;

  VVL edge_list(N);

  rep1(i, N - 1) {
    ll p;
    cin >> p;
    --p;

    // 親から子へ
    // edge_list[i].push_back(p);
    edge_list[p].push_back(i);
  }

  ll Q;
  cin >> Q;

  struct Query {
    ll index, d;
  };

  VV<Query> node_to_q(N);

  rep(i, Q) {
    ll u, d;
    cin >> u >> d;
    --u;
    node_to_q[u].push_back({i, d});
  }

  VL res(Q);

  auto dfs = [&](auto dfs, ll u, ll d = 0) -> map<ll, ll> {
    map<ll, ll> d_to_ct;
    d_to_ct[d] = 1;

    for (auto v : edge_list[u]) {
      auto c_d_to_ct = dfs(dfs, v, d + 1);

      if (c_d_to_ct.size() > d_to_ct.size()) {
        swap(c_d_to_ct, d_to_ct);
      }

      for (auto [k, v] : c_d_to_ct) {
        d_to_ct[k] += v;
      }
    }

    for (auto [q_i, q_d] : node_to_q[u]) {
      res[q_i] = d_to_ct[q_d];
    }

    return d_to_ct;
  };

  dfs(dfs, 0);

  for (auto r : res) cout << r << "\n";
}
