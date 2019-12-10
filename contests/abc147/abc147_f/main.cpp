// https://atcoder.jp/contests/abc147/tasks/abc147_f

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
  ll N, X, D;
  cin >> N >> X >> D;

  // S - T = S - (sum - S) = 2S - sum
  // S の通りを求めれば十分。

  if (D == 0) {
    if (X == 0)
      drop(1);
    else
      drop(N + 1);
  }

  if (D < 0) {
    D *= -1;
    X *= -1;
  }

  auto quot = [](ll a, ll divisor) {
    if (a >= 0) return a / divisor;

    return (a - (divisor - 1)) / divisor;
  };

  auto rem = [](ll a, ll divisor) {
    if (a >= 0) return a % divisor;

    a += divisor * ((abs(a) + divisor - 1) / divisor);
    return a % divisor;
  };

  map<ll, VPL> m;

  // N 個中 i 個取る
  rep(i, N + 1) {
    // iX + D*(\sum 0..i-1 ~ \sum (N-i)..(N-1)) を取りうる
    // overflow するので quot をそのまま求める
    // ll left = i * X + D * i * (i - 1) / 2;
    // ll right = i * X + D * i * (2 * N - i - 1) / 2;
    ll left_q = quot(i * X, D) + i * (i - 1) / 2;
    ll right_q = quot(i * X, D) + i * (2 * N - i - 1) / 2;
    ll r = rem(i * X, D);

    m[r].push_back({left_q, right_q + 1});
  }

  ll res = 0;

  for (auto& val : m) {
    auto ranges = val.second;

    VPL events;

    for (auto range : ranges) {
      events.emplace_back(range.first, 1);
      events.emplace_back(range.second, -1);
    }

    sort(all(events));

    ll cur = 0;
    ll prev_open = INF;

    for (auto e : events) {
      if (e.se == 1 && cur == 0) {
        prev_open = e.fi;
      }

      cur += e.se;

      if (cur == 0) {
        res += e.fi - prev_open;
        prev_open = INF;
      }
    }
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
