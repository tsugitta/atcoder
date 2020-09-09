// https://atcoder.jp/contests/practice2/tasks/practice2_d

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

void solve() {
  ll H, W;
  cin >> H >> W;

  V<string> mat(H);
  rep(i, H) cin >> mat[i];

  mf_graph<ll> g(H * W + 2);

  ll S = H * W;
  ll T = H * W + 1;

  // S -> even, odd -> T
  rep(h, H) rep(w, W) {
    unless(mat[h][w] == '.') continue;

    ll u = W * h + w;

    if ((h + w) % 2 == 0) {
      g.add_edge(S, u, 1);
    } else {
      g.add_edge(u, T, 1);
    }
  }

  // even -> odd
  rep(h, H) rep(w, W) {
    unless(mat[h][w] == '.') continue;
    unless((h + w) % 2 == 0) continue;

    ll e = W * h + w;

    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};

    rep(i, 4) {
      int nh = h + dy[i];
      int nw = w + dx[i];

      unless(0 <= nh && nh < H && 0 <= nw && nw < W) continue;
      unless(mat[nh][nw] == '.') continue;

      ll o = W * nh + nw;
      g.add_edge(e, o, 1);
    }
  }

  cout << g.flow(S, T) << "\n";

  auto edges = g.edges();

  for (auto e : edges) {
    if (e.from == S || e.to == T || e.flow == 0) continue;
    ll eh = e.from / W;
    ll ew = e.from % W;
    ll oh = e.to / W;
    ll ow = e.to % W;

    if (eh + 1 == oh) {
      mat[eh][ew] = 'v';
      mat[oh][ow] = '^';
    } else if (oh + 1 == eh) {
      mat[oh][ow] = 'v';
      mat[eh][ew] = '^';
    } else if (ew + 1 == ow) {
      mat[eh][ew] = '>';
      mat[oh][ow] = '<';
    } else if (ow + 1 == ew) {
      mat[oh][ow] = '>';
      mat[eh][ew] = '<';
    }
  }

  rep(h, H) cout << mat[h] << "\n";
}
