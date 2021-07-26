// https://atcoder.jp/contests/abc211/tasks/abc211_e

#include <atcoder/all>

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
#include "unordered_set"
#include "vector"
#define rep(i, to) for (ll i = 0; i < ((ll)to); ++i)
#define rep1(i, to) for (ll i = 1; i <= ((ll)to); ++i)
#define repf(i, from, to) for (ll i = from; i < ((ll)to); ++i)
#define repr(i, from) for (ll i = from - 1; i >= 0; --i)
#define all(vec) vec.begin(), vec.end()
#define unless(cond) if (!(cond))
#define fi first
#define se second
#define i128 __int128_t
using namespace std;
using namespace atcoder;
using ll = long long;
using ld = long double;
template <typename T>
using V = vector<T>;
using VL = V<ll>;
template <typename T>
using VV = V<V<T>>;
using VVL = VV<ll>;
template <typename T>
using VVV = VV<V<T>>;
template <typename T, typename U>
using P = pair<T, U>;
using PL = P<ll, ll>;
using VPL = V<PL>;
template <typename T>
using asc_pq = priority_queue<T, V<T>, greater<T>>;

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

template <typename T>
inline ll len(V<T> arr) {
  return arr.size();
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
  ll N, K;
  cin >> N >> K;

  V<string> mat(N);
  rep(i, N) cin >> mat[i];

  unordered_set<string> used;
  ll res = 0;

  auto dfs = [&](auto dfs, ll painted) {
    string mat_str = "";
    rep(h, N) mat_str += mat[h];

    if (used.count(mat_str)) return;
    used.insert(mat_str);

    if (painted == K) {
      res++;
      return;
    }

    VL dhs{-1, 0, 1, 0};
    VL dws{0, 1, 0, -1};

    set<PL> n_ps;

    rep(h, N) rep(w, N) {
      unless(mat[h][w] == '@') continue;

      rep(di, 4) {
        ll dh = dhs[di];
        ll dw = dws[di];

        ll nh = h + dh;
        ll nw = w + dw;

        unless(0 <= nh && nh < N) continue;
        unless(0 <= nw && nw < N) continue;
        unless(mat[nh][nw] == '.') continue;

        n_ps.emplace(nh, nw);
      }
    }

    for (auto [nh, nw] : n_ps) {
      mat[nh][nw] = '@';
      dfs(dfs, painted + 1);
      mat[nh][nw] = '.';
    }
  };

  rep(h, N) rep(w, N) {
    unless(mat[h][w] == '.') continue;

    mat[h][w] = '@';
    dfs(dfs, 1);
    mat[h][w] = '.';
  }

  cout << res << "\n";
}
