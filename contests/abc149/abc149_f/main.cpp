// https://atcoder.jp/contests/abc149/tasks/abc149_f

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

ll N;
VVL edge_list;
V<map<ll, ll>> ct_memo;

// u 以降の点の数, p を含まない
ll get_node_ct(ll u, ll p) {
  if (ct_memo[p].count(u) > 0) return ct_memo[p][u];
  if (ct_memo[u].count(p) > 0) return N - ct_memo[u][p];

  ll res = 1;

  for (auto v : edge_list[u]) {
    if (v == p) continue;
    res += get_node_ct(v, u);
  }

  ct_memo[p][u] = res;
  return res;
}

void solve() {
  cin >> N;

  edge_list = VVL(N, VL(0));
  ct_memo = V<map<ll, ll>>(N, map<ll, ll>());

  rep(i, N - 1) {
    ll a, b;
    cin >> a >> b;
    a--, b--;

    edge_list[a].push_back(b);
    edge_list[b].push_back(a);
  }

  // 全 S の頂点数の期待値 - 全木の黒頂点の数の期待値

  // 全 S の頂点数の期待値 = 全 S の辺の数の期待値 + 1
  // 各辺が S の頂点数に寄与する期待値 = S の頂点に入る確率 を合計すれば良い
  mint edge_ct_e = 0;

  rep(u, N) {
    for (ll v : edge_list[u]) {
      unless(u < v) continue;

      ll ct_u = get_node_ct(u, v);
      ll ct_v = N - ct_u;

      // この辺が S に含まれる確率 = u 側, v　側に一つでも黒がある確率
      mint r_for_edge = (mint(1) - mint(1) / modpow(mint(2), ct_u)) *
                        (mint(1) - mint(1) / modpow(mint(2), ct_v));
      edge_ct_e += r_for_edge;
    }
  }

  mint empty_prob = mint(1) / modpow(mint(2), N);
  mint node_ct_e = edge_ct_e + 1;
  node_ct_e -= empty_prob;  // 空グラフの場合の 1 が加算されている

  mint res = node_ct_e;

  // 全木の黒頂点の数の期待値
  res -= mint(N) / 2;

  cout << res << endl;
}

void solve2() {
  cin >> N;

  edge_list = VVL(N, VL(0));
  ct_memo = V<map<ll, ll>>(N, map<ll, ll>());

  rep(i, N - 1) {
    ll a, b;
    cin >> a >> b;
    a--, b--;

    edge_list[a].push_back(b);
    edge_list[b].push_back(a);
  }

  // 全 S の頂点数の期待値 - 全木の黒頂点の数の期待値

  // 全 S の頂点数の期待値 = \sum 各頂点が S に含まれる確率 * 1
  mint node_ct_e = 0;

  rep(u, N) {
    // u が黒の場合、 u は S に含まれる。
    // u が白の場合、 u に接続される部分木について、そのうち 2
    // つ以上に黒が含まれると u は S に含まれる。
    // 全体の通り 2^(N-1) から一つも黒が無い通り 1
    // と一つしか黒を含むものが無い通り \sum (2^Ct - 1) を引けば良い
    mint black_node_e = mint(1);
    mint white_node_e = modpow(mint(2), N - 1) - 1;

    for (ll v : edge_list[u]) {
      ll ct_v = get_node_ct(v, u);
      white_node_e -= modpow(mint(2), ct_v) - 1;
    }

    white_node_e /= modpow(mint(2), N - 1);

    mint node_e = (black_node_e + white_node_e) / 2;
    node_ct_e += node_e;
  }

  mint res = node_ct_e;

  // 全木の黒頂点の数の期待値
  res -= mint(N) / 2;

  cout << res << endl;
}

void solve3() {
  cin >> N;

  edge_list = VVL(N, VL(0));
  ct_memo = V<map<ll, ll>>(N, map<ll, ll>());

  rep(i, N - 1) {
    ll a, b;
    cin >> a >> b;
    a--, b--;

    edge_list[a].push_back(b);
    edge_list[b].push_back(a);
  }

  mint res = 0;

  rep(u, N) {
    // u が白かつ u に接続される部分木について、そのうち 2
    // つ以上に黒が含まれると u は「穴あき」にカウントされる
    // 全体の通り 2^(N-1) から一つも黒が無い通り 1
    // と一つしか黒を含むものが無い通り \sum (2^Ct - 1) を引けば良い
    mint u_e = modpow(mint(2), N - 1) - 1;

    for (ll v : edge_list[u]) {
      ll ct_v = get_node_ct(v, u);
      u_e -= modpow(mint(2), ct_v) - 1;
    }

    u_e /= modpow(mint(2), N);

    res += u_e;
  }

  cout << res << endl;
}

VVL dp;
VL dp_sum;

ll dfs(ll u, ll p = -1) {
  dp[u] = VL(edge_list[u].size());

  rep(i, edge_list[u].size()) {
    ll v = edge_list[u][i];
    if (v == p) continue;

    dp[u][i] = dfs(v, u);
    dp_sum[u] += dp[u][i];
  }

  return dp_sum[u] + 1;
}

ll dfs2(ll u, ll p_ct = -1, ll p = -1) {
  if (p != -1) dp_sum[u] += p_ct;

  rep(i, edge_list[u].size()) {
    ll v = edge_list[u][i];

    if (v == p) {
      dp[u][i] = p_ct;
      continue;
    }

    ll reverse_ct = dp_sum[u] - dp[u][i] + 1;
    dfs2(v, reverse_ct, u);
  }
}

// solve 3 の方法 + 全方位木 DP で個数を求める
void solve4() {
  cin >> N;

  edge_list = VVL(N, VL(0));
  dp = VVL(N, VL(0));
  dp_sum = VL(N);

  rep(i, N - 1) {
    ll a, b;
    cin >> a >> b;
    a--, b--;

    edge_list[a].push_back(b);
    edge_list[b].push_back(a);
  }

  dfs(0);
  dfs2(0);

  mint res = 0;

  rep(u, N) {
    mint u_e = modpow(mint(2), N - 1) - 1;

    rep(i, edge_list[u].size()) {
      ll v = edge_list[u][i];
      ll ct_v = dp[u][i];
      u_e -= modpow(mint(2), ct_v) - 1;
    }

    u_e /= modpow(mint(2), N);

    res += u_e;
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
    solve4();
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
