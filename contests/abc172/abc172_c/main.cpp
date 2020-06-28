// https://atcoder.jp/contests/abc172/tasks/abc172_c

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
  ll N, M, K;
  cin >> N >> M >> K;

  VL as(N);
  rep(i, N) cin >> as[i];

  VL bs(M);
  rep(i, M) cin >> bs[i];

  ll b_ct = M;
  ll sum = accumulate(all(bs), 0ll);

  ll res = 0;

  rep(a_ct, N + 1) {
    if (a_ct > 0) sum += as[a_ct - 1];

    while (b_ct > 0 && sum > K) {
      b_ct--;
      sum -= bs[b_ct];
    }

    if (sum > K) break;

    chmax(res, a_ct + b_ct);
  }

  cout << res << "\n";
}

void solve2() {
  ll N, M, K;
  cin >> N >> M >> K;

  VL as(N);
  rep(i, N) cin >> as[i];

  VL bs(M);
  rep(i, M) cin >> bs[i];

  VL b_acc(M + 1);
  rep(i, M) b_acc[i + 1] = b_acc[i] + bs[i];

  ll res = 0;
  ll a_sum = 0;

  rep(a_ct, N + 1) {
    if (a_ct > 0) a_sum += as[a_ct - 1];

    if (a_sum > K) break;

    ll b_max = K - a_sum;

    auto over_b_it = upper_bound(all(b_acc), b_max);
    ll b_ct = over_b_it - b_acc.begin() - 1;

    chmax(res, a_ct + b_ct);
  }

  cout << res << "\n";
}
