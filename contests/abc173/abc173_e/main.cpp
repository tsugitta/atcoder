// https://atcoder.jp/contests/abc173/tasks/abc173_e

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
  ll N, K;
  cin >> N >> K;

  VL as(N);
  VL pluses;
  VL minuses;
  rep(i, N) {
    ll a;
    cin >> a;
    as[i] = a;

    if (a > 0) {
      pluses.push_back(a);
    } else if (a < 0) {
      minuses.push_back(a);
    }
  }

  ll plus_ct = pluses.size();
  ll minus_ct = minuses.size();

  mint res = 1;

  // 必ずマイナスになってしまうケース
  if (minus_ct == N && K % 2 == 1) {
    sort(as.rbegin(), as.rend());
    rep(i, K) res *= as[i];
    drop(res);
  }

  // プラスが存在せず、ゼロが存在し、 K が奇数ならゼロが答えとなる
  if (plus_ct == 0 && minus_ct < N && K % 2 == 1) {
    drop(0);
  }

  sort(pluses.rbegin(), pluses.rend());
  sort(all(minuses));

  ll next_plus_i = 0;
  ll next_minus_i = 0;
  ll used_minus_ct = 0;

  const ll MINUS = -1;
  const ll PLUS = 1;

  rep(i, K) {
    ll used = 0;

    bool can_use_plus = next_plus_i < plus_ct;
    bool can_use_minus = next_minus_i < minus_ct;

    if (!can_use_plus && !can_use_minus) drop(0);

    if (can_use_plus && can_use_minus) {
      ll next_plus = pluses[next_plus_i];
      ll next_minus = minuses[next_minus_i];
      used = next_plus > abs(next_minus) ? PLUS : MINUS;
    } else if (can_use_plus) {
      used = PLUS;
    } else if (can_use_minus) {
      used = MINUS;
    }

    ll val = 0;

    if (used == PLUS) {
      val = pluses[next_plus_i];
      next_plus_i++;
    } else if (used == MINUS) {
      val = minuses[next_minus_i];
      next_minus_i++;
      used_minus_ct++;
    }

    res *= val;
  }

  if (used_minus_ct % 2 == 0) {
    drop(res);
  }

  bool can_use_plus = next_plus_i < plus_ct && next_minus_i > 0;
  bool can_use_minus = next_minus_i < minus_ct && next_plus_i > 0;

  if (!can_use_plus && !can_use_minus) {
    drop(res);
  }

  if (can_use_plus && !can_use_minus) {
    ll removed = minuses[next_minus_i - 1];
    ll added = pluses[next_plus_i];
    res /= removed;
    res *= added;
    drop(res);
  }

  if (!can_use_plus && can_use_minus) {
    ll removed = pluses[next_plus_i - 1];
    ll added = minuses[next_minus_i];
    res /= removed;
    res *= added;
    drop(res);
  }

  ll add_plus_removed = minuses[next_minus_i - 1];
  ll add_plus_added = pluses[next_plus_i];
  ll add_minus_removed = pluses[next_plus_i - 1];
  ll add_minus_added = minuses[next_minus_i];

  if (add_plus_added * add_minus_removed < add_minus_added * add_plus_removed) {
    res /= add_minus_removed;
    res *= add_minus_added;
  } else {
    res /= add_plus_removed;
    res *= add_plus_added;
  }

  cout << res << "\n";
}
