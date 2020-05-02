// https://atcoder.jp/contests/abc165/tasks/abc165_e

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
  ll N, M;
  cin >> N >> M;

  // 幅 1, 3, 5.. のペアを前方に、
  // 幅 2, 4, 6.. のペアを後方に配置
  ll forward_ct = (M + 1) / 2;
  ll back_ct = M - forward_ct;

  ll forward_begin_i = 1;
  ll forward_end_i = forward_begin_i + (2 * forward_ct - 1);

  rep(i, forward_ct) {
    ll a = forward_begin_i + i;
    ll b = forward_end_i - i;
    cout << a << " " << b << "\n";
  }

  ll back_begin_i = forward_end_i + 1;
  ll back_end_i = back_begin_i + (2 * back_ct - 1) + 1;

  rep(i, back_ct) {
    ll a = back_begin_i + i;
    ll b = back_end_i - i;
    cout << a << " " << b << "\n";
  }
}
