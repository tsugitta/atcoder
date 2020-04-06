// https://atcoder.jp/contests/abc161/tasks/abc161_d

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
  ll K;
  cin >> K;

  queue<ll> q;
  rep1(num, 9) q.push(num);

  rep(i, K - 1) {
    ll n = q.front();
    q.pop();

    if (n % 10 >= 1) q.push(10 * n + (n % 10 - 1));
    q.push(10 * n + (n % 10));
    if (n % 10 <= 8) q.push(10 * n + (n % 10 + 1));
  }

  ll res = q.front();

  cout << res << "\n";
}

// priority_queue なら順番を気にせずに済む
// ただし、自身から生成されるのは自身より大きい値だけであることに依存している
void solve2() {
  ll K;
  cin >> K;

  priority_queue<ll, V<ll>, greater<ll>> q;
  rep1(num, 9) q.push(num);

  rep(i, K - 1) {
    ll n = q.top();
    q.pop();

    q.push(10 * n + (n % 10));

    if (n % 10 >= 1) q.push(10 * n + (n % 10 - 1));
    if (n % 10 <= 8) q.push(10 * n + (n % 10 + 1));
  }

  ll res = q.top();

  cout << res << "\n";
}

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

void solve3() {
  ll K;
  cin >> K;

  ll MAX_DIGIT = 10;

  VL res(0);

  auto dfs = makeFixPoint([&](auto f, ll num) -> void {
    res.push_back(num);
    if (to_string(num).size() >= MAX_DIGIT) return;

    for (ll i = -1; i <= 1; ++i) {
      ll last = (num % 10) + i;
      unless(0 <= last && last <= 9) continue;
      f(10 * num + last);
    }
  });

  rep1(num, 9) dfs(num);

  sort(all(res));

  cout << res[K - 1] << "\n";
}

void solve4() {
  ll K;
  cin >> K;

  ll MAX_DIGIT = 10;

  VVL dp(10, VL(MAX_DIGIT + 1));

  rep(num, 10) dp[num][1] = 1;

  repf(digit, 2, MAX_DIGIT + 1) rep(num, 10) {
    for (auto diff : {-1, 0, 1}) {
      unless(0 <= num + diff && num + diff <= 9) continue;
      dp[num][digit] += dp[num + diff][digit - 1];
    }
  }

  ll res_digit = 0;
  ll ct_less_digit = 0;

  {
    ll ct = 0;

    rep1(d, MAX_DIGIT) {
      ll d_ct = 0;

      rep1(num, 9) d_ct += dp[num][d];

      if (ct + d_ct >= K) {
        res_digit = d;
        break;
      } else {
        ct += d_ct;
      }
    }

    ct_less_digit = ct;
  }

  VL res(res_digit, -1);

  {
    ll target_on_digit = K - ct_less_digit;
    ll ct = 0;

    rep1(num, 9) {
      if (ct + dp[num][res_digit] < target_on_digit) {
        ct += dp[num][res_digit];
      } else {
        res[0] = num;
        break;
      }
    }

    rep(i, res_digit) {
      if (i == 0) continue;

      for (auto diff : {-1, 0, 1}) {
        ll val = res[i - 1] + diff;
        unless(0 <= val && val <= 9) continue;

        if (ct + dp[val][res_digit - i] < target_on_digit) {
          ct += dp[val][res_digit - i];
        } else {
          res[i] = val;
          break;
        }
      }
    }
  }

  for (auto v : res) cout << v;
  cout << "\n";
}

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
