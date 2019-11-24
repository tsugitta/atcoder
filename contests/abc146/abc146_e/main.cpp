// https://atcoder.jp/contests/abc146/tasks/abc146_e

#include "algorithm"
#include "cmath"
#include "functional"
#include "iostream"
#include "map"
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

const ll INF = 1e18;

void solve() {
  ll N, K;
  cin >> N >> K;

  VL as(N);
  rep(i, N) cin >> as[i];

  VL rems(N + 1);
  rep(i, N) rems[i + 1] = rems[i] + as[i];
  rep(i, N + 1) rems[i] = (rems[i] - i + K) % K;

  map<ll, ll> m;

  ll res = 0;

  // i を右端とするものの個数を足していく
  rep(i, N + 1) {
    res += m[rems[i]];

    m[rems[i]]++;

    if (i - K + 1 >= 0) {
      m[rems[i - K + 1]]--;
    }
  }

  cout << res << endl;
}

// A を 1 ずつ減らせば区間の和が K の倍数となるものの個数を数える問題となる
void solve2() {
  ll N, K;
  cin >> N >> K;

  VL as(N);
  rep(i, N) cin >> as[i];
  rep(i, N) as[i]--;

  VL rems(N + 1);
  rep(i, N) rems[i + 1] = (rems[i] + as[i]) % K;

  map<ll, ll> m;

  ll res = 0;

  // i を右端とするものの個数を足していく
  rep(i, N + 1) {
    res += m[rems[i]];

    m[rems[i]]++;

    if (i - K + 1 >= 0) {
      m[rems[i - K + 1]]--;
    }
  }

  cout << res << endl;
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
