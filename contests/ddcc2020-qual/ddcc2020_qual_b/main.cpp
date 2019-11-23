// https://atcoder.jp/contests/ddcc2020-qual/tasks/ddcc2020_qual_b

#include "algorithm"
#include "cmath"
#include "functional"
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

void solve() {
  ll N;
  cin >> N;
  VL as(N);

  rep(i, N) cin >> as[i];

  ll sum = 0;
  for (auto a : as) sum += a;

  ll ov = -1;

  ll cur = 0;

  rep(i, N) {
    cur += as[i];
    if (sum % 2 == 0 && cur == sum / 2) drop(0);
    if (cur > sum / 2) {
      ov = i;
      break;
    }
  }

  ll leftEdge = cur - as[ov];
  ll rightEdge = sum - cur;
  ll res = min(sum - 2 * leftEdge, sum - 2 * rightEdge);

  cout << res << endl;
}

void solve2() {
  ll N;
  cin >> N;
  VL as(N);

  rep(i, N) cin >> as[i];

  VL sums(N);
  rep(i, N) {
    if (i > 0) sums[i] += sums[i - 1];
    sums[i] += as[i];
  }

  ll res = INF;
  rep(i, N - 1) {
    ll left = sums[i];
    ll right = sums[N - 1] - left;

    chmin(res, abs(left - right));
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
