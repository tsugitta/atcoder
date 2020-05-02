// https://atcoder.jp/contests/abc165/tasks/abc165_f

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

  VL as(N);
  rep(i, N) cin >> as[i];

  VVL edge_list(N, VL(0));

  rep(i, N - 1) {
    ll u, v;
    cin >> u >> v;
    --u, --v;
    edge_list[u].push_back(v);
    edge_list[v].push_back(u);
  }

  VL lis(N, INF);
  VL res(N, 0);

  auto dfs = makeFixPoint([&](auto f, ll u, ll p) -> void {
    auto it = lower_bound(all(lis), as[u]);
    ll i = it - lis.begin();
    ll prev = *it;
    lis[i] = as[u];
    res[u] = lower_bound(all(lis), INF) - lis.begin();

    for (auto v : edge_list[u]) {
      if (v == p) continue;
      f(v, u);
    }

    lis[i] = prev;
  });

  dfs(0, -1);

  rep(i, N) { cout << res[i] << "\n"; }
}
