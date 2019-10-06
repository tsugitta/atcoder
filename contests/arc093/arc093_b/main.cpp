// https://atcoder.jp/contests/arc093/tasks/arc093_b

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

void solve() {
  ll A, B;
  cin >> A >> B;

  auto mat = V<string>(100);

  // 上半分が白、 下半分が黒
  rep(i, 0, 50) mat[i] = string(100, '.');
  rep(i, 50, 100) mat[i] = string(100, '#');

  // 上半分に B-1 個の黒点を置く
  rep(i, 0, B - 1) {
    ll h = i / 50;
    ll w = i % 50;
    mat[2 * h][2 * w] = '#';
  }

  // 下半分に A-1 個の白点を置く
  rep(i, 0, A - 1) {
    ll h = i / 50;
    ll w = i % 50;
    mat[99 - 2 * h][2 * w] = '.';
  }

  print_ints(V<ll>{100, 100});
  rep(i, 0, 100) cout << mat[i] << endl;
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
