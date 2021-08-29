// https://atcoder.jp/contests/abc216/tasks/abc216_d

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
#define rep(i, to) for (ll i = 0; i < ((ll)to); ++i)
#define rep1(i, to) for (ll i = 1; i <= ((ll)to); ++i)
#define repf(i, from, to) for (ll i = from; i < ((ll)to); ++i)
#define repr(i, from) for (ll i = from - 1; i >= 0; --i)
#define all(vec) vec.begin(), vec.end()
#define unless(cond) if (!(cond))
#define fi first
#define se second
#define i128 __int128_t
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
  ll N, M;
  cin >> N >> M;

  V<deque<ll>> bs(M);

  VVL color_to_pos(N);

  rep(i, M) {
    ll k;
    cin >> k;

    while (k--) {
      ll a;
      cin >> a;
      --a;
      bs[i].push_back(a);
      color_to_pos[a].push_back(i);
    }
  }

  VL cts(N);

  auto check = [&](auto check, ll pos) -> void {
    if (bs[pos].empty()) return;

    ll c = bs[pos].front();

    if (cts[c] != 2) return;

    cts[c] = 0;

    for (ll np : color_to_pos[c]) {
      bs[np].pop_front();

      if (bs[np].empty()) continue;
      ll nc = bs[np].front();
      cts[nc]++;
    }

    for (ll np : color_to_pos[c]) {
      check(check, np);
    }
  };

  rep(i, M) {
    ll c = bs[i].front();
    cts[c]++;
  }

  rep(i, M) check(check, i);

  rep(i, N) if (cts[i]) drop("No");

  cout << "Yes"
       << "\n";
}
