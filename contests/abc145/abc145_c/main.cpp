// https://atcoder.jp/contests/abc145/tasks/abc145_c

#include "algorithm"
#include "cmath"
#include "functional"
#include "iomanip"
#include "iostream"
#include "numeric"
#include "queue"
#include "set"
#include "vector"
#define rep(i, to) for (ll i = 0; i < (to); ++i)
#define repf(i, from, to) for (ll i = from; i < (to); ++i)
#define repr(i, from) for (ll i = from - 1; i >= 0; --i)
#define all(vec) vec.begin(), vec.end()
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

double dist(PL a, PL b) {
  return sqrt((b.first - a.first) * (b.first - a.first) +
              (b.second - a.second) * (b.second - a.second));
}

void solve() {
  ll N;
  cin >> N;
  VPL ps(N);

  rep(i, N) {
    ll x, y;
    cin >> x >> y;
    ps[i] = {x, y};
  }

  double distSum = 0;

  rep(j, N) rep(i, j) { distSum += dist(ps[i], ps[j]); }

  double res = 2 * distSum / N;

  cout << fixed << setprecision(10) << res << endl;
}

void solve2() {
  ll N;
  cin >> N;
  VPL ps(N);

  rep(i, N) {
    ll x, y;
    cin >> x >> y;
    ps[i] = {x, y};
  }

  sort(all(ps));

  long double distSum = 0;

  auto fact = [](ll a) {
    ll res = 1;
    rep(i, a) res *= i + 1;
    return res;
  };

  do {
    rep(i, N - 1) distSum += dist(ps[i], ps[i + 1]);
  } while (next_permutation(ps.begin(), ps.end()));

  long double res = distSum / fact(N);

  cout << fixed << setprecision(10) << res << endl;
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
