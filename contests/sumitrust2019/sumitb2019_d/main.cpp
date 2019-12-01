// https://atcoder.jp/contests/sumitrust2019/tasks/sumitb2019_d

#include "algorithm"
#include "cmath"
#include "functional"
#include "iomanip"
#include "iostream"
#include "numeric"
#include "queue"
#include "set"
#include "string"
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
  string S;
  cin >> S;

  V<multiset<ll>> indices(10);

  rep(i, N) {
    auto c = S[i];
    auto cl = c - '0';
    indices[cl].insert(i);
  }

  ll res = 0;
  rep(f, 10) {
    auto fit = indices[f].lower_bound(0);
    auto f_i_i = distance(indices[f].begin(), fit);

    if (f_i_i == indices[f].size()) continue;
    ll f_i = *fit;

    rep(s, 10) {
      auto sit = indices[s].lower_bound(f_i + 1);
      auto s_i_i = distance(indices[s].begin(), sit);

      if (s_i_i == indices[s].size()) continue;
      auto s_i = *sit;

      rep(t, 10) {
        auto tit = indices[t].lower_bound(s_i + 1);
        auto t_i_i = distance(indices[t].begin(), tit);

        if (t_i_i == indices[t].size()) continue;
        auto t_i = *tit;

        res++;
      }
    }
  }

  cout << res << endl;
}

void solve2() {
  ll N;
  string S;
  cin >> N >> S;

  ll res = 0;

  rep(num, 1000) {
    VL cs = {num / 100, (num / 10) % 10, num % 10};
    ll i = 0;

    rep(j, N) {
      if (S[j] == ('0' + cs[i])) i++;
      if (i == 3) break;
    }

    if (i == 3) res++;
  }
  cout << res << endl;
}

void solve3() {
  ll N;
  string S;
  cin >> N >> S;

  // dp[i][j][n] i (>= 1) 桁目まで見て j 桁の数 n を残すことができるか
  // 001 などを扱うために j が必要となる
  V<VVL> dp(N + 1, VVL(4, VL(1000)));
  dp[0][0][0] = 1;

  rep(i, N) rep(j, 4) rep(num, 1000) {
    if (!dp[i][j][num]) continue;

    dp[i + 1][j][num] = 1;
    if (j < 3) dp[i + 1][j + 1][num * 10 + (S[i] - '0')] = 1;
  }

  ll res = 0;
  rep(num, 1000) if (dp[N][3][num]) res++;

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
    solve3();
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
