// https://atcoder.jp/contests/abc154/tasks/abc154_d

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
  ll N, K;
  cin >> N >> K;

  V<double> ps(N);
  rep(i, N) cin >> ps[i];

  V<double> es(N);
  rep(i, N) { es[i] = (ps[i] + 1) / 2; }

  double res = 0;
  double cur = 0;

  rep(i, N) {
    cur += es[i];

    if (i + 1 > K) {
      cur -= es[i - K];
    }

    chmax(res, cur);
  }

  cout << fixed << setprecision(12) << res << endl;
}

void solve2() {
  ll N, K;
  cin >> N >> K;

  V<double> ps(N);
  rep(i, N) cin >> ps[i];

  V<double> es(N);
  rep(i, N) { es[i] = (ps[i] + 1) / 2; }

  ld res = 0;
  ld cur = 0;
  queue<ld> q;

  rep(i, N) {
    cur += es[i];
    q.push(es[i]);

    if (q.size() > K) {
      ld v = q.front();
      q.pop();
      cur -= v;
    }

    if (q.size() == K) {
      chmax(res, cur);
    }
  }

  cout << fixed << setprecision(12) << res << endl;
}

struct exit_exception : public std::exception {
  const char* what() const throw() { return "Exited"; }
};

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
