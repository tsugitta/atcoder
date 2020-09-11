// https://atcoder.jp/contests/practice2/tasks/practice2_e

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
  ll N, K;
  cin >> N >> K;

  ll BIG = 1e10;

  mcf_graph<ll, ll> g(2 * N + 2);

  ll S = 2 * N;
  ll T = 2 * N + 1;

  g.add_edge(S, T, N * K, BIG);

  rep(i, N) {
    g.add_edge(S, i, K, 0);
    g.add_edge(N + i, T, K, 0);
  }

  rep(h, N) rep(w, N) {
    ll a;
    cin >> a;
    g.add_edge(h, N + w, 1, BIG - a);
  }

  auto flow_res = g.flow(S, T, N * K);
  ll res = N * K * BIG - flow_res.se;
  cout << res << "\n";

  V<string> mat(N, string(N, '.'));

  auto edges = g.edges();

  for (auto e : edges) {
    if (e.from == S || e.to == T || e.flow == 0) continue;
    mat[e.from][e.to - N] = 'X';
  }

  rep(i, N) cout << mat[i] << "\n";
}
