// https://atcoder.jp/contests/agc049/tasks/agc049_a

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

  VV<bool> mat(N, V<bool>(N));
  VV<bool> inv_mat(N, V<bool>(N));

  rep(i, N) {
    string S;
    cin >> S;

    rep(j, N) {
      if (S[j] == '1') {
        mat[i][j] = 1;
        inv_mat[j][i] = 1;
      }
    }
  }

  ld res = 0;

  rep(i, N) {
    // その頂点に到達できる頂点の個数（自身を含む）
    V<bool> visited(N);
    visited[i] = 1;

    auto dfs = [&](auto self, ll u) -> void {
      rep(v, N) {
        if (inv_mat[u][v]) {
          if (visited[v]) continue;
          visited[v] = 1;
          self(self, v);
        }
      }
    };

    dfs(dfs, i);
    ld ct = count(all(visited), true);
    res += 1 / ct;
  }

  cout << fixed << setprecision(20) << res << endl;
}
