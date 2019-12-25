// https://atcoder.jp/contests/agc006/tasks/agc006_b

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
  ll N, X;

  cin >> N >> X;

  if (X == 1 || X == 2 * N - 1) drop("No");

  cout << "Yes" << endl;

  ll len = 2 * N - 1;
  VL res(len);

  if (N == 2) {
    print_ints({1, 2, 3});
    return;
  }

  set<ll> used;

  used.insert(X);
  used.insert(2 * N - 1);
  used.insert(1);

  if (X == 2 * N - 2) {
    res[len / 2] = X;
    res[len / 2 - 1] = 2 * N - 1;
    res[len / 2 - 2] = 1;
    res[len / 2 + 1] = 2;
    used.insert(2);
  } else {
    res[len / 2] = X;
    res[len / 2 - 1] = 1;
    res[len / 2 - 2] = 2 * N - 1;
    res[len / 2 + 1] = 2 * N - 2;
    used.insert(2 * N - 2);
  }

  ll next_i = 0;

  rep1(num, len) {
    if (used.count(num)) continue;
    while (next_i >= len / 2 - 2 && next_i <= len / 2 + 1) next_i++;

    res[next_i] = num;
    next_i++;
  }

  rep(i, len) cout << res[i] << endl;
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
