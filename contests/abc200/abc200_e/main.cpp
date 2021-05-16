// https://atcoder.jp/contests/abc200/tasks/abc200_e

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
  ll N, K;
  cin >> N >> K;

  auto c2 = [](ll n) -> ll {
    if (n <= 0) return 0;
    return n * (n - 1) / 2;
  };

  // 包除原理
  // 和が sum になる 1 ~ N の tuple(3 要素) の数
  auto ct_sum3 = [&](ll sum) {
    return c2(sum - 1) - c2(sum - 1 - N) * 3 + c2(sum - 1 - 2 * N) * 3 -
           c2(sum - 1 - 3 * N);
  };

  // 和が sum になる 1 ~ N の pair の数
  auto ct_sum2 = [&](ll sum) {
    return (sum - 1) - max((sum - 1 - N) * 2, 0ll) +
           max((sum - 1 - 2 * N), 0ll);
  };

  ll rest = K;
  ll all_sum = -1;

  rep1(sum, 3 * N) {
    ll ct_for_sum = ct_sum3(sum);

    if (rest > ct_for_sum) {
      rest -= ct_for_sum;
    } else {
      all_sum = sum;
      break;
    }
  }

  ll b_c_sum = -1;

  rep1(a_num, N) {
    ll rest_sum = all_sum - a_num;
    ll ct_for_sum = ct_sum2(rest_sum);

    if (rest > ct_for_sum) {
      rest -= ct_for_sum;
    } else {
      b_c_sum = rest_sum;
      break;
    }
  }

  ll a = all_sum - b_c_sum;
  ll b = max(b_c_sum - N, 1ll) + rest - 1;
  ll c = b_c_sum - b;

  cout << a << " " << b << " " << c << "\n";
}
