// https://atcoder.jp/contests/abc174/tasks/abc174_d

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
  string cs;
  cin >> N >> cs;

  set<ll> r_indices;
  set<ll> w_indices;

  rep(i, N) {
    if (cs[i] == 'R') r_indices.insert(i);
    if (cs[i] == 'W') w_indices.insert(i);
  }

  if (r_indices.size() == 0 || w_indices.size() == 0) drop(0);

  ll res = 0;

  while (1) {
    ll w_i = *w_indices.begin();
    ll r_i = *r_indices.rbegin();

    if (r_i < w_i) break;

    w_indices.erase(w_i);
    r_indices.erase(r_i);

    w_indices.insert(r_i);
    r_indices.insert(w_i);

    ++res;
  }

  cout << res << "\n";
}
