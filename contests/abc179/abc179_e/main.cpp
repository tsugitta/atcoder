// https://atcoder.jp/contests/abc179/tasks/abc179_e

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

const int MAX_BIT = 33;  // 10^10 < 2^34 - 1

int val[MAX_BIT + 1][100005];  // val[bit][num]: num から 2^bit 操作した値
ll sum[MAX_BIT + 1][100005];  // sum[bit][num]: num から 2^bit 操作した総和

void solve() {
  ll N, X, M;
  cin >> N >> X >> M;

  fill(&val[0][0], &val[0][0] + sizeof(val) / sizeof(val[0][0]), 0);
  fill(&sum[0][0], &sum[0][0] + sizeof(sum) / sizeof(sum[0][0]), 0);

  rep(num, M) {
    val[0][num] = num * num % M;
    sum[0][num] = num;
  }

  rep(bit, MAX_BIT) {
    rep(num, M) {
      val[bit + 1][num] = val[bit][val[bit][num]];

      ll added;
      if (!__builtin_add_overflow(sum[bit][num], sum[bit][val[bit][num]],
                                  &added)) {
        sum[bit + 1][num] = added;
      }
    }
  }

  ll cur = X;
  ll res = 0;

  repr(bit, MAX_BIT + 1) {
    if (N & (1ll << bit)) {
      res += sum[bit][cur];
      cur = val[bit][cur];
    }
  }

  cout << res << "\n";
}
