// https://atcoder.jp/contests/abc143/tasks/abc143_e

#include "algorithm"
#include "iostream"
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
template <typename T>
inline bool chmax(T& a, T b);
template <typename T>
inline bool chmin(T& a, T b);
void print_ints(vector<ll> v);
template <typename T>
void drop(T a);

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
