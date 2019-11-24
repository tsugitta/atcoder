// https://atcoder.jp/contests/abc146/tasks/abc146_d

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

void dfs(ll u, ll p, ll color_p, V<VPL>& edge_list, VL& colors, ll& color_ct) {
  ll next_color = 1;

  for (auto e : edge_list[u]) {
    ll v = e.fi;
    if (v == p) {
      continue;
    }

    if (next_color == color_p) next_color++;
    colors[e.se] = next_color;
    chmax(color_ct, next_color);

    dfs(v, u, next_color, edge_list, colors, color_ct);
    next_color++;
  }
}

void solve() {
  ll N;
  cin >> N;

  V<VPL> edge_list(N, VPL(0));

  VL colors(N - 1);

  rep(i, N - 1) {
    ll a, b;
    cin >> a >> b;
    a--, b--;

    edge_list[a].emplace_back(b, i);
    edge_list[b].emplace_back(a, i);
  }

  ll color_ct = 0;
  dfs(0, -1, -1, edge_list, colors, color_ct);

  cout << color_ct << endl;
  rep(i, N - 1) { cout << colors[i] << endl; }
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
