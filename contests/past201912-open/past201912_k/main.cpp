// https://atcoder.jp/contests/past201912-open/tasks/past201912_k

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

  ll root = -1;

  VVL edge_list(N);

  rep(i, N) {
    ll p;
    cin >> p;

    if (p == -1) {
      root = i;
      continue;
    }

    --p;

    edge_list[i].emplace_back(p);
    edge_list[p].emplace_back(i);
  }

  VL ls(N, -1);  // オイラーツアー時の最初に現れる index
  VL rs(N, -1);  // 最後に現れる index

  // [ls[u], rs[u]) に v が含まれていれば v は u の部分木

  auto dfs = makeFixPoint([&](auto f, ll u, ll p, ll& i) -> void {
    ls[u] = i++;

    for (auto v : edge_list[u]) {
      if (v == p) continue;
      f(v, u, i);
    }

    rs[u] = i;
  });
  {
    ll i = 0;
    dfs(root, -1, i);
  }

  ll Q;
  cin >> Q;

  rep(i, Q) {
    ll a, b;
    cin >> a >> b;
    --a, --b;

    bool ok = ls[b] < ls[a] && ls[a] < rs[b];
    string res = ok ? "Yes" : "No";

    cout << res << "\n";
  }
}

struct LCA {
  VVL parent;  // parent[d][v] := 2^d-th parent of v
  VL depth;

  LCA() {}
  LCA(const VVL& edge_list, ll r = 0) { init(edge_list, r); }

  void init(const VVL& edge_list, ll r = 0) {
    ll V = edge_list.size();
    ll h = 1;
    while ((1 << h) < V) ++h;
    parent.assign(h, VL(V, -1));
    depth.assign(V, -1);
    dfs(edge_list, r, -1, 0);
    for (ll i = 0; i + 1 < (ll)parent.size(); ++i)
      for (ll v = 0; v < V; ++v)
        if (parent[i][v] != -1) parent[i + 1][v] = parent[i][parent[i][v]];
  }

  void dfs(const VVL& edge_list, ll v, ll p, ll d) {
    parent[0][v] = p;
    depth[v] = d;
    for (auto e : edge_list[v])
      if (e != p) dfs(edge_list, e, v, d + 1);
  }

  ll get(ll u, ll v) {
    if (depth[u] > depth[v]) swap(u, v);
    for (ll i = 0; i < (ll)parent.size(); ++i)
      if ((depth[v] - depth[u]) & (1 << i)) v = parent[i][v];
    if (u == v) return u;
    for (ll i = (ll)parent.size() - 1; i >= 0; --i) {
      if (parent[i][u] != parent[i][v]) {
        u = parent[i][u];
        v = parent[i][v];
      }
    }
    return parent[0][u];
  }
};

void solve2() {
  ll N;
  cin >> N;

  ll root = -1;

  VVL edge_list(N);

  rep(i, N) {
    ll p;
    cin >> p;

    if (p == -1) {
      root = i;
      continue;
    }

    --p;

    edge_list[i].emplace_back(p);
    edge_list[p].emplace_back(i);
  }

  auto lca = LCA(edge_list, root);

  ll Q;
  cin >> Q;

  rep(i, Q) {
    ll a, b;
    cin >> a >> b;
    --a, --b;

    string res = lca.get(a, b) == b ? "Yes" : "No";

    cout << res << "\n";
  }
}
