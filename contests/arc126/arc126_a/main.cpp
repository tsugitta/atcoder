// https://atcoder.jp/contests/arc126/tasks/arc126_a

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
  ll T;
  cin >> T;

  while (T--) {
    ll N2, N3, N4;
    cin >> N2 >> N3 >> N4;

    ll res = 0;

    ll six_ct = N3 / 2;

    // 3, 3, 4
    ll six_with_four = min(six_ct, N4);
    res += six_with_four;
    six_ct -= six_with_four;
    N4 -= six_with_four;

    // 3, 3, 2, 2
    // 3 が 1 個以下 or 4 が　0 個の前提となるため、 4, 4, 2
    // とは共存しない。よって順不同
    ll six_with_four_by_two = min(six_ct, N2 / 2);
    res += six_with_four_by_two;
    six_ct -= six_with_four_by_two;
    N2 -= six_with_four_by_two * 2;

    // 4, 4, 2
    ll eight_by_four_with_two = min(N4 / 2, N2);
    res += eight_by_four_with_two;
    N4 -= eight_by_four_with_two * 2;
    N2 -= eight_by_four_with_two;

    // 4, 2, 2, 2
    ll four_with_six_by_two = min(N4, N2 / 3);
    res += four_with_six_by_two;
    N4 -= four_with_six_by_two;
    N2 -= four_with_six_by_two * 3;

    // 2, 2, 2, 2, 2
    res += N2 / 5;

    cout << res << "\n";
  }
}
