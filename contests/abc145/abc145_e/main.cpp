// https://atcoder.jp/contests/abc145/tasks/abc145_e

#include "algorithm"
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
  ll N, T;
  cin >> N >> T;
  VPL fs(N);

  rep(i, N) {
    ll a, b;
    cin >> a >> b;
    fs[i] = {a, b};
  }

  sort(all(fs));

  ll MAX = 6000;
  // dp[i][j] i (>=1) 番目の料理までだけを考えた時の、注文後 j
  // 分以下となる美味しさの最大値.
  VVL dp(N + 1, VL(MAX + 1));

  repf(i, 1, N + 1) {
    PL f = fs[i - 1];
    ll time = f.first;
    ll del = f.second;

    rep(j, MAX + 1) {
      chmax(dp[i][j], dp[i - 1][j]);

      if (time <= j && j - time < T) {
        chmax(dp[i][j], dp[i - 1][j - time] + del);
      }
    }
  }

  ll res = 0;
  rep(i, MAX + 1) { chmax(res, dp[N][i]); }

  cout << res << endl;
}

void solve2() {
  ll N, T;
  cin >> N >> T;
  VPL fs(N);

  rep(i, N) {
    ll a, b;
    cin >> a >> b;
    fs[i] = {a, b};
  }

  sort(all(fs));

  // dp[i][j] i (>=1) 番目の料理までだけを考えた時の、注文・食事後 j
  // 分以下となる美味しさの最大値
  VVL dp(N + 1, VL(T + 1));

  repf(i, 1, N + 1) {
    PL f = fs[i - 1];
    ll time = f.first;
    ll del = f.second;

    rep(j, T + 1) {
      chmax(dp[i][j], dp[i - 1][j]);

      if (time <= j) chmax(dp[i][j], dp[i - 1][j - time] + del);
    }
  }

  ll res = 0;

  // i 番目まで食べるケースの最大値。かかる時間でソートしているため i
  // 番目は最後に食べるとして良い
  rep(i, N - 1) { chmax(res, dp[i + 1][T - 1] + fs[i + 1].second); }

  cout << res << endl;
}

void solve3() {
  ll N, T;
  cin >> N >> T;
  VPL fs(N);

  rep(i, N) {
    ll a, b;
    cin >> a >> b;
    fs[i] = {a, b};
  }

  // dp[i][j]: fs[i-1] までだけを考えた時の、注文・食事後 j
  // 分以下となる美味しさの最大値
  VVL dp(N + 1, VL(T + 1));

  repf(i, 1, N + 1) {
    PL f = fs[i - 1];
    ll time = f.first;
    ll del = f.second;

    rep(j, T + 1) {
      chmax(dp[i][j], dp[i - 1][j]);

      if (time <= j) chmax(dp[i][j], dp[i - 1][j - time] + del);
    }
  }

  // dp2[i][j] 後ろから fs[N-i] までの料理だけを考えた時の、注文・食事後 j
  // 分以下となる美味しさの最大値.
  VVL dp2(N + 1, VL(T + 1));

  repf(i, 1, N + 1) {
    PL f = fs[N - i];
    ll time = f.first;
    ll del = f.second;

    rep(j, T + 1) {
      chmax(dp2[i][j], dp2[i - 1][j]);

      if (time <= j) chmax(dp2[i][j], dp2[i - 1][j - time] + del);
    }
  }

  ll res = 0;

  // i 番目を最後に食べる場合の最大値。それ以外の部分を T-1
  // 以下で食べられれば良い
  repf(i, 0, N) {
    rep(t, T - 1) {
      chmax(res, dp[i][t] + fs[i].second + dp2[N - i - 1][T - 1 - t]);
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
