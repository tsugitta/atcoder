// https://atcoder.jp/contests/abc161/tasks/abc161_d

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

void solve() {
  ll K;
  cin >> K;

  queue<ll> q;
  rep1(num, 9) q.push(num);

  rep(i, K - 1) {
    ll n = q.front();
    q.pop();

    if (n % 10 >= 1) q.push(10 * n + (n % 10 - 1));
    q.push(10 * n + (n % 10));
    if (n % 10 <= 8) q.push(10 * n + (n % 10 + 1));
  }

  ll res = q.front();

  cout << res << "\n";
}

// priority_queue なら順番を気にせずに済む
// ただし、桁数が小さいものの方が先に取り出されることには依存している
void solve2() {
  ll K;
  cin >> K;

  priority_queue<ll, V<ll>, greater<ll>> q;
  rep1(num, 9) q.push(num);

  rep(i, K - 1) {
    ll n = q.top();
    q.pop();

    q.push(10 * n + (n % 10));

    if (n % 10 >= 1) q.push(10 * n + (n % 10 - 1));
    if (n % 10 <= 8) q.push(10 * n + (n % 10 + 1));
  }

  ll res = q.top();

  cout << res << "\n";
}

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
