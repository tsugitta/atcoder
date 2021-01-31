// https://atcoder.jp/contests/abc190/tasks/abc190_e

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

  ll K;
  cin >> K;

  VL cs(K);
  for (ll& c : cs) {
    cin >> c;
    --c;
  }

  auto get_dist = [&](ll start) {
    queue<ll> q;

    VL s_all_dist(N, INF);
    s_all_dist[start] = 0;

    q.emplace(start);

    while (!q.empty()) {
      ll u = q.front();
      q.pop();

      for (ll v : edge_list[u]) {
        if (chmin(s_all_dist[v], s_all_dist[u] + 1)) {
          q.emplace(v);
        }
      }
    }

    VL res(K, INF);
    rep(i, K) res[i] = s_all_dist[cs[i]];

    return res;
  };

  VVL dist(K, VL(K, INF));
  rep(i, K) dist[i] = get_dist(cs[i]);

  VVL dp(K, VL(1 << K, INF));
  rep(i, K) dp[i][1 << i] = 1;

  rep(bit, 1 << K) rep(last_i, K) {
    unless(bit & (1 << last_i)) continue;

    rep(next_i, K) {
      if (bit & (1 << next_i)) continue;
      chmin(dp[next_i][bit | (1 << next_i)],
            dp[last_i][bit] + dist[last_i][next_i]);
    }
  }

  ll res = INF;
  rep(i, K) chmin(res, dp[i][(1 << K) - 1]);

  if (res == INF) drop(-1);
  cout << res << "\n";
}
