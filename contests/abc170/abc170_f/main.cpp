// https://atcoder.jp/contests/abc170/tasks/abc170_f

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
VL dx = {-1, 0, 1, 0};
VL dy = {0, 1, 0, -1};

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
  ll H, W, K;
  cin >> H >> W >> K;

  ll si, sj, ti, tj;
  cin >> si >> sj >> ti >> tj;
  --si, --sj, --ti, --tj;

  V<string> mat(H);
  rep(i, H) cin >> mat[i];

  V<ll> dist(H * W * 4, INF);

  auto to_id = [&](ll i, ll j, ll dir) { return (i * W + j) * 4 + dir; };

  priority_queue<PL, VPL, greater<PL>> q;

  auto mod_ceil = [&](ll x) { return (x + K - 1) / K * K; };

  rep(dir, 4) {
    ll id = to_id(si, sj, dir);
    dist[id] = 0;
    q.emplace(0, id);
  }

  while (!q.empty()) {
    PL pa = q.top();
    q.pop();

    ll cost = pa.fi;
    ll id = pa.se;

    if (cost > dist[id]) continue;

    ll i = id / 4 / W;
    ll j = id / 4 % W;
    ll dir = id % 4;

    // 向きを変える
    rep(ndir, 4) {
      ll id = to_id(i, j, ndir);
      ll n_cost = mod_ceil(cost);

      if (chmin(dist[id], n_cost)) {
        q.emplace(n_cost, id);
      }
    }

    // 向きそのまま
    {
      ll ni = i + dy[dir];
      ll nj = j + dx[dir];

      unless(0 <= ni && ni < H && 0 <= nj && nj < W) continue;
      unless(mat[ni][nj] == '.') continue;

      ll nid = to_id(ni, nj, dir);
      ll n_cost = cost + 1;

      if (chmin(dist[nid], n_cost)) {
        q.emplace(n_cost, nid);
      }
    }
  }

  ll res = INF;
  rep(dir, 4) chmin(res, dist[to_id(ti, tj, dir)]);

  if (res == INF) drop(-1);

  res = mod_ceil(res) / K;
  cout << res << "\n";
}
