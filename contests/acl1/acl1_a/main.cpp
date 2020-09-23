// https://atcoder.jp/contests/acl1/tasks/acl1_a

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

void solve() {
  ll N;
  cin >> N;

  using PT = tuple<ll, ll, ll>;

  V<PT> points(N);

  VL y_to_i(N);

  rep(i, N) {
    ll x, y;
    cin >> x >> y;
    --x, --y;
    y_to_i[y] = i;
    points[i] = {x, y, i};
  }

  sort(all(points), [](PT a, PT b) {
    auto [ax, ay, ai] = a;
    auto [bx, by, bi] = b;
    return ax < bx;
  });

  dsu d(N);

  set<ll> ys;

  rep(i, N) {
    auto [x, y, pi] = points[i];

    ll merged_min_y = INF;

    for (auto it = ys.begin(); it != ys.end();) {
      auto s_y = *it;
      unless(s_y < y) break;
      d.merge(y_to_i[s_y], pi);
      chmin(merged_min_y, s_y);
      ys.erase(it++);
    }

    if (merged_min_y == INF) {
      ys.insert(y);
    } else {
      ys.insert(merged_min_y);
    }
  }

  rep(i, N) cout << d.size(i) << "\n";
}
