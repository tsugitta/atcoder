// https://atcoder.jp/contests/abc219/tasks/abc219_e

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
  VPL houses;

  ll N = 4;

  rep(h, N) rep(w, N) {
    ll val;
    cin >> val;
    if (val) houses.emplace_back(h, w);
  }

  ll res = 0;

  rep(bit, (1ll << (N * N))) {
    VV<bool> ok_mat(N, V<bool>(N));

    rep(i, 16) {
      unless(bit & (1ll << i)) continue;

      ll h = i / N;
      ll w = i % N;
      ok_mat[h][w] = true;
    }

    // 外側を同一グループに分類するため、外側の超頂点を末端に用意する
    dsu uf(N * N + 1);
    ll OUTSIDE = N * N;

    auto hw_to_id = [&](ll h, ll w) { return h * N + w; };

    rep(h, N) rep(w, N) {
      if (!ok_mat[h][w] && (h == 0 || h == N - 1 || w == 0 || w == N - 1)) {
        uf.merge(hw_to_id(h, w), OUTSIDE);
      }

      for (auto [dh, dw] : VPL{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}) {
        ll nh = h + dh;
        ll nw = w + dw;

        unless(0 <= nh && nh < N && 0 <= nw && nw < N) continue;

        if (ok_mat[h][w] == ok_mat[nh][nw]) {
          uf.merge(hw_to_id(h, w), hw_to_id(nh, nw));
        }
      }
    }

    // 内側と外側の 2 つのみ
    unless(uf.groups().size() == 2) continue;

    unless(all_of(all(houses), [&](PL house) {
      auto [hh, hw] = house;
      return ok_mat[hh][hw];
    })) {
      continue;
    }

    res++;
  }

  cout << res << "\n";
}
