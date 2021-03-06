// https://atcoder.jp/contests/arc104/tasks/arc104_b

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
#include "unordered_map"
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

  ll at_diff = 0;
  ll cg_diff = 0;

  unordered_map<int, unordered_map<int, int>> mp;
  mp[at_diff][cg_diff] = 1;

  ll res = 0;

  rep(i, N) {
    char c = S[i];

    if (c == 'A') at_diff++;
    if (c == 'T') at_diff--;
    if (c == 'C') cg_diff++;
    if (c == 'G') cg_diff--;

    res += mp[at_diff][cg_diff];
    mp[at_diff][cg_diff]++;
  }

  cout << res << "\n";
}

void solve2() {
  ll N;
  string S;
  cin >> N >> S;

  ll res = 0;

  rep(i, N) {
    ll at_diff = 0;
    ll cg_diff = 0;

    repf(j, i, N) {
      char c = S[j];
      if (c == 'A') at_diff++;
      if (c == 'T') at_diff--;
      if (c == 'C') cg_diff++;
      if (c == 'G') cg_diff--;

      if (at_diff == 0 && cg_diff == 0) res++;
    }
  }

  cout << res << "\n";
}
