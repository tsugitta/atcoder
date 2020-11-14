// https://atcoder.jp/contests/abc182/tasks/abc182_e

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

int dxs[] = {-1, 0, 1, 0};
int dys[] = {0, 1, 0, -1};

void solve() {
  ll H, W, N, M;
  cin >> H >> W >> N >> M;

  int UNKNOWN = 0;
  int LIGHT = 1;
  int BLOCK = 2;
  int OK = 3;

  VVL mat(H, VL(W));

  VPL lights(N);

  rep(i, N) {
    ll h, w;
    cin >> h >> w;
    --h, --w;
    lights[i] = {h, w};
    mat[h][w] = LIGHT;
  }

  rep(i, M) {
    ll h, w;
    cin >> h >> w;
    --h, --w;
    mat[h][w] = BLOCK;
  }

  for (auto& [h, w] : lights) {
    rep(i, 4) {
      int dx = dxs[i];
      int dy = dys[i];

      int nh = h + dy;
      int nw = w + dx;

      while (true) {
        unless(0 <= nh && nh < H) break;
        unless(0 <= nw && nw < W) break;

        if (mat[nh][nw] == LIGHT) break;
        if (mat[nh][nw] == BLOCK) break;
        mat[nh][nw] = OK;

        nh += dy;
        nw += dx;
      }
    }
  }

  ll res = 0;

  rep(h, H) rep(w, W) {
    if (mat[h][w] == LIGHT || mat[h][w] == OK) ++res;
  }

  cout << res << "\n";
}
