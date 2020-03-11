// https://atcoder.jp/contests/arc071/tasks/arc071_b

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

void solve() {
  ll N, M;
  cin >> N >> M;

  VL xs(N);
  rep(i, N) cin >> xs[i];

  VL ys(M);
  rep(i, M) cin >> ys[i];

  ll W = N - 1;
  ll H = M - 1;

  VL w_cts(W);
  VL h_cts(H);

  rep(i, W) {
    if (w_cts[i] > 0) break;
    if (i > 0) w_cts[i] += w_cts[i - 1];

    ll ct = W - 2 * i;
    w_cts[i] += ct;
    w_cts[W - 1 - i] = w_cts[i];
  }

  rep(i, H) {
    if (h_cts[i] > 0) break;
    if (i > 0) h_cts[i] += h_cts[i - 1];

    ll ct = H - 2 * i;
    h_cts[i] += ct;
    h_cts[H - 1 - i] = h_cts[i];
  }

  mint x_sum = 0;
  rep(i, W) {
    ll w = xs[i + 1] - xs[i];
    x_sum += w * w_cts[i];
  }

  mint y_sum = 0;
  rep(i, H) {
    ll h = ys[i + 1] - ys[i];
    y_sum += h * h_cts[i];
  }

  mint res = x_sum * y_sum;
  cout << res << endl;
}

void solve2() {
  ll N, M;
  cin >> N >> M;

  VL xs(N);
  rep(i, N) cin >> xs[i];

  VL ys(M);
  rep(i, M) cin >> ys[i];

  mint x_sum = 0;

  // 各長方形の width は x_k - x_j と表される。各 x_i
  // が何回足されて引かれるるかを考える
  rep(i, N) { x_sum += xs[i] * (i - (N - 1 - i)); }

  mint y_sum = 0;

  rep(i, M) { y_sum += ys[i] * (i - (M - 1 - i)); }

  mint res = x_sum * y_sum;
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
