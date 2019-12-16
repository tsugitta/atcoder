// https://atcoder.jp/contests/abc082/tasks/arc087_b

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
  string s;
  ll target_x, target_y;
  cin >> s >> target_x >> target_y;

  VL ds(0);

  ll cur = 0;

  for (auto c : s) {
    if (c == 'T') {
      ds.push_back(cur);
      cur = 0;
    } else if (c == 'F') {
      cur++;
    }
  }

  ds.push_back(cur);

  VL xds(0);
  VL yds(0);

  rep(i, ds.size()) {
    if (i % 2 == 0) xds.push_back(ds[i]);
    if (i % 2 == 1) yds.push_back(ds[i]);
  }

  const ll base = 8000;

  V<V<bool>> xdp(xds.size() + 1, V<bool>(base * 2 + 1));
  V<V<bool>> ydp(yds.size() + 1, V<bool>(base * 2 + 1));

  xdp[0][base] = true;
  ydp[0][base] = true;

  auto fill = [&](V<V<bool>>& dp, VL& ds, bool first_direction_only_forward) {
    rep(i, ds.size()) rep(t, base * 2 + 1) {
      unless(dp[i][t]) continue;

      ll d = ds[i];
      dp[i + 1][t + d] = true;

      if (i == 0 && first_direction_only_forward) continue;
      dp[i + 1][t - d] = true;
    }
  };

  fill(xdp, xds, true);
  fill(ydp, yds, false);

  if (xdp.back()[base + target_x] && ydp.back()[base + target_y]) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
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
