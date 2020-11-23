// https://atcoder.jp/contests/abc184/tasks/abc184_e

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

int dhs[] = {-1, 0, 1, 0};
int dws[] = {0, 1, 0, -1};

void solve() {
  ll H, W;
  cin >> H >> W;

  ll sh, sw, gh, gw;

  V<string> mat(H);
  rep(h, H) cin >> mat[h];

  VV<PL> teleports(26);

  rep(h, H) rep(w, W) {
    if (mat[h][w] == 'S') {
      sh = h;
      sw = w;
    } else if (mat[h][w] == 'G') {
      gh = h;
      gw = w;
    } else if ('a' <= mat[h][w] && mat[h][w] <= 'z') {
      teleports[mat[h][w] - 'a'].emplace_back(h, w);
    }
  }

  VVL costs(H, VL(W, INF));
  costs[sh][sw] = 0;
  // テレポートの使用有無は queue の中に持つのでなく全体で管理して良い。
  // 初めてテレポートが使えるタイミングが、そのテレポートが使える最小のコストのタイミングであるため
  V<bool> teleport_used(26);
  deque<tuple<ll, PL>> q;  // cost, 座標

  q.emplace_back(0, make_pair(sh, sw));

  while (!q.empty()) {
    auto [cur_cost, pos] = q.front();
    q.pop_front();
    auto [h, w] = pos;

    if ('a' <= mat[h][w] && mat[h][w] <= 'z' &&
        !teleport_used[mat[h][w] - 'a']) {
      teleport_used[mat[h][w] - 'a'] = true;

      for (auto [nh, nw] : teleports[mat[h][w] - 'a']) {
        if (nh == h && nw == w) continue;

        if (chmin(costs[nh][nw], cur_cost + 1)) {
          q.emplace_back(cur_cost + 1, make_pair(nh, nw));
        }
      }
    }

    rep(i, 4) {
      ll nh = h + dhs[i];
      ll nw = w + dws[i];

      unless(0 <= nh && nh < H && 0 <= nw && nw < W) continue;
      if (mat[nh][nw] == '#') continue;

      if (chmin(costs[nh][nw], cur_cost + 1)) {
        q.emplace_back(cur_cost + 1, make_pair(nh, nw));
      }
    }
  }

  ll res = costs[gh][gw];

  if (res == INF) drop(-1);
  cout << res << "\n";
}
