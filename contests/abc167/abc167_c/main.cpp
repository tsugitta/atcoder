// https://atcoder.jp/contests/abc167/tasks/abc167_c

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
  ll N, M, X;
  cin >> N >> M >> X;

  struct Book {
    ll cost;
    VL as;
  };

  V<Book> bs(N);

  rep(i, N) {
    cin >> bs[i].cost;
    bs[i].as.resize(M);
    rep(j, M) cin >> bs[i].as[j];
  }

  ll res = INF;

  rep(bit, 1 << N) {
    ll sum_cost = 0;
    VL got_as(M);

    rep(i, N) {
      unless(bit & (1 << i)) continue;

      sum_cost += bs[i].cost;
      rep(j, M) got_as[j] += bs[i].as[j];
    }

    if (all_of(all(got_as), [&](ll v) { return v >= X; })) {
      chmin(res, sum_cost);
    }
  }

  if (res == INF) drop(-1);

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

void solve2() {
  ll N, M, X;
  cin >> N >> M >> X;

  struct Book {
    ll cost;
    VL as;
  };

  V<Book> bs(N);

  rep(i, N) {
    cin >> bs[i].cost;
    bs[i].as.resize(M);
    rep(j, M) cin >> bs[i].as[j];
  }

  ll res = INF;

  auto check = [&](V<bool> uses) {
    ll sum_cost = 0;
    VL got_as(M);

    rep(i, N) {
      unless(uses[i]) continue;
      sum_cost += bs[i].cost;
      rep(j, M) got_as[j] += bs[i].as[j];
    }

    if (all_of(all(got_as), [&](ll v) { return v >= X; })) {
      chmin(res, sum_cost);
    }
  };

  auto dfs = makeFixPoint([&](auto f, V<bool> uses) -> void {
    if (len(uses) == N) {
      check(uses);
      return;
    }

    for (auto v : {true, false}) {
      uses.push_back(v);
      f(uses);
      uses.pop_back();
    }
  });

  V<bool> uses;
  dfs(uses);

  if (res == INF) drop(-1);

  cout << res << "\n";
}
