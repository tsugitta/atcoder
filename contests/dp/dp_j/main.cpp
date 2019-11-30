// https://atcoder.jp/contests/dp/tasks/dp_j

#include "algorithm"
#include "cmath"
#include "functional"
#include "iomanip"
#include "iostream"
#include "numeric"
#include "queue"
#include "set"
#include "string"
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

ll N;
V<V<V<double>>> memo;

double dfs(ll one, ll two, ll thr) {
  if (!one && !two && !thr) return 0.0;
  if (memo[one][two][thr] >= 0) return memo[one][two][thr];

  ll s = one + two + thr;
  double res = 1.0 * N / s;  // 0 でないものが選ばれるまでにかかる期待値
  if (one) res += dfs(one - 1, two, thr) * one / s;
  if (two) res += dfs(one + 1, two - 1, thr) * two / s;
  if (thr) res += dfs(one, two + 1, thr - 1) * thr / s;

  memo[one][two][thr] = res;
  return res;
}

void solve() {
  cin >> N;

  VL cts(4);
  memo = V<V<V<double>>>(N + 1, V<V<double>>(N + 1, V<double>(N + 1, -1)));

  rep(i, N) {
    ll c;
    cin >> c;
    cts[c]++;
  }

  double res = dfs(cts[1], cts[2], cts[3]);
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
