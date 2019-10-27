// https://atcoder.jp/contests/abc144/tasks/abc144_f

#include "algorithm"
#include "iomanip"
#include "iostream"
#include "queue"
#include "set"
#include "vector"
#define rep(i, to) for (ll i = 0; i < (to); ++i)
#define repf(i, from, to) for (ll i = from; i < (to); ++i)
using namespace std;
typedef long long ll;
template <typename T>
using V = vector<T>;
using VL = V<ll>;
using VVL = V<VL>;
template <typename T, typename U>
using P = pair<T, U>;
using PL = P<ll, ll>;
using VPL = V<PL>;
template <typename T>
inline bool chmax(T& a, T b);
template <typename T>
inline bool chmin(T& a, T b);
void print_ints(vector<ll> v);
template <typename T>
void drop(T a);

void solve() {
  ll N, M;
  cin >> N >> M;

  VVL edges(N);
  rep(i, M) {
    ll s, t;
    cin >> s >> t;
    s--, t--;
    edges[s].push_back(t);
  }

  // その頂点から点 N までの辺の数の期待値
  auto calc_dp = [&](ll rm_from, ll rm_to) {
    V<double> dp(N);
    for (ll u = N - 2; u >= 0; u--) {
      double e = 0;

      for (auto v : edges[u]) {
        if (u == rm_from && v == rm_to) continue;
        e += dp[v];
      }

      ll deg = edges[u].size();
      if (u == rm_from) deg--;

      e /= deg;
      e++;
      dp[u] = e;
    }

    return dp;
  };

  V<double> dp = calc_dp(-1, -1);
  double res = dp[0];

  // 各頂点について、期待値の大きい点への辺を消す
  rep(rm_from, N - 1) {
    if (edges[rm_from].size() == 1) continue;

    ll rm_to;
    {
      double max_e = -1;
      for (auto rv : edges[rm_from]) {
        if (chmax(max_e, dp[rv])) rm_to = rv;
      }
    }

    auto rdp = calc_dp(rm_from, rm_to);
    chmin(res, rdp[0]);
  }

  cout << fixed << setprecision(10) << res << endl;
}

struct exit_exception : public std::exception {
  const char* what() const throw() { return "Exited"; }
};

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

void print_ints(vector<ll> v) {
  rep(i, v.size()) {
    if (i > 0) {
      cout << " ";
    }

    cout << v[i];
  }

  cout << endl;
}

template <typename T>
void drop(T res) {
  cout << res << endl;
  throw exit_exception();
}
