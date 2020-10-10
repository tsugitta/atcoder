// https://atcoder.jp/contests/hhkb2020/tasks/hhkb2020_d

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

using mint = modint1000000007;

void solve() {
  auto partial = []() {
    ll N, A, B;
    cin >> N >> A >> B;

    // 一次元で A, B をこの順で重ならないように配置する通り
    // 空白の左右に配置することを考えて、同一の場所に置く場合： N+1,
    // 別の場所に置く場合 C(N+1,2) の和
    mint k = N - A - B < 0 ? 0 : (N - A - B + 2) * (N - A - B + 1) / 2;

    // 一次元で A, B を重ならないように配置する通り
    mint l = k * 2;

    // 一次元で A, B を重なるように配置する通り
    mint m = mint(N - A + 1) * (N - B + 1) - l;

    // 二次元で A, B を重なるように配置する通り
    mint n = m * m;

    mint res = mint(N - A + 1) * (N - A + 1) * (N - B + 1) * (N - B + 1) - n;
    cout << res.val() << "\n";
  };

  ll T;
  cin >> T;

  rep(i, T) partial();
}
