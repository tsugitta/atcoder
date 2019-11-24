// https://atcoder.jp/contests/nikkei2019-2-qual/tasks/nikkei2019_2_qual_c

#include "algorithm"
#include "functional"
#include "iostream"
#include "numeric"
#include "queue"
#include "set"
#include "vector"
#define rep(i, to) for (ll i = 0; i < (to); ++i)
#define repf(i, from, to) for (ll i = from; i < (to); ++i)
#define repr(i, from) for (ll i = from - 1; i >= 0; --i)
#define all(vec) vec.begin(), vec.end()
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
struct UnionFind {
  vector<ll> parents;

  UnionFind(ll n) : parents(vector<ll>(n, -1)) {}

  ll root(ll a) {
    if (parents[a] < 0) {
      return a;
    }

    auto r = root(parents[a]);
    parents[a] = r;
    return r;
  }

  bool same(ll a, ll b) { return root(a) == root(b); }

  void merge(ll a, ll b) {
    ll ar = root(a);
    ll br = root(b);

    if (ar == br) {
      return;
    }

    // make less index one as a root
    if (ar > br) {
      swap(ar, br);
    }

    parents[ar] += parents[br];
    parents[br] = ar;
  }

  ll size(ll a) { return -parents[a]; }

  ll group_count() {
    ll res = 0;

    for (auto s : parents) {
      if (s < 0) {
        res++;
      }
    }

    return res;
  }
};

void solve() {
  ll N;
  cin >> N;

  VPL ps(N);
  VL as(N);

  rep(i, N) cin >> as[i], ps[i].fi = as[i];
  rep(i, N) cin >> ps[i].se;

  sort(all(as));
  // B でソートしておく
  sort(all(ps), [](PL a, PL b) { return a.second < b.second; });

  // A をソートしても実現できなければ不可
  rep(i, N) {
    if (as[i] > ps[i].se) drop("No");
  }

  // N-2 回のソートでは N-2 個の要素を任意に入れ替えることができるため、
  // A のソート後で入れ替えなくても条件を満たす 2 要素があれば条件を満たす。
  // これは A のソート後で隣り合う 2 要素を入れ替えても ok
  // かどうかを見れば十分。
  {
    ll ok = false;

    rep(i, N - 1) if (as[i + 1] <= ps[i].se) ok = true;

    if (ok) drop("Yes");
  }

  // A のソート後で入れ替えなくても条件を満たす 2 要素が無いということは、 A
  // をソートしなければならないということとなる。
  // ソートする場合のサイクルの個数を UnionFind で求める
  // そのために、圧縮して A を 0 ~ N-1 にする
  // なお、この時 A に同一の要素は無い。

  rep(i, N) ps[i].fi = lower_bound(all(as), ps[i].fi) - as.begin();

  UnionFind uf(N);

  rep(i, N) uf.merge(i, ps[i].fi);

  if (uf.group_count() == 1) drop("No");
  cout << "Yes" << endl;
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
