// https://atcoder.jp/contests/abc054/tasks/abc054_c

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
typedef long long ll;
typedef long double ld;
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
  ll N, M;
  cin >> N >> M;

  VVL edge_mat(N, VL(N));
  rep(i, M) {
    ll a, b;
    cin >> a >> b;
    a--, b--;
    edge_mat[a][b] = 1;
    edge_mat[b][a] = 1;
  }

  ll res = 0;
  VL nodes(N);
  rep(i, N) nodes[i] = i;

  do {
    unless(nodes.front() == 0) continue;

    ll ok = true;

    rep(i, N - 1) { unless(edge_mat[nodes[i]][nodes[i + 1]]) ok = false; }

    if (ok) res++;
  } while (next_permutation(all(nodes)));

  cout << res << endl;
}

ll dfs(ll u, V<bool>& visited, VVL& edge_list) {
  if (all_of(all(visited), [](ll v) { return v; })) return 1;

  ll res = 0;

  for (auto v : edge_list[u]) {
    if (visited[v]) continue;
    visited[v] = true;

    res += dfs(v, visited, edge_list);
    visited[v] = false;
  }

  return res;
}

void solve2() {
  ll N, M;
  cin >> N >> M;

  VVL edge_list(N, VL(N));
  rep(i, M) {
    ll a, b;
    cin >> a >> b;
    a--, b--;
    edge_list[a].emplace_back(b);
    edge_list[b].emplace_back(a);
  }

  V<bool> visited(N);
  visited[0] = true;

  ll res = dfs(0, visited, edge_list);

  cout << res << endl;
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
