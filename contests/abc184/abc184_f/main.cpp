// https://atcoder.jp/contests/abc184/tasks/abc184_f

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

// 半分全列挙
void solve() {
  ll N, T;
  cin >> N >> T;

  VL as, bs;

  rep(i, N / 2) {
    ll a;
    cin >> a;
    as.push_back(a);
  }

  rep(i, N - N / 2) {
    ll b;
    cin >> b;
    bs.push_back(b);
  }

  VL sum_as;
  VL sum_bs;

  ll AN = as.size();
  ll BN = bs.size();

  rep(bit, 1 << AN) {
    ll sum = 0;

    rep(i, AN) {
      if (bit & (1 << i)) sum += as[i];
    }

    if (sum > T) continue;

    sum_as.push_back(sum);
  }

  sort(all(sum_as));

  rep(bit, 1 << BN) {
    ll sum = 0;

    rep(i, BN) {
      if (bit & (1 << i)) sum += bs[i];
    }

    if (sum > T) continue;

    sum_bs.push_back(sum);
  }

  sort(all(sum_bs));

  ll res = 0;

  for (ll sum_a : sum_as) {
    ll target = T - sum_a;
    auto it = upper_bound(all(sum_bs), target);
    it--;
    chmax(res, sum_a + *it);
  }

  cout << res << "\n";
}

void solve2() {
  ll N, T;
  cin >> N >> T;

  VL a_sums, b_sums;
  a_sums.push_back(0);
  b_sums.push_back(0);

  rep(i, N) {
    ll v;
    cin >> v;

    // for(ll a_sum : a_sums) とするとループ対象が増え続けるので NG
    ll size = a_sums.size();
    repr(i, size) {
      ll a_sum = a_sums[i];
      if (a_sum + v > T) continue;
      a_sums.push_back(a_sum + v);
    }

    swap(a_sums, b_sums);
  }

  // 「以下」を lower_bound するには、逆順ソートして lower_bound の最後に
  // greater() を渡せば良い
  sort(b_sums.rbegin(), b_sums.rend());

  ll res = 0;

  for (ll a_sum : a_sums) {
    auto it = lower_bound(all(b_sums), T - a_sum, greater());
    chmax(res, a_sum + *it);
  }

  cout << res << "\n";
}
