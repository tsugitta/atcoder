// https://atcoder.jp/contests/zone2021/tasks/zone2021_e

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

void solve() {
  ll R, C;
  cin >> R >> C;

  VVL a_mat(R, VL(C - 1));
  rep(r, R) rep(c, C - 1) cin >> a_mat[r][c];

  VVL b_mat(R - 1, VL(C));
  rep(r, R - 1) rep(c, C) cin >> b_mat[r][c];

  ll NODE_CT = 2 * R * C;

  struct Edge {
    ll to, cost;
  };

  VV<Edge> edge_list(NODE_CT);

  auto to_id = [&](ll r, ll c, bool is_r_back = false) {
    return r * C + c + (is_r_back ? R * C : 0);
  };

  rep(r, R) rep(c, C) {
    ll id = to_id(r, c);

    if (c + 1 < C) edge_list[id].push_back({to_id(r, c + 1), a_mat[r][c]});
    if (c > 0) edge_list[id].push_back({to_id(r, c - 1), a_mat[r][c - 1]});
    if (r + 1 < R) edge_list[id].push_back({to_id(r + 1, c), b_mat[r][c]});

    edge_list[id].push_back({to_id(r, c, true), 1});
  }

  rep(r, R) rep(c, C) {
    ll id = to_id(r, c, true);

    if (r > 0) edge_list[id].push_back({to_id(r - 1, c, true), 1});

    edge_list[id].push_back({to_id(r, c), 0});
  }

  VL dist(NODE_CT, INF);
  dist[to_id(0, 0)] = 0;

  // ダイクストラ
  asc_pq<PL> q;
  q.emplace(0, to_id(0, 0));

  while (!q.empty()) {
    auto [cost, node] = q.top();
    q.pop();

    if (cost > dist[node]) continue;

    for (auto e : edge_list[node]) {
      ll n_cost = cost + e.cost;

      if (chmin(dist[e.to], n_cost)) {
        q.emplace(n_cost, e.to);
      }
    }
  }

  ll res = dist[to_id(R - 1, C - 1)];
  cout << res << "\n";
}
