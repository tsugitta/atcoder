// https://atcoder.jp/contests/arc126/tasks/arc126_c

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

  VL as(N);
  for (ll& a : as) cin >> a;

  sort(all(as));
  ll a_max = *max_element(all(as));

  VL ct_acc(a_max + 1);   // a 以下の値の個数
  VL sum_acc(a_max + 1);  // a 以下の値の総和
  {
    VL cts(a_max + 1);
    for (ll a : as) cts[a]++;

    rep(i, a_max + 1) ct_acc[i] = cts[i] + (i > 0 ? ct_acc[i - 1] : 0);
    rep(i, a_max + 1) sum_acc[i] = cts[i] * i + (i > 0 ? sum_acc[i - 1] : 0);
  }

  ll res = 0;

  rep1(target_gcd, a_max) {
    ll required_ct = 0;

    // k*target_gcd - 1 < a <= k*target_gcd でグループ分け
    rep1(multiple, (a_max + target_gcd - 1) / target_gcd) {
      ll target_num = multiple * target_gcd;
      ll lower_bound_num = (multiple - 1) * target_gcd + 1;

      ll ct_total =
          ct_acc[min(target_num, a_max)] - ct_acc[lower_bound_num - 1];
      ll sum_total =
          sum_acc[min(target_num, a_max)] - sum_acc[lower_bound_num - 1];

      required_ct += target_num * ct_total - sum_total;
    }

    if (required_ct <= K) chmax(res, target_gcd);
  }

  // a_max より大きい値が答えとなるケースは、全ての要素をその値に変更するケース
  if (res == a_max) {
    ll total_sum = sum_acc[a_max] + K;
    drop(total_sum / N);
  }

  cout << res << "\n";
}
