// https://atcoder.jp/contests/abc136/tasks/abc136_f

#include "algorithm"
#include "iostream"
#include "map"
#include "vector"
#define rep(i, from, to) for (ll i = from; i < (to); ++i)
using namespace std;
typedef long long ll;

template <class T>
inline bool chmax(T& a, T b);
template <class T>
inline bool chmin(T& a, T b);

template <int MOD>
class Fp {
 public:
  long long val;
  constexpr Fp(long long v = 0) noexcept : val(v % MOD) {
    if (val < 0) v += MOD;
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
  friend constexpr istream& operator>>(istream& is, Fp<MOD>& x) noexcept {
    return is >> x.val;
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
using mint = Fp<MOD>;

struct Fenwick {
  vector<ll> tree;

  Fenwick(ll n) : tree(vector<ll>(n, 0)) {}

  // sum of [0, i)
  ll sum(ll i) {
    ll res = 0;

    for (i--; i >= 0; i = (i & (i + 1)) - 1) {
      res += tree[i];
    }

    return res;
  }

  void add(ll i, ll n) {
    for (ll len = tree.size(); i < len; i |= i + 1) {
      tree[i] += n;
    }
  }
};

template <typename T>
map<T, ll> to_index(const vector<T>& v) {
  map<T, ll> res;
  for (ll i = 0; i < v.size(); i++) res[v[i]] = i;
  return res;
}

void solve() {
  ll N;
  cin >> N;

  auto ps = vector<pair<ll, ll>>(N);

  rep(i, 0, N) {
    ll x, y;
    cin >> x >> y;
    ps[i] = pair<ll, ll>(x, y);
  }

  {
    // y の座標圧縮
    vector<ll> ys(N);
    rep(i, 0, N) { ys[i] = ps[i].second; }

    sort(ys.begin(), ys.end());

    rep(i, 0, N) {
      ps[i].second =
          lower_bound(ys.begin(), ys.end(), ps[i].second) - ys.begin();
    }
  }

  sort(ps.begin(), ps.end());

  vector<ll> lu(N), ld(N), ru(N), rd(N);

  {
    Fenwick bit(N);

    rep(i, 0, ps.size()) {
      auto p = ps[i];
      ld[i] = bit.sum(p.second);
      lu[i] = bit.sum(N) - ld[i];
      bit.add(p.second, 1);
    }
  }

  {
    Fenwick bit(N);

    for (ll i = ps.size() - 1; i >= 0; i--) {
      auto p = ps[i];
      rd[i] = bit.sum(p.second);
      ru[i] = bit.sum(N) - rd[i];
      bit.add(p.second, 1);
    }
  }

  mint res = 0;

  rep(i, 0, ps.size()) {
    // E: Exist, A: Any
    mint luA = modpow(mint(2), lu[i]);
    mint luE = luA - 1;
    mint ldA = modpow(mint(2), ld[i]);
    mint ldE = ldA - 1;
    mint ruA = modpow(mint(2), ru[i]);
    mint ruE = ruA - 1;
    mint rdA = modpow(mint(2), rd[i]);
    mint rdE = rdA - 1;

    // その点自身を含まない場合
    res += luE * ldA * ruA * rdE;
    res += luA * ldE * ruE * rdA;
    res -= luE * ldE * ruE * rdE;

    // その点自身を含む場合
    res += luA * ldA * ruA * rdA;
  }

  cout << res << endl;
}

#ifndef TEST
int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  solve();
  return 0;
}
#endif

template <class T>
inline bool chmax(T& a, T b) {
  if (a < b) {
    a = b;
    return 1;
  }
  return 0;
}

template <class T>
inline bool chmin(T& a, T b) {
  if (a > b) {
    a = b;
    return 1;
  }
  return 0;
}
