// https://atcoder.jp/contests/abc167/tasks/abc167_d

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

void solve() {
  ll N, K;
  cin >> N >> K;

  VL as(N);
  rep(i, N) cin >> as[i];
  rep(i, N) as[i]--;

  ll loop_i = -1;
  ll loop_length = -1;

  {
    VL visited_step(N, -1);
    ll cur = 0;

    rep(step, N + 1) {
      if (visited_step[cur] == -1) {
        visited_step[cur] = step;
        cur = as[cur];
        continue;
      }

      loop_i = cur;
      loop_length = step - visited_step[cur];
      break;
    }
  }

  ll cur = 0;
  ll rest = K;

  while (rest > 0) {
    if (cur != loop_i) {
      cur = as[cur];
      --rest;
      continue;
    }

    rest %= loop_length;
    if (rest == 0) break;

    cur = as[cur];
    --rest;

    continue;
  }

  cout << cur + 1 << "\n";
}

void solve2() {
  ll N, K;
  cin >> N >> K;

  VL as(N);
  rep(i, N) cin >> as[i];
  rep(i, N) as[i]--;

  ll cur = 0;

  while (K > 0) {
    if (K & 1) cur = as[cur];

    VL nas(N);
    rep(i, N) nas[i] = as[as[i]];
    swap(as, nas);

    K >>= 1;
  }

  cout << cur + 1 << "\n";
}
