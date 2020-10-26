// https://atcoder.jp/contests/abc180/tasks/abc180_f

#include <atcoder/all>

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
using namespace atcoder;
using ll = long long;
using ld = long double;
template <typename T>
using V = vector<T>;
using VL = V<ll>;
template <typename T>
using VV = V<V<T>>;
using VVL = VV<ll>;
template <typename T>
using VVV = VV<V<T>>;
template <typename T, typename U>
using P = pair<T, U>;
using PL = P<ll, ll>;
using VPL = V<PL>;
template <typename T>
using asc_pq = priority_queue<T, V<T>, greater<T>>;

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

// 重複組合せ n 種類から k 個重複を許して取る通り
mint h_m(ll n, ll k) { return c_m((n - 1) + k, k); }

mint p_m(ll n, ll k) { return c_m(n, k) * ct.fact[k]; }

void solve() {
  ll N, M, L;
  cin >> N >> M >> L;

  prepare_combination(max(N, M));

  auto partial = [&](ll n, ll m, ll l) -> mint {
    V<mint> path_ct(l + 1);  // path_ct[i]: サイズ i のパスの個数

    path_ct[1] = 1;
    path_ct[2] = 1;

    repf(i, 3, l + 1) path_ct[i] = path_ct[i - 1] * i;

    V<mint> cycle_ct(l + 1);  // cycle_ct[i]: サイズ i のサイクルの個数
    repf(i, 2, l + 1) cycle_ct[i] = path_ct[i - 1];

    // dp[i][j] 頂点 i 個、辺 j 個使ったときの求める個数
    VV<mint> dp(N + 1, V<mint>(M + 1));
    dp[0][0] = 1;

    rep(i, n + 1) rep(j, m + 1) {
      // dp[i][j] の状態から、新たにサイズ 1 ~ l
      // のパス・サイクルを付け加えることを考える
      // 重複を防ぐため、まだ足していない頂点の番号の最も小さいものを必ず含めることとする
      // こうすると、ある一つの連結成分の組み合わせに対して、それを構成する方法がただ一つに定まり重複しないことがわかる

      rep1(k, l) {
        ll ni = i + k;
        ll nj = j + k - 1;
        if (ni > n) break;
        if (nj > m) break;
        dp[ni][nj] += dp[i][j] * c_m(n - i - 1, k - 1) * path_ct[k];
      }

      rep1(k, l) {
        if (k == 1) continue;
        ll ni = i + k;
        ll nj = j + k;
        if (ni > n) break;
        if (nj > m) break;
        dp[ni][nj] += dp[i][j] * c_m(n - i - 1, k - 1) * cycle_ct[k];
      }
    }

    return dp[n][m];
  };

  mint res = partial(N, M, L) - partial(N, M, L - 1);

  cout << res << "\n";
}
