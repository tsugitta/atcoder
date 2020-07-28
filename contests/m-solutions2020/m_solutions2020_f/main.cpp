// https://atcoder.jp/contests/m-solutions2020/tasks/m_solutions2020_f

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

  const ll MAX_POSITION = 2e5;

  struct Point {
    ll x, y;
    char d;
  };

  V<Point> ps(N);
  rep(i, N) cin >> ps[i].x >> ps[i].y >> ps[i].d;

  map<char, char> rotate_map{
      {'U', 'R'},
      {'R', 'D'},
      {'D', 'L'},
      {'L', 'U'},
  };

  auto rotate = [&]() {
    rep(i, N) {
      auto p = ps[i];

      ps[i].x = p.y;
      ps[i].y = MAX_POSITION - p.x;
      ps[i].d = rotate_map[p.d];
    }
  };

  // 反対方向の衝突
  auto solve1 = [&]() {
    map<ll, V<P<ll, char>>> ps_for_y;

    rep(i, N) {
      unless(ps[i].d == 'L' || ps[i].d == 'R') continue;
      ps_for_y[ps[i].y].emplace_back(ps[i].x, ps[i].d);
    }

    ll res = INF;

    for (auto [_, ps] : ps_for_y) {
      sort(all(ps));

      rep(i, ps.size() - 1) {
        unless(ps[i].se == 'R' && ps[i + 1].se == 'L') continue;
        chmin(res, (ps[i + 1].fi - ps[i].fi) * 5);
      }
    }

    return res;
  };

  // 右・上方向の衝突
  auto solve2 = [&]() {
    map<ll, V<P<ll, char>>> ps_for_xy_sum;

    rep(i, N) {
      unless(ps[i].d == 'U' || ps[i].d == 'R') continue;
      ll sum = ps[i].x + ps[i].y;
      ps_for_xy_sum[sum].emplace_back(ps[i].x, ps[i].d);
    }

    ll res = INF;

    for (auto [_, ps] : ps_for_xy_sum) {
      sort(all(ps));

      rep(i, ps.size() - 1) {
        unless(ps[i].se == 'R' && ps[i + 1].se == 'U') continue;
        chmin(res, (ps[i + 1].fi - ps[i].fi) * 10);
      }
    }

    return res;
  };

  ll res = INF;

  rep(i, 4) {
    if (i < 2) chmin(res, solve1());
    chmin(res, solve2());
    rotate();
  }

  if (res == INF) drop("SAFE");

  cout << res << "\n";
}
