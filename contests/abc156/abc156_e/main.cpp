// https://atcoder.jp/contests/abc156/tasks/abc156_e

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

// 重複組合せ n 種類から k 個重複を許して取る通り
mint h_m(ll n, ll k) { return c_m((n - 1) + k, k); }

mint p_m(ll n, ll k, combination_table& ct) { return c_m(n, k) * ct.fact[k]; }

void solve() {
  ll N, K;
  cin >> N >> K;

  mint res = 0;
  prepare_combination(2 * N);

  if (K >= N) {
    mint res = h_m(N, N);
    drop(res);
  }

  // 制約上は無い
  if (K == 1) {
    ll res = N * (N - 1);
    drop(res);
  }

  ll max_v = min(N - 1, K);

  rep(zero_ct, max_v + 1) {
    ll non_zero_ct = N - zero_ct;
    // ゼロでないものを選ぶ
    // それらに 1 ずつ配ると残りは N-non_ezro_ct
    // それを重複を許してそれらに配る
    res += c_m(N, non_zero_ct) * h_m(non_zero_ct, N - non_zero_ct);
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
