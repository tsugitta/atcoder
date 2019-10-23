// https://atcoder.jp/contests/abc126/tasks/abc126_d

#include "algorithm"
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

// f: node, s: length
V<VPL> edges;
VL colors;

void rec(ll u, ll p, ll c) {
  colors[u] = c;

  for (auto edge : edges[u]) {
    ll v = edge.first;
    ll l = edge.second;
    if (v == p) continue;

    ll nc = l % 2 == 0 ? c : 1 - c;
    rec(v, u, nc);
  }
}

void solve() {
  ll N;
  cin >> N;

  edges = V<VPL>(N, VPL());

  rep(i, N - 1) {
    ll u, v, w;
    cin >> u >> v >> w;
    --u, --v;
    edges[u].emplace_back(v, w);
    edges[v].emplace_back(u, w);
  }

  // 一つの色を決め、再帰的に見て変が偶数であれば同じ色、奇数であれば違う色、としていくと、「任意の
  // 2 点間の距離が偶数 ⇒ 同じ色」「任意の 2 点間の距離が奇数 ⇒
  // 違う色」が実現され、後者の対偶より 「任意の 2 点が同じ色 ⇒
  // 距離が偶数」が実現されることとなる

  colors = VL(N, -1);

  rec(0, -1, 1);

  rep(i, N) { cout << colors[i] << endl; }
}

VL dists;
void rec_to_fill_dist(ll u, ll p, ll d) {
  dists[u] = d;

  for (auto edge : edges[u]) {
    ll v = edge.first;
    ll l = edge.second;

    if (v == p) continue;

    rec_to_fill_dist(v, u, d + l);
  }
}

void solve2() {
  ll N;
  cin >> N;

  edges = V<VPL>(N, VPL());

  rep(i, N - 1) {
    ll u, v, w;
    cin >> u >> v >> w;
    --u, --v;
    edges[u].emplace_back(v, w);
    edges[v].emplace_back(u, w);
  }

  // 適当に根を決め、根からの距離を d[i] とすると、 2 点間の距離は d[i] + d[j] -
  // 2*d[LCA] よってこの偶奇は d[i] と d[j] の偶奇で決定される
  // ここで、 d[i]
  // が偶数なら根と同じ色、奇数なら根と違う色を埋めるとすると、「任意の 2
  // 点について同じ色」 ⇔ 「2 点の d の偶奇が等しい」 ⇔ 「2 点の距離が偶数」
  // となる

  colors = VL(N);
  colors[0] = 1;

  dists = VL(N);
  rec_to_fill_dist(0, -1, 0);

  repf(u, 1, N) { colors[u] = dists[u] % 2 == 0 ? colors[0] : 1 - colors[0]; }

  rep(u, N) { cout << colors[u] << endl; }
}

struct exit_exception : public std::exception {
  const char* what() const throw() { return "Exited"; }
};

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
