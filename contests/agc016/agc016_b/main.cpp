// https://atcoder.jp/contests/agc016/tasks/agc016_b

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
  cin >> N;

  VL as(N);
  rep(i, N) cin >> as[i];

  ll min_v = *min_element(all(as));
  ll max_v = *max_element(all(as));

  const string Yes = "Yes";
  const string No = "No";

  // 種類数を A とする。
  // 自身の値は自身が唯一の種類であれば A-1、そうでなければ A となる。
  // よって、 A-1 と A のみしか出現しえないため、差が 2 以上であれば不可。

  ll diff = max_v - min_v;
  if (diff >= 2) drop(No);

  if (diff == 0) {
    // 上の議論より、全てが唯一の種類で値が A-1
    // であるか、全てが唯一でない種類かつ値が A のいずれか。

    // 前者の場合、種類数 A は N となる
    if (max_v == N - 1) drop(Yes);

    // 後者の場合、同じ種類のグループを A 個作れるかどうかで判定可能。
    // 全て同じ種類とすることで 1 グループとすることは可能。
    // 最もグループを多くすると、各グループ 2
    // 種類のみからなる floor(N/2) となるから、これ以下の場合のみ可能。
    if (max_v <= N / 2) drop(Yes);

    drop(No);
  } else if (diff == 1) {
    ll small_ct = 0;
    rep(i, N) if (as[i] == min_v)++ small_ct;

    ll large_ct = N - small_ct;

    // 小さい方は唯一の種類、大きい方は複数の種類となる。
    // 大きい方の種類数は [1, large_ct / 2] であるから、
    // small_ct + [1, large_ct / 2] に A が含まれていれば良い。

    if (small_ct + 1 <= max_v && max_v <= small_ct + large_ct / 2) drop(Yes);
    drop(No);
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
