// https://atcoder.jp/contests/abc187/tasks/abc187_f

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

  VV<bool> edge_mat(N, V<bool>(N));

  rep(i, M) {
    ll a, b;
    cin >> a >> b;
    --a, --b;
    edge_mat[a][b] = true;
    edge_mat[b][a] = true;
  }

  // その頂点群が完全グラフか
  V<bool> completed(1ll << N);

  rep(bit, 1ll << N) {
    VL vs;
    rep(i, N) if (bit & (1ll << i)) vs.push_back(i);

    auto check = [&]() {
      rep(j, vs.size()) rep(i, j) {
        ll u = vs[i];
        ll v = vs[j];

        unless(edge_mat[u][v]) {
          completed[bit] = false;
          return;
        }
      }

      completed[bit] = true;
    };

    check();
  }

  // 誘導グラフに対する答え
  VL dp(1ll << N, INF);
  dp[0] = 0;

  // 小さい誘導グラフから答えを求めていく。その誘導グラフに含まれない全頂点に対して、完全グラフであれば値を配る、というのを繰り返す
  rep(bit, 1ll << N) {
    if (dp[bit] == INF) continue;

    ll c_bit = (1ll << N) - 1 - bit;

    // bit 部分集合の部分集合を列挙する
    // https://qiita.com/drken/items/7c6ff2aa4d8fce1c9361#7-%E4%B8%8E%E3%81%88%E3%82%89%E3%82%8C%E3%81%9F%E9%83%A8%E5%88%86%E9%9B%86%E5%90%88%E3%81%AE%E9%83%A8%E5%88%86%E9%9B%86%E5%90%88%E3%82%92%E5%88%97%E6%8C%99
    for (ll add_bit = c_bit; add_bit > 0; add_bit = (add_bit - 1) & c_bit) {
      unless(completed[add_bit]) continue;
      chmin(dp[bit | add_bit], dp[bit] + 1);
    }
  }

  ll res = dp[(1ll << N) - 1];
  cout << res << "\n";
}
