// https://atcoder.jp/contests/agc041/tasks/agc041_b

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
  ll N, M, V, P;
  cin >> N >> M >> V >> P;

  VL as(N);
  rep(i, N) cin >> as[i];

  sort(all(as));

  auto is_ok = [&](ll index) -> bool {
    ll a = as[index];
    ll rest = M * V;

    auto over_it = upper_bound(all(as), a + M);
    ll over_a_ct = as.end() - over_it;
    if (over_a_ct >= P) return false;

    rest -= (P - 1) * M;
    if (rest <= 0) return true;

    ll smaller_a_ct = upper_bound(all(as), a) - as.begin();
    rest -= smaller_a_ct * M;
    if (rest <= 0) return true;

    ll b_i = upper_bound(all(as), a) - as.begin();
    repf(i, b_i, N - (P - 1)) { rest -= a + M - as[i]; }

    return rest <= 0;
  };

  if (is_ok(0)) drop(N);

  ll ng = 0;
  ll ok = N - 1;

  while (ok - ng > 1) {
    ll mid = (ng + ok) / 2;
    if (is_ok(mid)) {
      ok = mid;
    } else {
      ng = mid;
    }
  }

  ll res = N - ok;
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
