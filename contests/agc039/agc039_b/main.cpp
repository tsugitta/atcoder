// https://atcoder.jp/contests/agc039/tasks/agc039_b

#include "algorithm"
#include "iostream"
#include "queue"
#include "set"
#include "vector"
#define rep(i, from, to) for (ll i = from; i < (to); ++i)
using namespace std;
typedef long long ll;
template <typename T>
using V = vector<T>;
template <typename T>
inline bool chmax(T& a, T b);
template <typename T>
inline bool chmin(T& a, T b);
void print_ints(vector<ll> v);
template <typename T>
void drop(T a);

ll N;
V<V<ll>> G;
V<ll> colors;  // 0: 未着色
V<V<ll>> ds;
V<ll> group_ids;

bool check_bi(ll v, ll color) {
  colors[v] = color;

  for (auto to : G[v]) {
    if (colors[to] == color) {
      return false;
    }

    if (colors[to] == 0 && !check_bi(to, -color)) {
      return false;
    }
  }

  return true;
}

bool satisfied(ll s) {
  queue<pair<ll, ll>> q;  // f: edge, s: group

  group_ids[s] = 0;
  for (auto u : G[s]) q.emplace(u, 1);

  while (!q.empty()) {
    auto next = q.front();
    q.pop();

    auto u = next.first;
    auto g = next.second;

    if (group_ids[u] != -1) {
      if (group_ids[u] != g) {
        return false;
      } else {
        continue;
      }
    }

    group_ids[u] = g;

    for (auto v : G[u]) {
      if (group_ids[v] == -1) q.emplace(v, g + 1);
    }
  }

  return true;
}

// 二部グラフであることが構築可能の必要十分条件。解は最長パス + 1
void solve() {
  cin >> N;
  G.assign(N, V<ll>());

  rep(i, 0, N) {
    string e;
    cin >> e;

    rep(j, 0, N) {
      if (e[j] == '1') {
        G[i].push_back(j);
      }
    }
  }

  {
    colors.assign(N, 0);

    if (!check_bi(0, 1)) {
      drop(-1);
    }
  }

  {
    ll INF = 1 << 30;
    ds.assign(N, V<ll>(N, INF));
    rep(i, 0, N) ds[i][i] = 0;
    rep(i, 0, N) {
      for (auto to : G[i]) {
        ds[i][to] = 1;
        ds[to][i] = 1;
      }
    }

    // ワーシャルフロイド
    rep(k, 0, N) rep(i, 0, N) rep(j, 0, N) {
      ds[i][j] = min(ds[i][j], ds[i][k] + ds[k][j]);
    }
  }

  ll max_d = 0;
  rep(i, 0, N) rep(j, 0, N) chmax(max_d, ds[i][j]);

  cout << max_d + 1 << endl;
}

// 「最長パスを与える端点から BFS しグループ割り振りに矛盾が生じる」 ⇔
// 「二部グラフでない」 のようなので、二部グラフ判定でなく前者によって判定を行う
void solve2() {
  cin >> N;
  G.assign(N, V<ll>());

  rep(i, 0, N) {
    string e;
    cin >> e;

    rep(j, 0, N) {
      if (e[j] == '1') {
        G[i].push_back(j);
      }
    }
  }

  {
    ll INF = 1 << 30;
    ds.assign(N, V<ll>(N, INF));
    rep(i, 0, N) ds[i][i] = 0;
    rep(i, 0, N) {
      for (auto to : G[i]) {
        ds[i][to] = 1;
        ds[to][i] = 1;
      }
    }

    // ワーシャルフロイド
    rep(k, 0, N) rep(i, 0, N) rep(j, 0, N) {
      ds[i][j] = min(ds[i][j], ds[i][k] + ds[k][j]);
    }
  }

  ll max_d = 0;
  rep(i, 0, N) rep(j, 0, N) chmax(max_d, ds[i][j]);

  {
    pair<ll, ll> max_pair;
    rep(i, 0, N) rep(j, 0, N) if (ds[i][j] == max_d) max_pair = make_pair(i, j);

    group_ids.assign(N, -1);

    if (!satisfied(max_pair.first)) {
      drop(-1);
    }
  }

  cout << max_d + 1 << endl;
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
  rep(i, 0, v.size()) {
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
