// https://atcoder.jp/contests/abc143/tasks/abc143_e

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

// ワーシャルフロイド２回 O(N^3)
void solve() {
  ll N, M, L;
  cin >> N >> M >> L;

  ll INF = 1 << 30;

  auto ds = VVL(N, VL(N, INF));

  rep(i, M) {
    ll a, b, c;
    cin >> a >> b >> c;
    a--;
    b--;

    if (c > L) continue;

    ds[a][b] = c;
    ds[b][a] = c;
  }

  // ワーシャルフロイド
  rep(k, N) rep(i, N) rep(j, N) {
    ds[i][j] = min(ds[i][j], ds[i][k] + ds[k][j]);
  }

  auto cts = VVL(N, VL(N, INF));

  rep(i, N) rep(j, N) {
    if (i == j) continue;

    if (ds[i][j] <= L) {
      cts[i][j] = 1;
    }
  }

  rep(k, N) rep(i, N) rep(j, N) {
    cts[i][j] = min(cts[i][j], cts[i][k] + cts[k][j]);
  }

  ll Q;
  cin >> Q;
  rep(i, Q) {
    ll s, t;
    cin >> s >> t;
    s--;
    t--;

    ll res = cts[s][t] == INF ? -1 : cts[s][t] - 1;
    cout << res << endl;
  }
}

// priority_queue ダイクストラ N 回 O (N * (E+V) log N) = O(N^3 log N)?
void solve2() {
  ll N, M, L;
  cin >> N >> M >> L;

  ll INF = 1 << 30;

  auto G = VVL(N, VL(N, INF));
  rep(i, N) G[i][i] = 0;

  rep(i, M) {
    ll a, b, c;
    cin >> a >> b >> c;
    a--, b--;

    if (c > L) continue;

    G[a][b] = G[b][a] = c;
  }

  // first: times, second: used としてこれの最小値をダイクストラで得る
  V<V<PL>> dist(N, V<PL>(N, {INF, INF}));
  rep(i, N) dist[i][i] = {0, 0};

  rep(s, N) {
    // デフォルトでは大きい値から取り出されることに注意
    // priority_queue<pair<PL, ll>> q;
    priority_queue<pair<PL, ll>, V<pair<PL, ll>>, greater<pair<PL, ll>>> q;

    q.push({PL(0, 0), s});

    while (!q.empty()) {
      auto p = q.top();
      q.pop();

      ll v = p.second;
      ll times = p.first.first;
      ll used = p.first.second;

      if (p.first > dist[s][v]) continue;

      rep(nv, N) {
        if (nv == v) continue;
        if (G[v][nv] > L) continue;
        ll n_used = used + G[v][nv];

        auto np = n_used > L ? PL(times + 1, G[v][nv]) : PL(times, n_used);

        if (chmin(dist[s][nv], np)) {
          q.push({np, nv});
        }
      }
    }
  }

  ll Q;
  cin >> Q;

  rep(i, Q) {
    ll s, t;
    cin >> s >> t;
    s--, t--;

    ll res = dist[s][t].first == INF ? -1 : dist[s][t].first;
    cout << res << endl;
  }
}

// original ダイクストラ N 回 O (N * N^2) = O(N^3)
void solve3() {
  ll N, M, L;
  cin >> N >> M >> L;

  ll INF = 1 << 30;

  auto G = VVL(N, VL(N, INF));
  rep(i, N) G[i][i] = 0;

  rep(i, M) {
    ll a, b, c;
    cin >> a >> b >> c;
    a--, b--;

    if (c > L) continue;

    G[a][b] = G[b][a] = c;
  }

  // first: times, second: used としてこれの最小値をダイクストラで得る
  V<V<PL>> dist(N, V<PL>(N, {INF, INF}));
  rep(i, N) dist[i][i] = {0, 0};

  rep(s, N) {
    // １ステップで、全頂点を確認し、それが配られていて、かつその点は配っていない点で最小のものを得る。そしてその点から配る。
    // これを頂点の数だけ繰り返せば、全頂点への最小パスが得られる。

    V<bool> fixed(N);
    V<PL> mins(N, {INF, INF});

    mins[s] = {0, 0};

    rep(_, N) {
      // second: 頂点
      pair<PL, ll> min = {{INF, INF}, -1};

      rep(u, N) {
        if (fixed[u]) continue;
        if (mins[u] == PL(INF, INF)) continue;

        chmin(min, make_pair(mins[u], u));
      }

      ll u = min.second;

      if (u == -1) {
        break;
      }

      rep(v, N) {
        if (u == v) continue;
        if (fixed[v]) continue;

        ll cost = G[u][v];
        if (cost > L) continue;

        ll times = min.first.first;
        ll used = min.first.second;

        ll n_times = times;
        ll n_used = cost + used;

        if (n_used > L) {
          n_times++;
          n_used = cost;
        }

        chmin(mins[v], {n_times, n_used});
      }

      fixed[u] = true;
      dist[s][u] = min.first;
    }
  }

  ll Q;
  cin >> Q;

  rep(i, Q) {
    ll s, t;
    cin >> s >> t;
    s--, t--;

    ll res = dist[s][t].first == INF ? -1 : dist[s][t].first;
    cout << res << endl;
  }
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
