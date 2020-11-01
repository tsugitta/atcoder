// https://atcoder.jp/contests/abc181/tasks/abc181_d

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

void solve() {
  string S;
  cin >> S;

  if (S.size() <= 3) {
    sort(all(S));

    do {
      int num = stoi(S);
      if (num % 8 == 0) drop("Yes");
    } while (next_permutation(all(S)));

    drop("No");
  }

  V<int> cts(10);

  for (char c : S) cts[c - '0']++;

  repf(num, 100, 1000) {
    unless(num % 8 == 0) continue;

    string st = to_string(num);

    if (any_of(all(st), [](char c) { return c == '0'; })) {
      continue;
    }

    auto cp_cts = cts;

    for (auto c : st) cp_cts[c - '0']--;

    auto is_ok = [&]() {
      rep1(digit, 9) {
        if (cp_cts[digit] < 0) {
          return false;
        }
      }

      return true;
    };

    if (is_ok()) drop("Yes");
  }

  cout << "No"
       << "\n";
}
