// https://atcoder.jp/contests/arc089/tasks/arc089_b

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

void solve() {
  ll N, K;
  cin >> N >> K;

  VVL mat(2 * K, VL(2 * K));

  rep(i, N) {
    ll x, y;
    char c;
    cin >> x >> y >> c;

    if (c == 'W') y += K;

    x %= 2 * K;
    y %= 2 * K;

    mat[y][x]++;
  }

  VVL mat_sum(2 * K + 1, VL(2 * K + 1));
  rep(h, 2 * K) rep(w, 2 * K) {
    mat_sum[h + 1][w + 1] += mat_sum[h + 1][w] + mat[h][w];
  }
  rep(w, 2 * K) rep(h, 2 * K) mat_sum[h + 1][w + 1] += mat_sum[h][w + 1];

  auto ct_inside_square = [&](ll bl_h, ll bl_w) {
    if (bl_w > 2 * K || bl_h > 2 * K) return 0ll;
    ll tr_h = min(2 * K - 1, bl_h + K - 1);
    ll tr_w = min(2 * K - 1, bl_w + K - 1);
    if (tr_h < 0 || tr_w < 0) return 0ll;

    ll res = mat_sum[tr_h + 1][tr_w + 1] - mat_sum[tr_h + 1][max(0ll, bl_w)] -
             mat_sum[max(0ll, bl_h)][tr_w + 1] +
             mat_sum[max(0ll, bl_h)][max(0ll, bl_w)];

    return res;
  };

  ll res = 0;

  rep(h, K) rep(w, 2 * K) {
    ll r = 0;

    r += ct_inside_square(h, w);
    r += ct_inside_square(h + K, w + K);
    r += ct_inside_square(h - K, w + K);
    r += ct_inside_square(h + K, w - K);
    r += ct_inside_square(h - K, w - K);
    r += ct_inside_square(h - 2 * K, w);
    r += ct_inside_square(h, w - 2 * K);

    chmax(res, r);
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
