// https://atcoder.jp/contests/abc176/tasks/abc176_d

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

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

// ダイクストラ
void solve() {
  ll H, W;
  cin >> H >> W;

  ll ch, cw;
  cin >> ch >> cw;
  ch--, cw--;

  ll dh, dw;
  cin >> dh >> dw;
  dh--, dw--;

  V<string> mat(H);
  rep(h, H) cin >> mat[h];

  VVL costs(H, VL(W, INF));
  costs[ch][cw] = 0;

  asc_pq<P<ll, PL>> pq;
  pq.emplace(0, make_pair(ch, cw));

  auto is_inside = [&](ll h, ll w) {
    return 0 <= h && h < H && 0 <= w && w < W;
  };

  auto is_street = [&](ll h, ll w) { return mat[h][w] == '.'; };

  while (!pq.empty()) {
    auto [cost, loc] = pq.top();
    pq.pop();
    auto [h, w] = loc;

    for (int i = 0; i < 4; ++i) {
      ll nh = h + dy[i];
      ll nw = w + dx[i];

      if (is_inside(nh, nw) && is_street(nh, nw) &&
          chmin(costs[nh][nw], cost)) {
        pq.emplace(cost, make_pair(nh, nw));
      }
    }

    for (ll dx = -2; dx <= 2; ++dx) {
      for (ll dy = -2; dy <= 2; ++dy) {
        ll nh = h + dy;
        ll nw = w + dx;

        if (is_inside(nh, nw) && is_street(nh, nw) &&
            chmin(costs[nh][nw], cost + 1)) {
          pq.emplace(cost + 1, make_pair(nh, nw));
        }
      }
    }
  }

  ll res = costs[dh][dw];
  if (res == INF) drop(-1);
  cout << res << "\n";
}

// 01-BFS
void solve2() {
  ll H, W;
  cin >> H >> W;

  ll ch, cw;
  cin >> ch >> cw;
  ch--, cw--;

  ll dh, dw;
  cin >> dh >> dw;
  dh--, dw--;

  V<string> mat(H);
  rep(h, H) cin >> mat[h];

  VVL costs(H, VL(W, INF));
  costs[ch][cw] = 0;

  deque<P<ll, PL>> q;
  q.emplace_back(0, make_pair(ch, cw));

  auto is_inside = [&](ll h, ll w) {
    return 0 <= h && h < H && 0 <= w && w < W;
  };

  auto is_street = [&](ll h, ll w) { return mat[h][w] == '.'; };

  while (!q.empty()) {
    auto [cost, loc] = q.front();
    q.pop_front();
    auto [h, w] = loc;

    for (int i = 0; i < 4; ++i) {
      ll nh = h + dy[i];
      ll nw = w + dx[i];

      if (is_inside(nh, nw) && is_street(nh, nw) &&
          chmin(costs[nh][nw], cost)) {
        q.emplace_front(cost, make_pair(nh, nw));
      }
    }

    for (ll dx = -2; dx <= 2; ++dx) {
      for (ll dy = -2; dy <= 2; ++dy) {
        ll nh = h + dy;
        ll nw = w + dx;

        if (is_inside(nh, nw) && is_street(nh, nw) &&
            chmin(costs[nh][nw], cost + 1)) {
          q.emplace_back(cost + 1, make_pair(nh, nw));
        }
      }
    }
  }

  ll res = costs[dh][dw];
  if (res == INF) drop(-1);
  cout << res << "\n";
}
