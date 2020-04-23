// https://atcoder.jp/contests/arc075/tasks/arc075_c

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

struct Fenwick {
  vector<ll> tree;

  Fenwick(ll n) : tree(vector<ll>(n, 0)) {}

  // sum of [0, i)
  ll sum(ll i) {
    ll res = 0;

    for (i--; i >= 0; i = (i & (i + 1)) - 1) {
      res += tree[i];
    }

    return res;
  }

  void add(ll i, ll n) {
    for (ll len = tree.size(); i < len; i |= i + 1) {
      tree[i] += n;
    }
  }
};

void solve() {
  ll N, K;
  cin >> N >> K;

  VL bs(N + 1);

  {
    ll cur = 0;
    bs[0] = cur;

    rep(i, N) {
      ll a;
      cin >> a;
      bs[i + 1] = bs[i] + a - K;
    }
  }

  // 座標圧縮
  {
    VL cs(N + 1);
    rep(i, N + 1) cs[i] = bs[i];

    sort(all(cs));

    rep(i, N + 1) {
      ll b_i = lower_bound(all(cs), bs[i]) - cs.begin();
      bs[i] = b_i;
    }
  }

  ll res = 0;

  Fenwick bit(N + 1);

  rep(i, N + 1) {
    res += bit.sum(bs[i] + 1);
    bit.add(bs[i], 1);
  }

  cout << res << "\n";
}
