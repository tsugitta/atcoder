// https://atcoder.jp/contests/abc099/tasks/abc099_d

#include "algorithm"
#include "iostream"
#include "queue"
#include "set"
#include "vector"
#define rep(i, to) for (ll i = 0; i < (to); ++i)
#define repf(i, from, to) for (ll i = from; i < (to); ++i)
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

void solve() {
  ll N, C;
  cin >> N >> C;
  VVL ds(C, VL(C));
  VVL cs(N, VL(N));

  // counts[parity][color]: その parity の中の color の数
  VVL counts(3, VL(C));

  rep(i, C) rep(j, C) cin >> ds[i][j];
  rep(i, N) rep(j, N) {
    cin >> cs[i][j];
    cs[i][j]--;
    counts[(i + j) % 3][cs[i][j]]++;
  }

  ll res = 1e18;

  rep(fc, C) rep(sc, C) rep(tc, C) {
    if (fc == sc || sc == tc || tc == fc) continue;
    VL ideal = VL({fc, sc, tc});
    ll _res = 0;

    rep(parity, 3) rep(from_c, C) {
      _res += ds[from_c][ideal[parity]] * counts[parity][from_c];
    }

    chmin(res, _res);
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

ll pow(ll a, ll e) {
  ll res = 1;

  while (e > 0) {
    if ((e & 1) == 1) {
      res *= a;
    }

    res *= res;
    e >>= 1;
  }

  return res;
}
