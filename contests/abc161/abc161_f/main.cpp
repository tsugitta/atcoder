// https://atcoder.jp/contests/abc161/tasks/abc161_f

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

VPL factorize(ll n) {
  VPL res;

  for (ll i = 2; i * i <= n; i++) {
    if (n % i != 0) continue;

    auto r = PL(i, 0);

    while (n % i == 0) {
      n /= i;
      r.second++;
    }

    res.push_back(r);
  }

  // sqrt(n) 以上の素因数は高々一つ
  if (n != 1) res.emplace_back(n, 1);

  return res;
}

void solve() {
  ll N;
  cin >> N;

  auto fact = factorize(N);

  ll res = 0;

  // N
  {
    VL facts(0);

    for (ll fact = 1; fact * fact <= N; ++fact) {
      unless(N % fact == 0) continue;

      if (fact != 1) facts.push_back(fact);
      if (fact != N / fact) facts.push_back(N / fact);
    }

    for (auto fact : facts) {
      ll num = N;
      while (num % fact == 0) num /= fact;
      if (num % fact == 1) ++res;
    }
  }

  // N-1
  {
    ll M = N - 1;

    for (ll fact = 1; fact * fact <= M; ++fact) {
      unless(M % fact == 0) continue;

      if (fact != 1) ++res;
      if (fact != M / fact) ++res;
    }
  }

  cout << res << "\n";
}

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
