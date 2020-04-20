// https://atcoder.jp/contests/abc163/tasks/abc163_e

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
#include "unordered_map"
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
void solve3();
void solve4();

#ifndef TEST
int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  try {
    solve4();
  } catch (exit_exception& e) {
  }

  return 0;
}
#endif

template <typename F>
class
#if defined(__has_cpp_attribute) && __has_cpp_attribute(nodiscard)
    [[nodiscard]]
#elif defined(__GNUC__) && \
    (__GNUC__ > 3 || __GNUC__ == 3 && __GNUC_MINOR__ >= 4)
    __attribute__((warn_unused_result))
#endif
    FixPoint : private F {
 public:
  explicit constexpr FixPoint(F && f) noexcept : F(std::forward<F>(f)) {}

  template <typename... Args>
  constexpr decltype(auto) operator()(Args&&... args) const
#if !defined(__GNUC__) || defined(__clang__) || __GNUC__ >= 9
      noexcept(noexcept(
          F::operator()(std::declval<FixPoint>(), std::declval<Args>()...)))
#endif
  {
    return F::operator()(*this, std::forward<Args>(args)...);
  }
};

template <typename F>
static inline constexpr decltype(auto) makeFixPoint(F&& f) noexcept {
  return FixPoint<F>{std::forward<F>(f)};
}

void solve() {
  ll N;
  cin >> N;

  struct Val {
    ll i, a;
  };

  V<Val> as(N);
  rep(i, N) {
    ll a;
    cin >> a;

    as[i] = {i, a};
  }

  sort(all(as), [](Val a, Val b) { return a.a > b.a; });

  VVL memo(N + 1, VL(N + 1));

  auto dfs = makeFixPoint([&](auto f, ll i, ll next_left) -> ll {
    if (i == N) return 0;
    ll next_right = N - 1 - i + next_left;

    if (memo[i][next_left]) {
      return memo[i][next_left];
    }

    Val val = as[i];

    ll left_dis = abs(val.i - next_left);
    ll right_dis = abs(val.i - next_right);

    ll res = 0;

    chmax(res, val.a * right_dis + f(i + 1, next_left));
    chmax(res, val.a * left_dis + f(i + 1, next_left + 1));

    memo[i][next_left] = res;

    return res;
  });

  ll res = dfs(0, 0);

  cout << res << "\n";
}

struct hash_pair {
  template <class T1, class T2>
  size_t operator()(const pair<T1, T2>& p) const {
    return p.first * 1e5 + p.second;
  }
};

void solve2() {
  ll N;
  cin >> N;

  struct Val {
    ll i, a;
  };

  V<Val> as(N);
  rep(i, N) {
    ll a;
    cin >> a;

    as[i] = {i, a};
  }

  sort(all(as), [](Val a, Val b) { return a.a > b.a; });

  // unordered_map は hash 可能なものしか key にできない
  // → pair はデフォルトでは不可能
  unordered_map<PL, ll, hash_pair> memo;

  auto dfs = makeFixPoint([&](auto f, ll i, ll next_left) -> ll {
    if (i == N) return 0;
    ll next_right = N - 1 - i + next_left;

    if (memo[{i, next_left}]) {
      return memo[{i, next_left}];
    }

    Val val = as[i];

    ll left_dis = abs(val.i - next_left);
    ll right_dis = abs(val.i - next_right);

    ll res = 0;

    chmax(res, val.a * right_dis + f(i + 1, next_left));
    chmax(res, val.a * left_dis + f(i + 1, next_left + 1));

    memo[{i, next_left}] = res;

    return res;
  });

  ll res = dfs(0, 0);

  cout << res << "\n";
}

void solve3() {
  ll N;
  cin >> N;

  struct Val {
    ll i, a;
  };

  V<Val> as(N);
  rep(i, N) {
    ll a;
    cin >> a;

    as[i] = {i, a};
  }

  sort(all(as), [](Val a, Val b) { return a.a > b.a; });

  // dp[i][l]: i 人目まで見た時、左から l 個は埋めている場合の最大値
  VVL dp(N + 1, VL(N + 1));

  rep1(i, N) {
    Val a = as[i - 1];

    // i-1 人目までを考えると左から 0 ~ i-1 個が埋まっている
    rep(l, i) {
      // a を左に置いた場合
      chmax(dp[i][l + 1], dp[i - 1][l] + a.a * abs(a.i - l));

      // 右
      ll r = i - 1 - l;
      chmax(dp[i][l], dp[i - 1][l] + a.a * abs(a.i - (N - 1 - r)));
    }
  }

  ll res = 0;
  rep(i, N + 1) chmax(res, dp[N][i]);

  cout << res << "\n";
}

void solve4() {
  ll N;
  cin >> N;

  struct Val {
    ll i, a;
  };

  V<Val> as(N);
  rep(i, N) {
    ll a;
    cin >> a;

    as[i] = {i, a};
  }

  sort(all(as), [](Val a, Val b) { return a.a > b.a; });

  // dp[l][r]: l+r 人目まで見た時、左から l 個、右から r 個
  // 埋まっている場合の最大値
  VVL dp(N + 1, VL(N + 1));

  // 配る DP
  rep(l, N) rep(r, N) {
    unless(l + r <= N - 1) continue;

    Val a = as[l + r];

    // a を左に置いた場合
    chmax(dp[l + 1][r], dp[l][r] + a.a * abs(a.i - l));

    // 右
    chmax(dp[l][r + 1], dp[l][r] + a.a * abs(a.i - (N - 1 - r)));
  }

  ll res = 0;
  rep(i, N + 1) chmax(res, dp[i][N - i]);

  cout << res << "\n";
}
