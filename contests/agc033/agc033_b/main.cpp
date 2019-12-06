// https://atcoder.jp/contests/agc033/tasks/agc033_b

#include "algorithm"
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
  ll H, W, N, sr, sc;
  string S, T;
  cin >> H >> W >> N >> sr >> sc >> S >> T;

  // 1 次元の問題に帰着
  // コマが残れば return される
  auto solve_one_dim = [](ll start, ll limit, VL ss, VL ts) {
    // [l, r] にコマがあれば ok
    ll l = 1;
    ll r = limit;

    repr(i, ts.size()) {
      ll t = ts[i];
      if (t == 1) l = max(l - 1, 1ll);
      if (t == -1) r = min(r + 1, limit);

      ll s = ss[i];
      if (s == 1) r -= 1;
      if (s == -1) l += 1;

      if (r < l) drop("NO");
    }

    if (!(l <= start && start <= r)) drop("NO");
  };

  VL ss_w(N), ts_w(N), ss_h(N), ts_h(N);

  auto fill = [N](VL& w, VL& h, string& str) {
    rep(i, N) {
      char ch = str[i];
      if (ch == 'R') w[i] = 1, h[i] = 0;
      if (ch == 'L') w[i] = -1, h[i] = 0;
      if (ch == 'U') w[i] = 0, h[i] = -1;
      if (ch == 'D') w[i] = 0, h[i] = 1;
    }
  };

  fill(ss_w, ss_h, S);
  fill(ts_w, ts_h, T);

  solve_one_dim(sr, H, ss_h, ts_h);
  solve_one_dim(sc, W, ss_w, ts_w);

  cout << "YES" << endl;
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
