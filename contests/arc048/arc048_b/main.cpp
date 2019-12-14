// https://atcoder.jp/contests/arc048/tasks/arc048_b

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

  struct Player {
    ll r;
    ll h;
  };

  V<Player> ps(N);
  map<ll, VL> hand_cts;  // hand_cts[rate][hand]: その rate & hand の数
  VL acc_rates(1e5 + 1);

  rep(i, N) {
    ll r, h;
    cin >> r >> h;
    h--;
    ps[i] = {r, h};

    if (hand_cts[r].size() == 0) hand_cts[r] = VL(3);
    hand_cts[r][h]++;

    acc_rates[r]++;
  }

  rep(i, 1e5) { acc_rates[i + 1] += acc_rates[i]; }

  rep(i, N) {
    auto p = ps[i];

    ll same_h_win = hand_cts[p.r][(p.h + 1) % 3];
    ll same_h_lose = hand_cts[p.r][(p.h + 2) % 3];
    ll same_h_same = hand_cts[p.r][p.h] - 1;

    ll win = acc_rates[p.r - 1] + same_h_win;
    ll lose = N - acc_rates[p.r] + same_h_lose;
    ll same = same_h_same;

    print_ints({win, lose, same});
  }
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
