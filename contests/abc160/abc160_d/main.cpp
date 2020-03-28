// https://atcoder.jp/contests/abc160/tasks/abc160_d

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
  ll N, X, Y;
  cin >> N >> X >> Y;

  VVL edge_list(N, VL(0));

  rep(i, N - 1) {
    edge_list[i].emplace_back(i + 1);
    edge_list[i + 1].emplace_back(i);
  }

  edge_list[X - 1].emplace_back(Y - 1);
  edge_list[Y - 1].emplace_back(X - 1);

  VVL dist(N, VL(N, INF));
  rep(i, N) dist[i][i] = 0;

  // ダイクストラ
  rep(i, N) {
    priority_queue<PL, V<PL>, greater<PL>> q;
    q.emplace(0, i);

    while (!q.empty()) {
      PL pa = q.top();
      q.pop();
      ll cost = pa.fi;
      ll p = pa.se;

      if (cost > dist[i][p]) continue;

      for (auto np : edge_list[p]) {
        ll nc = cost + 1;
        if (chmin(dist[i][np], nc)) {
          q.emplace(nc, np);
        }
      }
    }
  }

  VL dist_ct(N + 1);

  rep(j, N) rep(i, j) { ++dist_ct[dist[i][j]]; }
  rep1(i, N - 1) { cout << dist_ct[i] << endl; }
}

void solve2() {
  ll N, X, Y;
  cin >> N >> X >> Y;
  --X, --Y;

  VL dist_ct(N);

  rep(j, N) rep(i, j) {
    ll dist = min(j - i, abs(i - X) + 1 + abs(j - Y));

    ++dist_ct[dist];
  }

  rep1(i, N - 1) cout << dist_ct[i] << "\n";
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
