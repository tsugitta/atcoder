// https://atcoder.jp/contests/abc211/tasks/abc211_d

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

using mint = modint1000000007;

void solve() {
  ll N, M;
  cin >> N >> M;

  VVL edge_list(N);

  rep(i, M) {
    ll a, b;
    cin >> a >> b;
    --a, --b;

    edge_list[a].push_back(b);
    edge_list[b].push_back(a);
  }

  VL dists(N, INF);
  dists[0] = 0;

  V<mint> cts(N);
  cts[0] = 1;

  asc_pq<PL> q;
  q.emplace(0, 0);

  while (!q.empty()) {
    auto [dist, u] = q.top();
    q.pop();

    ll n_dist = dist + 1;

    for (ll v : edge_list[u]) {
      if (chmin(dists[v], n_dist)) {
        cts[v] = cts[u];
        q.emplace(n_dist, v);
      } else if (dists[v] == n_dist) {
        cts[v] += cts[u];
      }
    }
  }

  ll res = cts[N - 1].val();

  cout << res << "\n";
}
