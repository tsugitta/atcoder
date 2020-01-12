// https://atcoder.jp/contests/abc151/tasks/abc151_d

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

ll H, W;
V<string> mat;

VPL directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

ll get_max(ll h, ll w) {
  if (mat[h][w] == '#') return 0;

  VVL visited(H, VL(W));

  VPL q;
  q.push_back({h, w});
  visited[h][w] = 1;

  ll res = 0;

  while (q.size() > 0) {
    VPL nq(0);

    for (auto pa : q) {
      ll ph = pa.fi;
      ll pw = pa.se;

      for (auto d : directions) {
        ll nh = ph + d.fi;
        ll nw = pw + d.se;

        unless(0 <= nh && nh < H && 0 <= nw && nw < W) continue;
        unless(mat[nh][nw] == '.') continue;
        if (visited[nh][nw]) continue;
        visited[nh][nw] = 1;
        nq.push_back({nh, nw});
      }
    }

    res++;
    q = nq;
  }

  res--;
  return res;
}

void solve() {
  cin >> H >> W;

  mat = V<string>(H);

  rep(i, H) { cin >> mat[i]; }

  ll res = 0;

  rep(h, H) rep(w, W) chmax(res, get_max(h, w));

  cout << res << endl;
}

VL dx = {1, 0, -1, 0};
VL dy = {0, 1, 0, -1};

// ワーシャルフロイド
void solve2() {
  cin >> H >> W;

  mat = V<string>(H);

  rep(i, H) { cin >> mat[i]; }

  VVL edge_mat(H * W, VL(H * W));

  auto id = [&](ll h, ll w) { return h * W + w; };

  rep(h, H) rep(w, W) {
    if (mat[h][w] == '#') continue;

    rep(i, 4) {
      ll nh = h + dy[i];
      ll nw = w + dx[i];
      unless(0 <= nh && nh < H && 0 <= nw && nw < W) continue;
      unless(mat[nh][nw] == '.') continue;

      edge_mat[id(h, w)][id(nh, nw)] = 1;
    }
  }

  VVL ds(H * W, VL(H * W));

  rep(i, H * W) rep(j, H * W) {
    if (edge_mat[i][j]) {
      ds[i][j] = 1;
    } else {
      ds[i][j] = INF;
    }
  }

  // ワーシャルフロイド
  rep(k, H * W) rep(i, H * W) rep(j, H * W) {
    ds[i][j] = min(ds[i][j], ds[i][k] + ds[k][j]);
  }

  ll res = 0;
  rep(j, H * W) rep(i, j) if (ds[i][j] != INF) chmax(res, ds[i][j]);

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
