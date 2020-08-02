// https://atcoder.jp/contests/abc174/tasks/abc174_f

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
  ll N, Q;
  cin >> N >> Q;

  VL cs(N);
  rep(i, N) cin >> cs[i];

  VL last_i(N + 1, -1);  // 各数字の最後に現れた index
  VL next_index(N, -1);  // 次に同じ数字が現れる index

  rep(i, N) {
    ll last = last_i[cs[i]];
    if (last != -1) next_index[last] = i;
    last_i[cs[i]] = i;
  }

  V<VPL> qs(N);
  rep(qi, Q) {
    ll l, r;
    cin >> l >> r;
    --l, --r;
    qs[l].emplace_back(r, qi);
  }

  Fenwick bit(N);
  VL res(Q);

  // その範囲 (r - l + 1) から重複分を引く
  repr(l, N) {
    if (next_index[l] != -1) bit.add(next_index[l], 1);

    for (auto [r, qi] : qs[l]) {
      res[qi] = r - l + 1 - bit.sum(r + 1);
    }
  }

  rep(i, Q) cout << res[i] << "\n";
}
