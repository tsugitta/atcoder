// https://atcoder.jp/contests/agc043/tasks/agc043_b

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
inline bool chmax(T& a, T b);
template <typename T>
inline bool chmin(T& a, T b);
void print_ints(vector<ll> v);
template <typename T>
void drop(T a);

const ll INF = 1e18;

void solve() {
  ll N;
  string S;
  cin >> N >> S;

  VL as(N);
  rep(i, N) as[i] = (S[i] - '0') - 1;

  // C(N-1, i) が奇数か偶数か
  VL comb_parity(N);

  {
    // i! が 2 で割れる回数
    VL fact_two_div_ct(N);

    rep1(num, N - 1) {
      ll ct = 0;
      ll _num = num;
      while (_num % 2 == 0) ++ct, _num /= 2;

      fact_two_div_ct[num] = fact_two_div_ct[num - 1] + ct;
    }

    rep(i, N) {
      ll two_div_ct = fact_two_div_ct[N - 1] - fact_two_div_ct[i] -
                      fact_two_div_ct[N - 1 - i];
      comb_parity[i] = two_div_ct > 0 ? 0 : 1;
    }
  }

  // 答えの偶奇を求める。奇であれば 1 で確定
  {
    ll parity = 0;

    rep(i, N) {
      if (as[i] % 2 == 0 || comb_parity[i] == 0) continue;
      parity ^= 1;
    }

    if (parity == 1) drop(1);
  }

  // 答えが 2 だとすると、１つ目の列に 1 は存在し得ない
  if (any_of(all(as), [](ll v) { return v == 1; })) {
    drop(0);
  }

  // 0 か 2 か存在し得ないため、 2 を 1 と捉えた時の
  // 答えの偶奇を見て、奇数であれば 2 偶数であれば 0 が答えとなる
  {
    ll parity = 0;

    rep(i, N) {
      if (as[i] == 0 || comb_parity[i] == 0) continue;
      parity ^= 1;
    }

    if (parity == 1) {
      drop(2);
    } else {
      drop(0);
    }
  }
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
  } catch (exception e) {
    ll x = 1;
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
