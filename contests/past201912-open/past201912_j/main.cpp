// https://atcoder.jp/contests/past201912-open/tasks/past201912_j

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

VL dx = {1, 0, -1, 0};
VL dy = {0, 1, 0, -1};

void solve() {
  ll H, W;
  cin >> H >> W;

  VVL mat(H, VL(W));

  rep(h, H) rep(w, W) cin >> mat[h][w];

  auto to_id = [W](ll h, ll w) -> ll { return h * W + w; };

  ll N = H * W;

  V<V<PL>> edges(N);

  rep(h, H) rep(w, W) {
    rep(di, 4) {
      ll nh = h + dy[di];
      ll nw = w + dx[di];

      unless(0 <= nh && nh < H && 0 <= nw && nw < W) continue;

      edges[to_id(h, w)].emplace_back(to_id(nh, nw), mat[nh][nw]);
    }
  }

  // ダイクストラ
  auto get_dist = [&](ll from_h, ll from_w) -> VL {
    VL dist(N, INF);
    dist[to_id(from_h, from_w)] = 0;

    priority_queue<PL, VPL, greater<PL>> q;
    q.push({0, to_id(from_h, from_w)});

    while (!q.empty()) {
      auto p = q.top();
      q.pop();

      ll cost = p.first;
      ll u = p.second;

      if (cost > dist[u]) continue;

      for (auto vp : edges[u]) {
        ll v = vp.first;
        ll edge_cost = vp.second;

        ll n_cost = cost + edge_cost;
        if (chmin(dist[v], n_cost)) {
          q.emplace(n_cost, v);
        }
      }
    }

    return dist;
  };

  auto left_bottom_dist = get_dist(H - 1, 0);
  auto right_bottom_dist = get_dist(H - 1, W - 1);
  auto right_top_dist = get_dist(0, W - 1);

  ll res = INF;

  rep(h, H) rep(w, W) {
    ll id = to_id(h, w);
    ll _res = left_bottom_dist[id] + right_bottom_dist[id] +
              right_top_dist[id] - mat[h][w] * 2;

    chmin(res, _res);
  }

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
    solve();
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
