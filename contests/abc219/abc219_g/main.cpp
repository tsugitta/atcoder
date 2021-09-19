// https://atcoder.jp/contests/abc219/tasks/abc219_g

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
  ll N, M, Q;
  cin >> N >> M >> Q;

  VL degs(N);
  VVL edge_list(N);
  VVL to_large_edge_list(N);  // 次数が一定以上の頂点への辺
  ll DEGREE_THRESHOLD = sqrt(M);

  rep(i, M) {
    ll u, v;
    cin >> u >> v;
    --u, --v;
    edge_list[u].push_back(v);
    edge_list[v].push_back(u);
    ++degs[u];
    ++degs[v];
  }

  rep(u, N) {
    for (ll v : edge_list[u]) {
      if (degs[v] >= DEGREE_THRESHOLD) to_large_edge_list[u].push_back(v);
    }
  }

  ll IS_INITIAL_STATE = -1;
  VPL cur(N);  // {クエリ番号, 値}
  rep(i, N) cur[i] = {IS_INITIAL_STATE, i + 1};

  VPL updates(N);  // {クエリ番号, 値}

  auto update_from_large_node = [&](ll u) {
    ll last_q_i = -INF;
    ll last_q_val = -1;

    for (ll v : to_large_edge_list[u]) {
      auto& [q_i, new_val] = updates[v];

      if (new_val) {
        if (chmax(last_q_i, q_i)) last_q_val = new_val;
      }
    }

    auto& [cur_q_i, cur_val] = cur[u];
    unless(last_q_val != -1 &&
           (last_q_i > cur_q_i || cur_q_i == IS_INITIAL_STATE)) return;

    cur_q_i = last_q_i;
    cur_val = last_q_val;
  };

  rep(q_i, Q) {
    ll u;
    cin >> u;
    --u;

    update_from_large_node(u);

    cur[u].fi = q_i;

    if (degs[u] >= DEGREE_THRESHOLD) {
      updates[u] = cur[u];
    } else {
      for (ll v : edge_list[u]) {
        cur[v] = cur[u];
      }
    }
  }

  rep(u, N) update_from_large_node(u);

  rep(i, cur.size()) {
    if (i > 0) cout << " ";
    cout << cur[i].se;
  }
  cout << "\n";
}
