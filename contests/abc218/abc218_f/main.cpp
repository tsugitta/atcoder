// https://atcoder.jp/contests/abc218/tasks/abc218_f

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
  ll N, M;
  cin >> N >> M;

  VPL edges(M);
  VVL edge_list(N);

  rep(i, M) {
    ll s, t;
    cin >> s >> t;
    --s, --t;
    edge_list[s].push_back(t);
    edges[i] = {s, t};
  }

  VL dists(N, INF);
  dists[0] = 0;

  VL prevs(N, -1);

  {
    asc_pq<PL> q;

    q.emplace(0, 0);

    while (q.size()) {
      auto [c, u] = q.top();
      q.pop();

      if (dists[u] < c) continue;

      for (ll v : edge_list[u]) {
        if (chmin(dists[v], c + 1)) {
          q.emplace(c + 1, v);
          prevs[v] = u;
        }
      }
    }
  }

  if (dists[N - 1] == INF) {
    rep(i, M) cout << -1 << "\n";
    return;
  }

  set<PL> shorted_path_edges;

  {
    ll cur = N - 1;

    while (cur != 0) {
      ll prev = prevs[cur];
      shorted_path_edges.emplace(prev, cur);
      swap(prev, cur);
    }
  }

  rep(i, M) {
    PL edge = edges[i];

    if (!shorted_path_edges.count(edge)) {
      cout << dists[N - 1] << "\n";
      continue;
    }

    VL dists2(N, INF);
    dists2[0] = 0;

    {
      asc_pq<PL> q;

      q.emplace(0, 0);

      while (q.size()) {
        auto [c, u] = q.top();
        q.pop();

        if (dists2[u] < c) continue;

        for (ll v : edge_list[u]) {
          if (edge.fi == u && edge.se == v) continue;

          if (chmin(dists2[v], c + 1)) {
            q.emplace(c + 1, v);
          }
        }
      }
    }

    cout << (dists2[N - 1] == INF ? -1 : dists2[N - 1]) << "\n";
  }
}
