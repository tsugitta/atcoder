// https://atcoder.jp/contests/ddcc2020-qual/tasks/ddcc2020_qual_c

#include "algorithm"
#include "cmath"
#include "functional"
#include "iostream"
#include "numeric"
#include "queue"
#include "set"
#include "vector"
#define rep(i, to) for (ll i = 0; i < (to); ++i)
#define repf(i, from, to) for (ll i = from; i < (to); ++i)
#define repr(i, from) for (ll i = from - 1; i >= 0; --i)
#define all(vec) vec.begin(), vec.end()
#define fi first
#define se second
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

const ll INF = 1e18;

void solve() {
  ll H, W, K;
  cin >> H >> W >> K;

  V<string> mat(H);
  rep(i, H) cin >> mat[i];

  VVL res(H, VL(W));

  {
    ll next_k = 1;

    rep(i, H) rep(j, W) {
      if (mat[i][j] == '#') {
        res[i][j] = next_k;
        next_k++;
      }
    }
  }

  rep(i, H) {
    rep(j, W) {
      if (j == 0) continue;
      if (res[i][j] == 0) res[i][j] = res[i][j - 1];
    }

    repr(j, W) {
      if (j == W - 1) continue;
      if (res[i][j] == 0) res[i][j] = res[i][j + 1];
    }
  }

  rep(i, H) {
    if (i == 0) continue;
    if (res[i][0] == 0) rep(j, W) res[i][j] = res[i - 1][j];
  }

  repr(i, H) {
    if (i == H - 1) continue;
    if (res[i][0] == 0) rep(j, W) res[i][j] = res[i + 1][j];
  }

  rep(i, H) print_ints(res[i]);
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
