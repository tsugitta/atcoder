// https://atcoder.jp/contests/abc213/tasks/abc213_e

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

// ダイクストラ
void solve() {
  ll H, W;
  cin >> H >> W;

  V<string> mat(H);
  rep(h, H) cin >> mat[h];

  VV<PL> edge_list(H * W);  // {to, cost}

  auto id_to_hw = [&](ll id) -> PL {
    ll h = id / W;
    ll w = id % W;
    return {h, w};
  };

  auto hw_to_id = [&](ll h, ll w) { return h * W + w; };

  auto is_included = [&](ll h, ll w) {
    return 0 <= h && h < H && 0 <= w && w < W;
  };

  rep(h, H) rep(w, W) {
    {
      VL dhs{-1, 0, 1, 0};
      VL dws{0, 1, 0, -1};

      rep(di, 4) {
        ll dh = dhs[di];
        ll dw = dws[di];

        ll nh = h + dh;
        ll nw = w + dw;

        unless(is_included(nh, nw)) continue;
        unless(mat[nh][nw] == '.') continue;

        edge_list[hw_to_id(h, w)].emplace_back(hw_to_id(nh, nw), 0);
      }
    }

    {
      for (ll dh : {-2, -1, 0, 1, 2}) {
        for (ll dw : {-2, -1, 0, 1, 2}) {
          unless(abs(dh) + abs(dw) <= 3) continue;

          ll nh = h + dh;
          ll nw = w + dw;

          unless(is_included(nh, nw)) continue;
          edge_list[hw_to_id(h, w)].emplace_back(hw_to_id(nh, nw), 1);
        }
      }
    }
  }

  VL dists(H * W, INF);
  dists[hw_to_id(0, 0)] = 0;

  asc_pq<tuple<ll, ll, ll>> q;  // {cost, h, w}

  q.emplace(0, 0, 0);

  while (!q.empty()) {
    auto [cur_cost, uh, uw] = q.top();
    q.pop();

    ll u_id = hw_to_id(uh, uw);

    if (cur_cost > dists[u_id]) continue;

    for (auto [v_id, edge_cost] : edge_list[u_id]) {
      ll n_cost = cur_cost + edge_cost;

      if (chmin(dists[v_id], n_cost)) {
        auto [vh, vw] = id_to_hw(v_id);

        q.emplace(n_cost, vh, vw);
      }
    }
  }

  ll res = dists[hw_to_id(H - 1, W - 1)];
  cout << res << "\n";
}

// 01BFS
void solve2() {
  ll H, W;
  cin >> H >> W;

  V<string> mat(H);
  rep(h, H) cin >> mat[h];

  VV<PL> edge_list(H * W);  // {to, cost}

  auto id_to_hw = [&](ll id) -> PL {
    ll h = id / W;
    ll w = id % W;
    return {h, w};
  };

  auto hw_to_id = [&](ll h, ll w) { return h * W + w; };

  auto is_included = [&](ll h, ll w) {
    return 0 <= h && h < H && 0 <= w && w < W;
  };

  rep(h, H) rep(w, W) {
    {
      VL dhs{-1, 0, 1, 0};
      VL dws{0, 1, 0, -1};

      rep(di, 4) {
        ll dh = dhs[di];
        ll dw = dws[di];

        ll nh = h + dh;
        ll nw = w + dw;

        unless(is_included(nh, nw)) continue;
        unless(mat[nh][nw] == '.') continue;

        edge_list[hw_to_id(h, w)].emplace_back(hw_to_id(nh, nw), 0);
      }
    }

    {
      for (ll dh : {-2, -1, 0, 1, 2}) {
        for (ll dw : {-2, -1, 0, 1, 2}) {
          unless(abs(dh) + abs(dw) <= 3) continue;

          ll nh = h + dh;
          ll nw = w + dw;

          unless(is_included(nh, nw)) continue;
          edge_list[hw_to_id(h, w)].emplace_back(hw_to_id(nh, nw), 1);
        }
      }
    }
  }

  VL dists(H * W, INF);
  dists[hw_to_id(0, 0)] = 0;

  deque<tuple<ll, ll, ll>> q;  // {cost, h, w}

  q.emplace_back(0, 0, 0);

  while (!q.empty()) {
    auto [cur_cost, uh, uw] = q.front();
    q.pop_front();

    ll u_id = hw_to_id(uh, uw);

    if (cur_cost > dists[u_id]) continue;

    for (auto [v_id, edge_cost] : edge_list[u_id]) {
      ll n_cost = cur_cost + edge_cost;

      if (chmin(dists[v_id], n_cost)) {
        auto [vh, vw] = id_to_hw(v_id);

        if (edge_cost == 0) {
          q.emplace_front(n_cost, vh, vw);
        } else {
          q.emplace_back(n_cost, vh, vw);
        }
      }
    }
  }

  ll res = dists[hw_to_id(H - 1, W - 1)];
  cout << res << "\n";
}
