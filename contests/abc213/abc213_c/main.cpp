// https://atcoder.jp/contests/abc213/tasks/abc213_c

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
void solve2();

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

// ソートによる座標圧縮
void solve() {
  ll H, W, N;
  cin >> H >> W >> N;

  VL as(N);
  VL bs(N);

  VL hs(N);
  VL ws(N);

  rep(i, N) {
    ll a, b;
    cin >> a >> b;

    as[i] = a;
    bs[i] = b;

    hs[i] = a;
    ws[i] = b;
  }

  sort(all(hs));
  sort(all(ws));

  hs.erase(unique(all(hs)), hs.end());
  ws.erase(unique(all(ws)), ws.end());

  rep(i, N) {
    ll h = lower_bound(all(hs), as[i]) - hs.begin() + 1;
    ll w = lower_bound(all(ws), bs[i]) - ws.begin() + 1;

    cout << h << " " << w << "\n";
  }
}

// map による座標圧縮
void solve2() {
  ll H, W, N;
  cin >> H >> W >> N;

  VL as(N);
  VL bs(N);

  map<ll, ll> h_to_rank;
  map<ll, ll> w_to_rank;

  rep(i, N) {
    ll a, b;
    cin >> a >> b;

    as[i] = a;
    bs[i] = b;

    h_to_rank[a] = 0;
    w_to_rank[b] = 0;
  }

  {
    auto it = h_to_rank.begin();

    rep(i, h_to_rank.size()) {
      it->second = i;
      it++;
    }
  }

  {
    auto it = w_to_rank.begin();

    rep(i, w_to_rank.size()) {
      it->second = i;
      it++;
    }
  }

  rep(i, N) {
    ll h = h_to_rank[as[i]] + 1;
    ll w = w_to_rank[bs[i]] + 1;

    cout << h << " " << w << "\n";
  }
}
