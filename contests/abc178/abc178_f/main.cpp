// https://atcoder.jp/contests/abc178/tasks/abc178_f

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

void solve() {
  ll N;
  cin >> N;

  VL as(N);
  rep(i, N) cin >> as[i];

  VL bs(N);
  rep(i, N) cin >> bs[i];

  auto print_and_exit = [&]() {
    cout << "Yes"
         << "\n";

    rep(i, N) {
      if (i > 0) cout << " ";
      cout << bs[i];
    }
    cout << "\n";
    throw exit_exception();
  };

  reverse(all(bs));

  // 逆順ソートすれば、被っている要素はたかだか一種類となり、範囲となる
  // [same_l, same_r) で被っているとする
  ll same_l = -1;
  ll same_r = -1;

  rep(i, N) {
    if (as[i] == bs[i] && same_l == -1) {
      same_l = i;
    }

    if (as[i] != bs[i] && same_l != -1) {
      same_r = i;
      break;
    }
  }

  if (same_l == -1) print_and_exit();
  if (same_r == -1) same_r = same_l + 1;

  ll ni = same_l;

  rep(i, N) {
    if (ni == same_r) break;
    if (same_l <= i && i < same_r) continue;

    if (as[i] != bs[ni] && bs[i] != as[ni]) {
      swap(bs[i], bs[ni++]);
    }
  }

  if (ni < same_r) drop("No");

  print_and_exit();
}
