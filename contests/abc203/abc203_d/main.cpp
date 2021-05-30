// https://atcoder.jp/contests/abc203/tasks/abc203_d

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

  VVL mat(N, VL(N));
  rep(h, N) rep(w, N) cin >> mat[h][w];

  ll ng = -1;
  ll ok = INF;

  while (ok - ng > 1) {
    ll mid = (ok + ng) / 2;

    VVL one_mat(N, VL(N));

    rep(h, N) rep(w, N) one_mat[h][w] = mat[h][w] <= mid ? 1 : 0;

    VVL acc_one_ct(N + 1, VL(N + 1));

    /** 単一ループで埋める場合は差し引きを考慮する必要がある */
    // rep1(h, N) rep1(w, N) {
    //   if (one_mat[h - 1][w - 1]) acc_one_ct[h][w] += 1;
    //   acc_one_ct[h][w] += acc_one_ct[h - 1][w];
    //   acc_one_ct[h][w] += acc_one_ct[h][w - 1];
    //   acc_one_ct[h][w] -= acc_one_ct[h - 1][w - 1];
    // }

    /** 複数ループで埋める場合は行・列ごとに考えるだけで良い */
    rep(h, N) rep(w, N) if (one_mat[h][w]) acc_one_ct[h + 1][w + 1] = 1;
    rep(h, N + 1) rep(w, N) acc_one_ct[h][w + 1] += acc_one_ct[h][w];
    rep(h, N) rep(w, N + 1) acc_one_ct[h + 1][w] += acc_one_ct[h][w];

    bool found = false;

    rep(h, N) {
      unless(h + K - 1 < N) continue;

      rep(w, N) {
        unless(w + K - 1 < N) continue;

        ll ct = acc_one_ct[h + K][w + K] - acc_one_ct[h][w + K] -
                acc_one_ct[h + K][w] + acc_one_ct[h][w];

        if (ct >= (K * K + 1) / 2) {
          found = true;
          break;
        }
      }
    }

    if (found) {
      ok = mid;
    } else {
      ng = mid;
    }
  }

  cout << ok << "\n";
}
