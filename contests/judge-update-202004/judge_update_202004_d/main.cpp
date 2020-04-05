// https://atcoder.jp/contests/judge-update-202004/tasks/judge_update_202004_d

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

void solve() {
  ll N, Q;
  cin >> N >> Q;

  VL as(N);
  rep(i, N) cin >> as[i];

  VL gs(N + 1);
  rep(i, N) gs[i + 1] = gcd(gs[i], as[i]);

  rep(i, Q) {
    ll s;
    cin >> s;

    if (gcd(s, gs[N]) != 1) {
      cout << gcd(s, gs[N]) << "\n";
      continue;
    }

    ll ng = 0;
    ll ok = N;

    while (ok - ng > 1) {
      ll mid = (ok + ng) / 2;

      if (gcd(s, gs[mid]) == 1) {
        ok = mid;
      } else {
        ng = mid;
      }
    }

    cout << ok << "\n";
  }
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
