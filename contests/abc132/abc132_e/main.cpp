// https://atcoder.jp/contests/abc132/tasks/abc132_e

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
using PL = pair<ll, ll>;
template <typename T>
inline bool chmax(T& a, T b);
template <typename T>
inline bool chmin(T& a, T b);
void print_ints(vector<ll> v);
template <typename T>
void drop(T a);

// BFS
void solve() {
  ll N, M;
  cin >> N >> M;

  VVL edges(N, VL());
  const ll STEP = 3;

  rep(i, M) {
    ll u, v;
    cin >> u >> v;
    u--, v--;
    edges[u].push_back(v);
  }

  ll S, T;
  cin >> S >> T;
  S--, T--;

  ll INF = 1e18;

  VVL dist(N, VL(STEP, INF));
  dist[S][0] = 0;

  queue<PL> q;
  q.push({S, 0});

  while (!q.empty()) {
    PL cur = q.front();
    q.pop();

    ll cp = cur.first;
    ll parity = cur.second;

    ll n_parity = (parity + 1) % STEP;

    for (auto np : edges[cp]) {
      if (dist[np][n_parity] != INF) continue;
      dist[np][n_parity] = dist[cp][parity] + 1;
      q.push({np, n_parity});
    }
  }

  ll res = dist[T][0] == INF ? -1 : dist[T][0] / STEP;
  cout << res << endl;
}

struct exit_exception : public std::exception {
  const char* what() const throw() { return "Exited"; }
};

// コストがあるとした場合のダイクストラ
void solve2() {
  ll N, M;
  cin >> N >> M;

  V<V<PL>> edges(N, V<PL>());
  const ll STEP = 3;

  rep(i, M) {
    ll u, v;
    cin >> u >> v;
    u--, v--;
    ll cost = 1;
    edges[u].push_back({v, cost});
  }

  ll S, T;
  cin >> S >> T;
  S--, T--;

  ll INF = 1e18;

  VVL dist(N, VL(STEP, INF));
  dist[S][0] = 0;

  priority_queue<pair<ll, PL>, V<pair<ll, PL>>, greater<pair<ll, PL>>> q;
  q.push({0, make_pair(S, 0)});

  while (!q.empty()) {
    auto p = q.top();
    q.pop();

    PL v = p.second;
    ll cp = v.first;
    ll parity = v.second;

    ll c_cost = p.first;
    if (c_cost > dist[cp][parity]) continue;

    ll n_parity = (parity + 1) % STEP;

    for (auto n : edges[cp]) {
      ll np = n.first;
      ll cost = n.second;

      ll n_cost = c_cost + cost;
      if (chmin(dist[np][n_parity], n_cost)) {
        q.push({n_cost, PL(np, n_parity)});
      }
    }
  }

  ll res = dist[T][0] == INF ? -1 : dist[T][0] / STEP;
  cout << res << endl;
}

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
