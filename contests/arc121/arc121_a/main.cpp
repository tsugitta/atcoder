// https://atcoder.jp/contests/arc121/tasks/arc121_a

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
  ll N;
  cin >> N;

  struct Point {
    ll x, y, i;
  };

  V<Point> ps(N);

  rep(i, N) {
    ll x, y;
    cin >> x >> y;
    ps[i] = {x, y, i};
  }

  V<Point> x_mins;
  V<Point> x_maxs;
  V<Point> y_mins;
  V<Point> y_maxs;

  sort(all(ps), [&](Point lhs, Point rhs) { return lhs.x < rhs.x; });

  x_mins.push_back(ps[0]);
  x_mins.push_back(ps[1]);
  x_maxs.push_back(ps[N - 1]);
  x_maxs.push_back(ps[N - 2]);

  sort(all(ps), [&](Point lhs, Point rhs) { return lhs.y < rhs.y; });

  x_mins.push_back(ps[0]);
  x_mins.push_back(ps[1]);
  x_maxs.push_back(ps[N - 1]);
  x_maxs.push_back(ps[N - 2]);

  map<ll, Point> cand_map;

  for (auto ps_added : {x_mins, x_maxs, y_mins, y_maxs}) {
    for (auto p : ps_added) {
      cand_map[p.i] = p;
    }
  }

  V<Point> cands;

  for (auto [k, v] : cand_map) {
    cands.push_back(v);
  }

  ll cand_n = cands.size();

  asc_pq<ll> pq;

  rep(j, cand_n) rep(i, j) {
    auto pi = cands[i];
    auto pj = cands[j];

    pq.push(max(abs(pi.x - pj.x), abs(pi.y - pj.y)));

    while (pq.size() > 2) pq.pop();
  }

  ll res = pq.top();

  cout << res << "\n";
}
