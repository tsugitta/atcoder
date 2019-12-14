// https://atcoder.jp/contests/arc073/tasks/arc073_b

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
  ll N, W;
  cin >> N >> W;

  struct Item {
    ll w;
    ll v;
  };

  V<Item> is(N);

  rep(i, N) {
    ll w, v;
    cin >> w >> v;
    is[i] = {w, v};
  }

  ll w_diff = 3;
  ll max_w = w_diff * (N - 1);

  // dp[i][w][ct]: i >= 1 番目のアイテムまでで重さ w
  // 以下での価値の最大値. ct 個選んだ場合。 w は先頭の要素の重さとの差
  V<VVL> dp(N + 1, VVL(max_w + 1, VL(N + 1)));

  ll w_base = is[0].w;

  rep(i, N) rep(w, max_w + 1) rep(ct, N) {
    auto item = is[i];

    chmax(dp[i + 1][w][ct], dp[i][w][ct]);

    if (w + item.w - w_base <= max_w) {
      chmax(dp[i + 1][w + item.w - w_base][ct + 1], dp[i][w][ct] + item.v);
    }
  }

  ll res = 0;

  rep(ct, N + 1) {
    ll w = w_base * ct;
    if (w > W) continue;
    ll rest_w = W - w;

    chmax(res, dp[N][min(rest_w, max_w)][ct]);
  }

  cout << res << endl;
}

void solve2() {
  ll N, W;
  cin >> N >> W;

  ll w_diff = 3;
  VVL values(w_diff + 1, VL());

  ll base_w;

  rep(i, N) {
    ll w, v;
    cin >> w >> v;

    if (i == 0) base_w = w;

    values[w - base_w].push_back(v);
  }

  rep(i, w_diff + 1) sort(values[i].rbegin(), values[i].rend());

  ll res = 0;

  rep(i, values[0].size() + 1) rep(j, values[1].size() + 1) {
    rep(k, values[2].size() + 1) rep(l, values[3].size() + 1) {
      ll w = (i + j + k + l) * base_w + j + 2 * k + 3 * l;
      unless(w <= W) continue;

      ll v = 0;

      rep(m, i) v += values[0][m];
      rep(m, j) v += values[1][m];
      rep(m, k) v += values[2][m];
      rep(m, l) v += values[3][m];

      chmax(res, v);
    }
  }

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
