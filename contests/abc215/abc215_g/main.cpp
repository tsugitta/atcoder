// https://atcoder.jp/contests/abc215/tasks/abc215_g

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
#define rep(i, to) for (ll i = 0; i < ((ll)to); ++i)
#define rep1(i, to) for (ll i = 1; i <= ((ll)to); ++i)
#define repf(i, from, to) for (ll i = from; i < ((ll)to); ++i)
#define repr(i, from) for (ll i = from - 1; i >= 0; --i)
#define all(vec) vec.begin(), vec.end()
#define unless(cond) if (!(cond))
#define fi first
#define se second
#define i128 __int128_t
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

const ll MOD = 998244353;
// const ll MOD = 1000000007;
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
  ll N;
  cin >> N;

  prepare_combination(N);

  VPL ct_kind_cts;  // [個数, その個数の色の種類数]

  {
    map<ll, ll> color_to_ct;

    rep(i, N) {
      ll c;
      cin >> c;

      color_to_ct[c]++;
    }

    map<ll, ll> ct_to_colors_kind_ct;

    for (auto [_, ct] : color_to_ct) {
      ct_to_colors_kind_ct[ct]++;
    }

    for (auto [ct, kind_ct] : ct_to_colors_kind_ct) {
      ct_kind_cts.emplace_back(ct, kind_ct);
    }
  }

  rep1(k, N) {
    mint res = 0;

    for (auto [ct, kind_ct] : ct_kind_cts) {
      res += (c_m(N, k) - c_m(N - ct, k)) * kind_ct;
    }

    // これを L239 で行ってしまうと TLE
    res /= c_m(N, k);

    cout << res << "\n";
  }
}
