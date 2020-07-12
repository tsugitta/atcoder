// https://atcoder.jp/contests/aising2020/tasks/aising2020_d

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

void solve() {
  ll N;
  string S;
  cin >> N >> S;

  ll x_pop_ct = 0;
  rep(i, N) {
    if (S[i] == '1') {
      x_pop_ct++;
    }
  }

  V<map<ll, ll>> two_mods(N, map<ll, ll>());

  for (ll diff : {-1, 1}) {
    if (x_pop_ct + diff == 0) continue;

    two_mods[0][diff] = 1;
    rep(i, N - 1) {
      two_mods[i + 1][diff] = two_mods[i][diff] * 2 % (x_pop_ct + diff);
    }
  }

  // X を x_pop_ct ±1 で割ったあまりに書き換えた値
  map<ll, ll> x_first_changed_map = {};
  for (ll diff : {-1, 1}) {
    if (x_pop_ct + diff == 0) continue;

    rep(i, N) {
      if (S[N - 1 - i] == '1') {
        x_first_changed_map[diff] += two_mods[i][diff];
        x_first_changed_map[diff] %= (x_pop_ct + diff);
      }
    }
  }

  rep(i, N) {
    ll diff = S[i] == '1' ? -1 : 1;
    ll pop_ct = x_pop_ct + diff;
    ll val = x_first_changed_map[diff];

    if (pop_ct == 0) {
      cout << 0 << "\n";
      continue;
    }

    if (diff > 0) {
      val = (val + two_mods[N - 1 - i][diff]) % pop_ct;
    } else if (diff < 0) {
      val = (val + pop_ct - two_mods[N - 1 - i][diff]) % pop_ct;
    }

    ll res = 1;

    while (val > 0) {
      ll pct = __builtin_popcountll(val);
      val = val % pct;
      res++;
    }

    cout << res << "\n";
  }
}
