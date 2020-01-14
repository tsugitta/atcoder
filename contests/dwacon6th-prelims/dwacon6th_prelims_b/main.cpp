// https://atcoder.jp/contests/dwacon6th-prelims/tasks/dwacon6th_prelims_b

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

void solve() {
  ll N;
  cin >> N;

  VL xs(N);
  rep(i, N) cin >> xs[i];

  mint res = 0;

  V<mint> ps(N + 1);  // ps[i]: 1/1 + .. + 1/i
  ps[1] = 1;
  rep1(i, N - 1) { ps[i + 1] = ps[i] + mint(1) / (i + 1); }

  rep(i, N - 1) {
    // xs[i] ~ xs[i+1] が寄与する期待値はその距離 x 各スライムが通過する確率の和
    // xs[i] : 1
    // xs[i-1]: 1/2
    // xs[0]: 1/(i+1)
    res += ps[i + 1] * (xs[i + 1] - xs[i]);
  }

  rep1(i, N - 1) { res *= i; }

  cout << res << endl;
}

void solve2() {
  ll N;
  cin >> N;

  VL xs(N);
  rep(i, N) cin >> xs[i];

  mint res = 0;

  // i から j に行く通りは (1-indexed)
  // j == N : (N-1)! / (N-i)
  // j < N  : (N-1)! / ((j-i+1)(j-i))

  // j == N
  rep(i, N - 1) { res += mint(xs[N - 1] - xs[i]) / (N - 1 - i); }

  V<mint> ds(N);  // ds[i]: 距離が i のものの総距離。 右端が N-1 のものを除く

  {
    mint acc = 0;

    for (ll d = 1; d <= N - 2; d++) {
      unless(d <= N - 1 - d) break;
      mint new_diff = (xs[N - 1 - d] - xs[d - 1]);
      ds[d] = acc + new_diff;
      ds[N - 1 - d] = acc + new_diff;
      acc += new_diff;
    }
  }

  // j < N
  rep1(d, N - 2) {
    // d = j - i とすると通りは (N-1)! / (d*(d+1))
    res += ds[d] / (d * (d + 1));
  }

  rep1(i, N - 1) { res *= i; }

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
    solve2();
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
