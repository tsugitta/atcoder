// https://atcoder.jp/contests/abc160/tasks/abc160_f

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
inline bool chmax(T& a, T b);
template <typename T>
inline bool chmin(T& a, T b);
void print_ints(vector<ll> v);
template <typename T>
void drop(T a);

const ll INF = 1e18;

template <int MOD>
class Fp {
 public:
  long long val;
  constexpr Fp(long long v = 0) noexcept : val(v % MOD) {
    if (val < 0) val += MOD;
  }
  constexpr int getmod() { return MOD; }
  constexpr Fp operator-() const noexcept { return val ? MOD - val : 0; }
  constexpr Fp operator+(const Fp& r) const noexcept { return Fp(*this) += r; }
  constexpr Fp operator-(const Fp& r) const noexcept { return Fp(*this) -= r; }
  constexpr Fp operator*(const Fp& r) const noexcept { return Fp(*this) *= r; }
  constexpr Fp operator/(const Fp& r) const noexcept { return Fp(*this) /= r; }
  constexpr Fp& operator+=(const Fp& r) noexcept {
    val += r.val;
    if (val >= MOD) val -= MOD;
    return *this;
  }
  constexpr Fp& operator-=(const Fp& r) noexcept {
    val -= r.val;
    if (val < 0) val += MOD;
    return *this;
  }
  constexpr Fp& operator*=(const Fp& r) noexcept {
    val = val * r.val % MOD;
    return *this;
  }
  constexpr Fp& operator/=(const Fp& r) noexcept {
    long long a = r.val, b = MOD, u = 1, v = 0;
    while (b) {
      long long t = a / b;
      a -= t * b;
      swap(a, b);
      u -= t * v;
      swap(u, v);
    }
    val = val * u % MOD;
    if (val < 0) val += MOD;
    return *this;
  }
  constexpr bool operator==(const Fp& r) const noexcept {
    return this->val == r.val;
  }
  constexpr bool operator!=(const Fp& r) const noexcept {
    return this->val != r.val;
  }
  friend constexpr ostream& operator<<(ostream& os, const Fp<MOD>& x) noexcept {
    return os << x.val;
  }
  friend constexpr Fp<MOD> modpow(const Fp<MOD>& a, long long n) noexcept {
    if (n == 0) return 1;
    auto t = modpow(a, n / 2);
    t = t * t;
    if (n & 1) t = t * a;
    return t;
  }
};

// const ll MOD = 998244353;
const ll MOD = 1000000007;
using mint = Fp<MOD>;

struct combination_table {
  // i! % MOD M
  V<ll> fact;
  // (i!)^(-1) MOD M
  V<ll> finv;
  // i^(-1) MOD M
  V<ll> inv;
};

combination_table ct;

// ref: http://drken1215.hatenablog.com/entry/2018/06/08/210000
void prepare_combination(ll max) {
  V<ll> fact(max + 1);
  V<ll> finv(max + 1);
  V<ll> inv(max + 1);

  fact[0] = 1;
  fact[1] = 1;
  finv[0] = 1;
  finv[1] = 1;
  inv[1] = 1;

  for (ll i = 2; i <= max; i++) {
    fact[i] = fact[i - 1] * i % MOD;
    inv[i] = MOD - inv[MOD % i] * (MOD / i) %
                       MOD;  // a^(-1) ≡ -(p % a)^(-1) * (p/a) MOD p
    finv[i] = finv[i - 1] * inv[i] % MOD;
  }

  ct = {
      fact,
      finv,
      inv,
  };
}

mint c_m(ll n, ll k) {
  if (n < k) return 0;
  if (n < 0 || k < 0) return 0;
  return mint(ct.fact[n]) * ct.finv[k] * ct.finv[n - k];
}

// 部分木のサイズと答えを持つ
struct Val {
  mint res;
  ll size;

  Val(mint res = 1, ll size = 0) : res(res), size(size) {}

  Val operator+(const Val& a) {
    return Val(res * a.res * c_m(size + a.size, a.size), size + a.size);
  }

  Val add_self() {
    Val r(*this);
    ++r.size;
    return r;
  }
};

ll N;
VVL edge_list;
V<V<Val>> dp;
V<Val> dp_sum;

// dp: 根から向いた全辺についての埋まる。
// dp_sum: 根は埋まり、それ以外の点については根方向への辺以外の合計が埋まる。
Val dfs(ll u, ll p = -1) {
  dp[u] = V<Val>(edge_list[u].size());

  rep(i, edge_list[u].size()) {
    ll v = edge_list[u][i];
    if (v == p) continue;

    dp[u][i] = dfs(v, u);
    dp_sum[u] = dp_sum[u] + dp[u][i];
  }

  return dp_sum[u].add_self();
}

// 根以外の点についての dp_sum を埋めるのが目的
// 根から「根方向への Val」を渡して降りていくことで、根方向への dp と dp_sum
// を埋めることができる
void dfs2(ll u, const Val& p_v = Val(), ll p = -1) {
  if (p != -1) dp_sum[u] = dp_sum[u] + p_v;

  ll deg = edge_list[u].size();

  rep(i, deg) if (edge_list[u][i] == p) dp[u][i] = p_v;

  V<Val> left_sum(deg + 1);
  rep(i, deg) left_sum[i + 1] = left_sum[i] + dp[u][i];

  V<Val> right_sum(deg + 1);
  repr(i, deg) right_sum[i] = right_sum[i + 1] + dp[u][i];

  rep(i, deg) {
    ll v = edge_list[u][i];

    if (v == p) {
      dp[u][i] = p_v;
      continue;
    }

    Val d = left_sum[i] + right_sum[i + 1];
    dfs2(v, d.add_self(), u);
  }
}

// 全方位木 DP
void solve() {
  cin >> N;

  edge_list = VVL(N, VL(0));
  dp = V<V<Val>>(N, V<Val>(0));
  dp_sum = V<Val>(N);

  prepare_combination(N);

  rep(i, N - 1) {
    ll a, b;
    cin >> a >> b;
    a--, b--;

    edge_list[a].emplace_back(b);
    edge_list[b].emplace_back(a);
  }

  dfs(0);
  dfs2(0);

  rep(i, N) {
    mint res = dp_sum[i].add_self().res;
    cout << res << "\n";
  }
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
