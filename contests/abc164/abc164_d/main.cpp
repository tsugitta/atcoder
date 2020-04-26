// https://atcoder.jp/contests/abc164/tasks/abc164_d

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
  string S;
  cin >> S;

  ll N = S.size();
  ll MOD = 2019;
  VL mods(N + 1);

  rep(i, N) mods[i + 1] = (mods[i] * 10 + (S[i] - '0')) % MOD;

  {
    ll ten_mod = 1;
    repr(i, N + 1) {
      mods[i] = (mods[i] * ten_mod) % MOD;
      ten_mod = ten_mod * 10 % MOD;
    }
  }

  ll res = 0;

  map<ll, ll> m;

  rep(i, N + 1) {
    res += m[mods[i]];
    m[mods[i]]++;
  }

  cout << res << "\n";
}

void solve2() {
  string S;
  cin >> S;

  ll N = S.size();
  ll MOD = 2019;

  VL dp(MOD);
  ll res = 0;

  for (auto c : S) {
    ll num = c - '0';
    VL dp2(MOD);

    // 配る DP
    rep(m, MOD) dp2[(10 * m + num) % MOD] += dp[m];

    ++dp2[num];  // 一桁の場合

    res += dp2[0];
    swap(dp, dp2);
  }

  cout << res << "\n";
}
