// https://atcoder.jp/contests/past202004-open/tasks/past202004_h

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

  VVL mat(N, VL(M));

  VV<PL> num_to_positions(11);

  {
    V<string> mat_s(N);
    rep(i, N) cin >> mat_s[i];

    rep(h, N) rep(w, M) {
      mat[h][w] =
          mat_s[h][w] == 'S' ? 0 : mat_s[h][w] == 'G' ? 10 : mat_s[h][w] - '0';

      num_to_positions[mat[h][w]].emplace_back(h, w);
    }
  }

  VVL dp(N, VL(M, INF));

  auto [sh, sw] = num_to_positions[0][0];
  auto [gh, gw] = num_to_positions[10][0];

  dp[sh][sw] = 0;

  rep(num, 10) {
    for (auto [h, w] : num_to_positions[num]) {
      for (auto [nh, nw] : num_to_positions[num + 1]) {
        chmin(dp[nh][nw], dp[h][w] + abs(nh - h) + abs(nw - w));
      }
    }
  }

  ll res = dp[gh][gw];
  if (res == INF) drop(-1);

  cout << res << "\n";
}
