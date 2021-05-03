// https://atcoder.jp/contests/zone2021/tasks/zone2021_c

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
#include "unordered_set"
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
  ll N;
  cin >> N;

  ll CATEGORY_CT = 5;

  VVL as(N, VL(CATEGORY_CT));

  rep(i, N) rep(j, 5) cin >> as[i][j];

  ll ok = 0;
  ll ng = INF;

  auto is_ok = [&](ll res) {
    set<set<ll>> satisfied_category_set;

    rep(i, N) {
      set<ll> satisfied;

      rep(c, CATEGORY_CT) {
        if (as[i][c] >= res) satisfied.insert(c);
      }

      if (satisfied.size()) satisfied_category_set.insert(satisfied);
    }

    V<set<ll>> satisfied_categories(all(satisfied_category_set));

    // 別の要素を選んでも同一の set が得られることがあり得るため、重複を許す
    rep(k, satisfied_categories.size()) rep(j, k + 1) rep(i, j + 1) {
      set<ll> satisfied;

      rep(c, CATEGORY_CT) {
        for (auto idx : {i, j, k}) {
          if (satisfied_categories[idx].count(c)) satisfied.insert(c);
        }
      }

      if (satisfied.size() == CATEGORY_CT) return true;
    }

    return false;
  };

  while (ng - ok > 1) {
    ll mid = ok + (ng - ok) / 2;

    if (is_ok(mid)) {
      ok = mid;
    } else {
      ng = mid;
    }
  }

  cout << ok << "\n";
}
