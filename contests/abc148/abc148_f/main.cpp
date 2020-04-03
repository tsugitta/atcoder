// https://atcoder.jp/contests/abc148/tasks/abc148_f

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

void print_ints(vector<ll> v);
template <typename T>
void drop(T a);

const ll INF = 1e18;

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
  ll N, FI_V, SE_V;
  cin >> N >> FI_V >> SE_V;
  FI_V--, SE_V--;

  if (FI_V == SE_V) drop(0);

  VVL edge_list(N, VL(0));

  rep(i, N - 1) {
    ll a, b;
    cin >> a >> b;
    a--, b--;
    edge_list[a].push_back(b);
    edge_list[b].push_back(a);
  }

  // 1. 先手から後手までのパスを求める

  // 2.
  // 後手から逃げ切れる限界（limit_v）を求め、スタートからその点までの範囲から到達できる全ての点について考える

  // 3. それらに含まれるある端の点について、そこから 1
  // 戻った点で２者は合流するから、後手から全ての点への距離を求めておき、そこから
  // 1 引けば良い

  auto fill_path = makeFixPoint([&](auto f, ll u, ll p, VL& path) -> bool {
    if (p >= 0 && edge_list[u].size() == 1 && u != SE_V) return false;

    path.push_back(u);
    if (u == SE_V) return true;

    bool exist = false;

    for (auto v : edge_list[u]) {
      if (v == p) continue;

      if (f(v, u, path)) {
        exist = true;
        break;
      }
    }

    if (!exist) path.pop_back();

    return exist;
  });

  auto fill_ds =
      makeFixPoint([&](auto f, ll u, ll p, ll cur_d, VL& ds) -> void {
        chmin(ds[u], cur_d);

        for (ll v : edge_list[u]) {
          if (v == p) continue;
          f(v, u, cur_d + 1, ds);
        }
      });

  VL path(0);
  fill_path(FI_V, -1, path);

  ll limit_v = path[path.size() / 2 - 1];
  ll ng_v = path[path.size() / 2];

  VL se_ds(N, INF);
  fill_ds(SE_V, -1, 0, se_ds);

  auto dfs = makeFixPoint([&](auto f, ll u, ll p) -> ll {
    ll res = se_ds[u] - 1;

    for (ll v : edge_list[u]) {
      if (v == ng_v || v == p) continue;

      ll _res = f(v, u);
      chmax(res, _res);
    }

    return res;
  });

  ll res = dfs(limit_v, -1);
  cout << res << endl;
}

void solve2() {
  ll N, FI_V, SE_V;

  cin >> N >> FI_V >> SE_V;
  FI_V--, SE_V--;

  if (FI_V == SE_V) drop(0);

  VVL edge_list(N, VL(0));

  rep(i, N - 1) {
    ll a, b;
    cin >> a >> b;
    a--, b--;
    edge_list[a].push_back(b);
    edge_list[b].push_back(a);
  }

  auto fill_ds =
      makeFixPoint([&](auto f, ll u, ll p, ll cur_d, VL& ds) -> void {
        chmin(ds[u], cur_d);

        for (ll v : edge_list[u]) {
          if (v == p) continue;
          f(v, u, cur_d + 1, ds);
        }
      });

  // 後手から逃げ切れる限界は先手からの距離も求めておけばわざわざ求める必要がなくなる
  VL se_ds(N, INF);
  VL fi_ds(N, INF);
  fill_ds(SE_V, -1, 0, se_ds);
  fill_ds(FI_V, -1, 0, fi_ds);

  ll res = 0;

  rep(i, N) {
    if (fi_ds[i] < se_ds[i]) {
      chmax(res, se_ds[i] - 1);
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
    solve();
  } catch (exit_exception& e) {
  }

  return 0;
}
#endif

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
