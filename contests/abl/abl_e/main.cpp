// https://atcoder.jp/contests/abl/tasks/abl_e

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

using mint = modint998244353;
const mint inv9 = mint(1) / 9;

// ref:
// https://www.youtube.com/watch?v=D0Op33UL_cA&feature=youtu.be&ab_channel=AtCoderLive

struct S {
  mint x;
  mint w;  // s_a * s_b する時 s_a 側にかけるべき数。 10^(len(x))

  S(mint x = 0, mint w = 1) : x(x), w(w) {}
};

// 連結した数字の mod （とその桁数）を返す
S op(S a, S b) { return S(a.x * b.w + b.x, a.w * b.w); }

S e() { return S(); }

S mapping(ll f, S a) {
  if (f == 0) return a;
  // a の全桁を f に書き換える
  // (a.w - 1) / 9 は a の桁数だけ 1 が並んだ数となっている
  return S((a.w - 1) * inv9 * f, a.w);
}

ll composition(ll f, ll g) {
  if (f == 0) return g;
  return f;
}

ll id() { return 0; }

void solve() {
  ll N, Q;
  cin >> N >> Q;

  lazy_segtree<S, op, e, ll, mapping, composition, id> st(N);

  rep(i, N) st.set(i, S(1, 10));

  rep(i, Q) {
    ll l, r, d;
    cin >> l >> r >> d;
    --l;
    st.apply(l, r, d);
    int res = st.all_prod().x.val();
    cout << res << "\n";
  }
}
