// https://atcoder.jp/contests/abc180/tasks/abc180_e

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

  V<tuple<ll, ll, ll>> ps;

  rep(i, N) {
    ll x, y, z;
    cin >> x >> y >> z;

    ps.emplace_back(x, y, z);
  }

  VVL dp(N, VL(1 << (N - 1), INF));
  dp[0][0] = 0;

  asc_pq<tuple<ll, ll, ll>> q;  // cost, bit, last;

  q.emplace(0, 0, 0);

  while (!q.empty()) {
    auto [cost, bit, last_i] = q.top();
    q.pop();

    if (dp[last_i][bit] < cost) continue;

    auto [ax, ay, az] = ps[last_i];

    rep(n_i, N - 1) {
      if (bit & (1 << n_i)) continue;

      auto [bx, by, bz] = ps[n_i + 1];

      ll n_cost =
          dp[last_i][bit] + abs(bx - ax) + abs(by - ay) + max(0ll, bz - az);
      ll n_bit = bit | (1 << n_i);
      if (chmin(dp[n_i + 1][n_bit], n_cost)) {
        if (n_bit != ((1 << (N - 1) - 1))) {
          q.emplace(n_cost, n_bit, n_i + 1);
        }
      }
    }
  }

  ll res = INF;

  rep(i, N - 1) {
    ll d = dp[i + 1][(1 << (N - 1)) - 1];
    auto [ax, ay, az] = ps[i + 1];
    auto [bx, by, bz] = ps[0];
    ll r = d + abs(bx - ax) + abs(by - ay) + max(0ll, bz - az);
    chmin(res, r);
  }

  cout << res << "\n";
}

// priority queue を使わなくても bit 順に見れば OK
// その bit の部分 bit はその bit 未満 ⇒ 既に探索済み であることから
void solve2() {
  ll N;
  cin >> N;

  V<tuple<ll, ll, ll>> ps(N);

  rep(i, N) {
    ll x, y, z;
    cin >> x >> y >> z;

    ps[i] = {x, y, z};
  }

  auto dist = [&](ll a, ll b) {
    auto [ax, ay, az] = ps[a];
    auto [bx, by, bz] = ps[b];

    return abs(bx - ax) + abs(by - ay) + max(0ll, bz - az);
  };

  VVL dp(N, VL(1 << N, INF));
  dp[0][1] = 0;

  rep(bit, 1 << N) {
    rep(from, N) {
      unless(bit & (1 << from)) continue;
      rep(to, N) chmin(dp[to][bit | (1 << to)], dp[from][bit] + dist(from, to));
    }
  }

  ll res = dp[0][(1 << N) - 1];
  cout << res << "\n";
}
