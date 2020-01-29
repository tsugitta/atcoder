// https://atcoder.jp/contests/abc027/tasks/abc027_b

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
  ll N;
  cin >> N;

  VL as(N);
  rep(i, N) cin >> as[i];

  ll sum = accumulate(all(as), 0ll);

  unless(sum % N == 0) drop(-1);

  ll target = sum / N;

  ll res = 0;
  ll cur_sum = 0;
  ll prev_unsatisfied_ct = 0;

  rep(i, N) {
    if (prev_unsatisfied_ct > 0) {
      res++;

      if (cur_sum + as[i] == target * (prev_unsatisfied_ct + 1)) {
        prev_unsatisfied_ct = 0;
        cur_sum = 0;
      } else {
        prev_unsatisfied_ct++;
        cur_sum += as[i];
      }

      continue;
    }

    if (as[i] != target) {
      cur_sum += as[i];
      prev_unsatisfied_ct++;
    }
  }

  cout << res << endl;
}

void solve2() {
  ll N;
  cin >> N;

  VL as(N);
  rep(i, N) cin >> as[i];

  ll sum = accumulate(all(as), 0ll);

  unless(sum % N == 0) drop(-1);

  ll target = sum / N;

  ll res = 0;

  ll i = 0;

  while (i < N) {
    ll sum = 0;

    ll j = i;

    while (true) {
      sum += as[j];

      if (sum == (j - i + 1) * target) {
        break;
      }

      j++;
    }

    res += j - i;
    i = j + 1;
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
