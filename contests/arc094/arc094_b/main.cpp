// https://atcoder.jp/contests/arc094/tasks/arc094_b

#include "algorithm"
#include "iostream"
#include "set"
#include "vector"
#define rep(i, from, to) for (ll i = from; i < (to); ++i)
using namespace std;
typedef long long ll;
template <typename T>
using V = vector<T>;
template <typename T>
inline bool chmax(T& a, T b);
template <typename T>
inline bool chmin(T& a, T b);
void print_ints(vector<ll> v);
template <typename T>
void drop(T a);

ll partial(ll a, ll b) {
  if (a == b) {
    // 1, 2 回目のコンテストのどちらか一方で a 以下を取る必要がある。
    // よって最大値は 2*(a-1)
    // (a-i)(a+i) = a^2 - i^2 < a^2 より、
    // (a-i) と (a+i) でペアを作っていけば最大値を実現できる
    return 2 * (a - 1);
  }

  if (a > b) {
    swap(a, b);
  }

  // a 側については、 a-1 と b+1 以上のペアは (a-i)(b+i) - ab = (a-b)i-i^2 < 0
  // より条件を満たす。
  // b 側が最大で a 側の a+1 以上といくつペアを作れるかを二分探索。
  ll ok = 0, ng = 1LL << 31;

  while (ng - ok > 1) {
    ll mid = (ok + ng) / 2;
    // mid ペア作れるとき、それぞれ (a+mid-i+1) と i (i = 1, 2, .., mid)
    // と表せ、その最大ペアは arg = (a+mid+1)/2 とすると a+mid+1 - arg
    // なおこれが偶数であれば軸は整数となり問題がなく、奇数であれば軸は二整数の中間だから
    // 切り捨て切り上げを気にする必要はない
    ll arg = (a + mid + 1) / 2;
    ll mul = arg * (a + mid + 1 - arg);

    if (mul < a * b) {
      ok = mid;
    } else {
      ng = mid;
    }
  }

  return ok + a - 1;
}

void solve() {
  ll Q;
  cin >> Q;

  rep(i, 0, Q) {
    ll A, B;
    cin >> A >> B;

    cout << partial(A, B) << endl;
  }
}

struct exit_exception : public std::exception {
  const char* what() const throw() { return "Exited"; }
};

#ifndef TEST
int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  solve();
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
  rep(i, 0, v.size()) {
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
