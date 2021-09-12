// https://atcoder.jp/contests/abc218/tasks/abc218_d

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
#include "unordered_set"
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

void solve() {
  ll N;
  cin >> N;

  VPL ps(N);
  for (auto& [x, y] : ps) cin >> x >> y;

  set<PL> p_set;
  for (auto& [x, y] : ps) p_set.emplace(x, y);

  ll res = 0;

  // rep(j, N) rep(i, j) ではないことに注意。ソートしていないので i, j
  // のインデックスの順序に制約は設けられない
  rep(i, N) rep(j, N) {
    auto [ix, iy] = ps[i];
    auto [jx, jy] = ps[j];
    unless(ix < jx && iy < jy) continue;

    if (p_set.count({ix, jy}) && p_set.count({jx, iy})) res++;
  }

  cout << res << "\n";
}

void solve2() {
  ll N;
  cin >> N;

  VPL ps(N);
  for (auto& [x, y] : ps) cin >> x >> y;

  map<ll, VL> x_to_ys;
  for (auto& [x, y] : ps) x_to_ys[x].push_back(y);

  multiset<PL> y_pair;

  ll res = 0;

  for (auto [x, ys] : x_to_ys) {
    sort(all(ys));

    multiset<PL> new_y_pair;

    rep(j, ys.size()) rep(i, j) {
      ll iy = ys[i];
      ll jy = ys[j];

      res += y_pair.count({iy, jy});
      new_y_pair.insert({iy, jy});
    }

    for (auto p : new_y_pair) y_pair.insert(p);
  }

  cout << res << "\n";
}
