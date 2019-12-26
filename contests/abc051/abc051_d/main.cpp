// https://atcoder.jp/contests/abc051/tasks/abc051_d

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

  struct Edge {
    ll from, to, cost;
  };

  V<Edge> edges(M);

  VVL ds(N, VL(N, INF));
  rep(i, N) ds[i][i] = 0;

  rep(i, M) {
    ll a, b, c;
    cin >> a >> b >> c;
    a--, b--;

    edges[i] = {a, b, c};

    chmin(ds[a][b], c);
    chmin(ds[b][a], c);
  }

  // ワーシャルフロイド
  rep(k, N) rep(i, N) rep(j, N) {
    ds[i][j] = min(ds[i][j], ds[i][k] + ds[k][j]);
  }

  ll necessary_path_ct = 0;

  rep(i, M) {
    bool necessary = false;

    rep(s, N) rep(t, N) {
      Edge e = edges[i];
      if (ds[s][e.from] + e.cost + ds[e.to][t] == ds[s][t]) {
        necessary = true;
      }
    }

    if (necessary) necessary_path_ct++;
  }

  ll res = M - necessary_path_ct;
  cout << res << endl;
}

void solve2() {
  ll N, M;
  cin >> N >> M;

  struct Edge {
    ll from, to, cost;
  };

  V<Edge> edges(M);

  VVL ds(N, VL(N, INF));
  rep(i, N) ds[i][i] = 0;

  rep(i, M) {
    ll a, b, c;
    cin >> a >> b >> c;
    a--, b--;

    edges[i] = {a, b, c};

    chmin(ds[a][b], c);
    chmin(ds[b][a], c);
  }

  rep(k, N) rep(i, N) rep(j, N) {
    ds[i][j] = min(ds[i][j], ds[i][k] + ds[k][j]);
  }

  ll necessary_path_ct = 0;

  rep(i, M) {
    bool necessary = false;

    rep(s, N) {
      Edge e = edges[i];
      if (ds[s][e.from] + e.cost == ds[s][e.to]) {
        necessary = true;
      }
    }

    if (necessary) necessary_path_ct++;
  }

  ll res = M - necessary_path_ct;
  cout << res << endl;
}

void solve3() {
  ll N, M;
  cin >> N >> M;

  struct Edge {
    ll from, to, cost;
  };

  V<Edge> edges(M);

  VVL ds(N, VL(N, INF));
  rep(i, N) ds[i][i] = 0;

  rep(i, M) {
    ll a, b, c;
    cin >> a >> b >> c;
    a--, b--;

    edges[i] = {a, b, c};

    chmin(ds[a][b], c);
    chmin(ds[b][a], c);
  }

  rep(k, N) rep(i, N) rep(j, N) {
    ds[i][j] = min(ds[i][j], ds[i][k] + ds[k][j]);
  }

  ll res = 0;

  rep(i, M) {
    Edge e = edges[i];
    if (e.cost > ds[e.from][e.to]) res++;
  }

  cout << res << endl;
}

void solve4() {
  ll N, M;
  cin >> N >> M;

  struct Edge {
    ll from, to, cost;
  };

  V<Edge> edges(M);
  V<V<Edge>> edge_list(N, V<Edge>(0));

  VVL ds(N, VL(N, INF));
  rep(i, N) ds[i][i] = 0;

  rep(i, M) {
    ll a, b, c;
    cin >> a >> b >> c;
    a--, b--;

    edges[i] = {a, b, c};
    edge_list[a].push_back({a, b, c});
    edge_list[b].push_back({b, a, c});
  }

  // ダイクストラ
  rep(i, N) {
    priority_queue<PL, V<PL>, greater<PL>> pq;

    pq.emplace(0, i);

    while (!pq.empty()) {
      auto p = pq.top();
      pq.pop();

      ll cost = p.fi;
      ll from = p.se;

      if (cost > ds[i][from]) continue;

      for (auto e : edge_list[from]) {
        ll n_cost = cost + e.cost;

        if (chmin(ds[i][e.to], n_cost)) {
          pq.emplace(n_cost, e.to);
        }
      }
    }
  }

  ll necessary_path_ct = 0;

  rep(i, M) {
    bool necessary = false;

    rep(s, N) {
      Edge e = edges[i];
      if (ds[s][e.from] + e.cost == ds[s][e.to]) {
        necessary = true;
      }
    }

    if (necessary) necessary_path_ct++;
  }

  ll res = M - necessary_path_ct;
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
    solve3();
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
