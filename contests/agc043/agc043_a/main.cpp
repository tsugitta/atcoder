// https://atcoder.jp/contests/agc043/tasks/agc043_a

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
typedef long long ll;
typedef long double ld;
template <typename T>
using V = vector<T>;
using VL = V<ll>;
using VVL = V<VL>;
template <typename T, typename U>
using P = pair<T, U>;
using PL = P<ll, ll>;
using VPL = V<PL>;
template <typename T>
inline bool chmax(T& a, T b);
template <typename T>
inline bool chmin(T& a, T b);
void print_ints(vector<ll> v);
template <typename T>
void drop(T a);

const ll INF = 1e18;

void solve() {
  ll H, W;
  cin >> H >> W;

  VL dx = {0, 1};
  VL dy = {1, 0};

  char BL = '#';
  char WH = '.';

  V<string> mat(H);
  rep(i, H) cin >> mat[i];

  VVL black_acc_ct_mat(H, VL(W, INF));
  black_acc_ct_mat[0][0] = mat[0][0] == BL ? 1 : 0;

  rep(h, H) rep(w, W) {
    rep(i, dx.size()) {
      ll nw = w + dx[i];
      ll nh = h + dy[i];
      unless(nw < W && nh < H) continue;

      chmin(black_acc_ct_mat[nh][nw],
            black_acc_ct_mat[h][w] +
                (mat[h][w] == WH && mat[nh][nw] == BL ? 1 : 0));
    }
  }

  cout << black_acc_ct_mat[H - 1][W - 1] << endl;
}

// ダイクストラ
void solve2() {
  ll H, W;
  cin >> H >> W;

  char BL = '#';
  char WH = '.';

  V<string> mat(H);
  rep(i, H) cin >> mat[i];

  ll node_ct = H * W;

  struct Edge {
    ll to, cost;
  };

  V<V<Edge>> edge_list(node_ct, V<Edge>(0));

  auto to_id = [W](ll h, ll w) { return h * W + w; };

  VL dx = {0, 1};
  VL dy = {1, 0};

  rep(h, H) rep(w, W) {
    rep(i, dx.size()) {
      ll nw = w + dx[i];
      ll nh = h + dy[i];
      unless(nw < W && nh < H) continue;

      ll id = to_id(h, w);
      ll nid = to_id(nh, nw);

      ll cost = mat[h][w] == WH && mat[nh][nw] == BL ? 1 : 0;
      edge_list[id].push_back({nid, cost});
    }
  }

  VL dist(node_ct, INF);
  priority_queue<PL, VPL, greater<PL>> q;
  q.emplace(0, to_id(0, 0));

  while (!q.empty()) {
    auto p = q.top();
    q.pop();

    ll cost = p.fi;
    ll u = p.se;

    if (cost > dist[u]) continue;

    for (auto e : edge_list[u]) {
      ll n_cost = cost + e.cost;
      if (chmin(dist[e.to], n_cost)) {
        q.emplace(n_cost, e.to);
      }
    }
  }

  ll res = dist[to_id(H - 1, W - 1)] + (mat[0][0] == BL ? 1 : 0);
  cout << res << endl;
}

// BFS
void solve3() {
  ll H, W;
  cin >> H >> W;

  char BL = '#';
  char WH = '.';

  V<string> mat(H);
  rep(i, H) cin >> mat[i];

  ll node_ct = H * W;

  struct Edge {
    ll to, cost;
  };

  V<V<Edge>> edge_list(node_ct, V<Edge>(0));

  auto to_id = [W](ll h, ll w) { return h * W + w; };

  VL dx = {0, 1};
  VL dy = {1, 0};

  rep(h, H) rep(w, W) {
    rep(i, dx.size()) {
      ll nw = w + dx[i];
      ll nh = h + dy[i];
      unless(nw < W && nh < H) continue;

      ll id = to_id(h, w);
      ll nid = to_id(nh, nw);

      ll cost = mat[h][w] == WH && mat[nh][nw] == BL ? 1 : 0;
      edge_list[id].push_back({nid, cost});
    }
  }

  VL dist(node_ct, INF);
  dist[to_id(0, 0)] = 0;
  queue<ll> q;
  q.emplace(to_id(0, 0));

  while (!q.empty()) {
    auto p_id = q.front();
    q.pop();

    for (auto e : edge_list[p_id]) {
      ll n_cost = dist[p_id] + e.cost;
      if (chmin(dist[e.to], n_cost)) {
        q.emplace(e.to);
      }
    }
  }

  ll res = dist[to_id(H - 1, W - 1)] + (mat[0][0] == BL ? 1 : 0);
  cout << res << endl;
}

struct exit_exception : public std::exception {
  const char* what() const throw() { return "Exited"; }
};

#ifndef TEST
int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  try {
    solve3();
  } catch (exit_exception& e) {
  }

  return 0;
}
#endif

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

void print_ints(vector<ll> v) {
  rep(i, v.size()) {
    if (i > 0) {
      cout << " ";
    }

    cout << v[i];
  }

  cout << endl;
}

template <typename T>
void drop(T res) {
  cout << res << endl;
  throw exit_exception();
}
