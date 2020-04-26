// https://atcoder.jp/contests/abc164/tasks/abc164_e

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
  ll N, M, S;
  cin >> N >> M >> S;

  struct Edge {
    ll to, silver_cost, time_cost;
  };

  ll sum_silver_cost = 0;

  V<V<Edge>> edge_list(N);
  VL change_cts(N);
  VL change_time_costs(N);

  rep(i, M) {
    ll u, v, silver, time;
    cin >> u >> v >> silver >> time;
    --u, --v;
    sum_silver_cost += silver;
    edge_list[u].push_back({v, silver, time});
    edge_list[v].push_back({u, silver, time});
  }

  rep(i, N) {
    cin >> change_cts[i];
    cin >> change_time_costs[i];
  }

  // ダイクストラ
  // costs[i][silver_ct]: silver_ct の枚数を持った頂点 i までの最小コスト
  VVL costs(N, VL(sum_silver_cost + 1, INF));

  ll initial_s = min(S, sum_silver_cost);

  priority_queue<P<PL, ll>, V<P<PL, ll>>, greater<P<PL, ll>>> q;
  q.emplace(PL(0, initial_s), 0);

  while (!q.empty()) {
    auto p = q.top();
    q.pop();

    ll cur_time = p.fi.fi;
    ll cur_silver = p.fi.se;
    ll u = p.se;

    if (cur_time > costs[u][cur_silver]) continue;

    for (auto e : edge_list[u]) {
      rep(changed_ct, INF) {
        ll n_silver = cur_silver + change_cts[u] * changed_ct - e.silver_cost;
        if (n_silver < 0) continue;
        if (n_silver > sum_silver_cost) break;
        ll n_time = cur_time + change_time_costs[u] * changed_ct + e.time_cost;

        if (chmin(costs[e.to][n_silver], n_time)) {
          q.emplace(PL(n_time, n_silver), e.to);
        }
      }
    }
  }

  rep(i, N) {
    if (i == 0) continue;
    ll res = *min_element(all(costs[i]));
    cout << res << "\n";
  }
}
