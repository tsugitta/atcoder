// https://atcoder.jp/contests/past202004-open/tasks/past202004_l

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
#define rep(i, to) for (ll i = 0; i < (to); ++i)
#define rep1(i, to) for (ll i = 1; i <= (to); ++i)
#define repf(i, from, to) for (ll i = from; i < (to); ++i)
#define repr(i, from) for (ll i = from - 1; i >= 0; --i)
#define all(vec) vec.begin(), vec.end()
#define unless(cond) if (!(cond))
#define fi first
#define se second
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
void solve2();

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

PL op(PL a, PL b) {
  if (a.fi == b.fi) {
    if (a.se < b.se) {
      return a;
    } else {
      return b;
    }
  }

  if (a.fi < b.fi) {
    return a;
  } else {
    return b;
  }
}

PL e() { return make_pair(INF, -1); }

void solve() {
  ll N, K, D;
  cin >> N >> K >> D;

  VPL as(N);

  rep(i, N) {
    cin >> as[i].fi;
    as[i].se = i;
  }

  segtree<PL, op, e> seg(as);

  ll cur_i = -1;

  VL res(K);
  rep(k, K) {
    ll rest = K - k - 1;
    ll max_i = N - 1 - rest * D;
    if (max_i < 0) drop(-1);

    PL mi = seg.prod(cur_i + 1, max_i + 1);
    res[k] = mi.fi;
    cur_i = mi.se + D - 1;
  }

  rep(i, res.size()) {
    if (i > 0) cout << " ";
    cout << res[i];
  }
  cout << "\n";
}

void solve2() {
  ll N, K, D;
  cin >> N >> K >> D;

  VL as(N);
  rep(i, N) cin >> as[i];

  asc_pq<PL> pq;

  ll last_i = -INF;
  ll next_add_i = 0;

  VL res(K);

  rep(k, K) {
    ll rest = K - k - 1;
    ll max_i = N - 1 - rest * D;

    while (next_add_i <= max_i) {
      pq.emplace(as[next_add_i], next_add_i);
      ++next_add_i;
    }

    if (pq.size() == 0) drop(-1);

    while (true) {
      auto [cand_val, cand_i] = pq.top();
      pq.pop();

      unless(last_i + D <= cand_i) continue;
      last_i = cand_i;
      res[k] = cand_val;
      break;
    }
  }

  rep(i, res.size()) {
    if (i > 0) cout << " ";
    cout << res[i];
  }
  cout << "\n";
}
