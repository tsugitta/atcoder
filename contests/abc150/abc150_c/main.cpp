// https://atcoder.jp/contests/abc150/tasks/abc150_c

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
  ll N;
  cin >> N;

  VL ps(N);
  VL qs(N);
  rep(i, N) cin >> ps[i];
  rep(i, N) cin >> qs[i];

  VL a(N);
  rep(i, N) a[i] = i + 1;

  ll pi;
  ll qi;

  ll ct = 0;
  do {
    if (a == ps) pi = ct;
    if (a == qs) qi = ct;
    ct++;
  } while (next_permutation(all(a)));

  cout << abs(pi - qi) << endl;
}

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

void solve2() {
  ll N;
  cin >> N;

  VL ps(N);
  VL qs(N);
  rep(i, N) cin >> ps[i];
  rep(i, N) cin >> qs[i];

  auto fact = [](ll a) -> ll {
    ll res = 1;

    while (a > 0) {
      res *= a;
      a--;
    }

    return res;
  };

  auto get_index = [&](VL& vs) -> ll {
    ll smaller_ct = 0;

    Fenwick bit(N + 1);

    rep(i, N) {
      ll v = vs[i];
      ll rest_ct = N - i - 1;
      ll used_smaller_num_ct = bit.sum(v);
      smaller_ct += (v - 1 - used_smaller_num_ct) * fact(rest_ct);
      bit.add(v, 1);
    }

    return smaller_ct;
  };

  cout << abs(get_index(ps) - get_index(qs)) << endl;
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
