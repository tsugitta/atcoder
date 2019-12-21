// https://atcoder.jp/contests/abc019/tasks/abc019_3

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

  sort(all(as));

  ll res = 0;

  auto exists = [as](ll v) -> bool {
    ll mul = 2;

    while (v * mul <= 1e9) {
      auto it = lower_bound(all(as), v * mul);
      if (it != as.end() && *it == v * mul) return true;
      mul *= 2;
    };

    return false;
  };

  for (auto a : as) {
    unless(exists(a)) res++;
  }

  cout << res << endl;
}

void solve2() {
  ll N;
  cin >> N;

  VL as(N);
  rep(i, N) cin >> as[i];

  for (auto& a : as) {
    while (a % 2 == 0) a /= 2;
  }

  set<ll> s;
  for (auto a : as) s.insert(a);

  cout << s.size() << endl;
}

void solve3() {
  ll N;
  cin >> N;

  VL as(N);
  rep(i, N) cin >> as[i];

  for (auto& a : as) {
    while (a % 2 == 0) a /= 2;
  }

  sort(all(as));

  ll res = 1;

  rep(i, N - 1) {
    if (as[i] != as[i + 1]) res++;
  }

  cout << res << endl;
}

struct exit_exception : public std::exception {
  const char* what() const throw() { return "Exited"; }
};

#ifndef TEST
int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  try {
    solve3();
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
