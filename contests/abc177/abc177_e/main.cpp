// https://atcoder.jp/contests/abc177/tasks/abc177_e

#include "algorithm"
#include "bitset"
#include "cmath"
#include "functional"
#include "iomanip"
#include "iostream"
#include "map"
#include "numeric"
#include "queue"
#include "string"
#include "unordered_set"
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
void solve2();
void solve3();

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

string PC = "pairwise coprime";
string SC = "setwise coprime";
string NC = "not coprime";

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

  V<int> as(N);
  rep(i, N) cin >> as[i];

  auto is_pc = [&]() {
    unordered_set<int> facts;

    for (int a : as) {
      VPL fact = factorize(a);

      for (PL pa : fact) {
        auto [fact, _] = pa;

        if (facts.count(fact)) {
          return false;
        }

        facts.insert(fact);
      }
    }

    return true;
  };

  if (is_pc()) drop(PC);

  ll gcd_v = 0;
  rep(i, N) { gcd_v = gcd(gcd_v, as[i]); }

  if (gcd_v == 1) drop(SC);

  drop(NC);
}

void solve2() {
  ll N;
  cin >> N;

  V<int> as(N);
  rep(i, N) cin >> as[i];

  auto is_pc = [&]() {
    int a_max = *max_element(all(as));
    VL cs(a_max + 1);

    rep(i, N) cs[as[i]]++;

    repf(fact, 2, a_max + 1) {
      ll ct = 0;

      for (int num = fact; num <= a_max; num += fact) {
        ct += cs[num];
      }

      if (ct > 1) return false;
    }

    return true;
  };

  if (is_pc()) drop(PC);

  ll gcd_v = 0;
  rep(i, N) { gcd_v = gcd(gcd_v, as[i]); }

  if (gcd_v == 1) drop(SC);

  drop(NC);
}

void solve3() {
  ll N;
  cin >> N;

  V<int> as(N);
  rep(i, N) cin >> as[i];

  int a_max = *max_element(all(as));
  VL min_factor(a_max + 1);

  repf(fact, 2, a_max + 1) {
    if (min_factor[fact] > 0) continue;

    for (int num = fact; num <= a_max; num += fact) {
      if (min_factor[num] == 0) min_factor[num] = fact;
    }
  }

  auto is_pc = [&]() {
    unordered_set<int> facts;

    for (int a : as) {
      while (a > 1) {
        if (min_factor[a] == 0) {
          if (facts.count(a)) return false;
          facts.insert(a);
          break;
        }

        int f = min_factor[a];
        if (facts.count(f)) return false;
        facts.insert(f);
        while (a % f == 0) a /= f;
      }
    }

    return true;
  };

  if (is_pc()) drop(PC);

  ll gcd_v = 0;
  rep(i, N) { gcd_v = gcd(gcd_v, as[i]); }

  if (gcd_v == 1) drop(SC);

  drop(NC);
}
