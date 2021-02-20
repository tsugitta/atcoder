// https://atcoder.jp/contests/abc192/tasks/abc192_e

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
  ll N, M, X, Y;
  cin >> N >> M >> X >> Y;

  --X, --Y;

  struct Edge {
    ll to, time, k;
  };

  VV<Edge> edge_list(N);

  rep(i, M) {
    ll a, b, t, k;
    cin >> a >> b >> t >> k;
    --a, --b;
    edge_list[a].push_back({b, t, k});
    edge_list[b].push_back({a, t, k});
  }

  asc_pq<PL> q;

  VL dists(N, INF);
  dists[X] = 0;

  q.emplace(0, X);

  while (!q.empty()) {
    auto [time, cur] = q.top();
    q.pop();

    if (dists[cur] < time) continue;

    for (auto e : edge_list[cur]) {
      ll K = e.k;
      ll n_time = (time + K - 1) / K * K + e.time;

      if (chmin(dists[e.to], n_time)) {
        q.emplace(n_time, e.to);
      }
    }
  }

  if (dists[Y] == INF) drop(-1);
  cout << dists[Y] << "\n";
}
