// https://atcoder.jp/contests/arc090/tasks/arc090_b

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

void check(ll u, VL& positions, V<V<PL>>& edge_list, V<bool>& visited) {
  visited[u] = true;

  for (auto e : edge_list[u]) {
    ll v = e.fi;
    ll c = e.se;

    ll n_pos = positions[u] + c;
    if (positions[v] != INF && positions[v] != n_pos) drop("No");
    positions[v] = n_pos;

    if (!visited[v]) check(v, positions, edge_list, visited);
  }
}

void solve() {
  ll N, M;
  cin >> N >> M;

  V<V<PL>> edge_list(N, VPL(0));

  rep(i, M) {
    ll l, r, d;
    cin >> l >> r >> d;
    l--, r--;

    edge_list[l].emplace_back(r, d);
    edge_list[r].emplace_back(l, -d);
  }

  VL positions(N, INF);

  rep(i, N) {
    if (positions[i] != INF) continue;
    V<bool> visited(N);
    positions[i] = 0;
    check(i, positions, edge_list, visited);
  }

  cout << "Yes" << endl;
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
