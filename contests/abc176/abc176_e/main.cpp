// https://atcoder.jp/contests/abc176/tasks/abc176_e

#include "algorithm"
#include "bitset"
#include "cmath"
#include "functional"
#include "iomanip"
#include "iostream"
#include "map"
#include "numeric"
#include "queue"
#include "string"
#include "unordered_set"
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

void solve() {
  ll H, W, M;
  cin >> H >> W >> M;

  VPL bs(M);
  map<int, unordered_set<int>> wh, hw;

  rep(i, M) {
    ll h, w;
    cin >> h >> w;
    h--, w--;
    bs[i].fi = h;
    bs[i].se = w;

    wh[w].insert(h);
    hw[h].insert(w);
  }

  VL h_ct(H);
  VL w_ct(W);

  rep(i, M) {
    auto [h, w] = bs[i];
    w_ct[w]++;
    h_ct[h]++;
  }

  ll w_ct_max = 0;
  ll h_ct_max = 0;

  rep(h, H) chmax(h_ct_max, h_ct[h]);
  rep(w, W) chmax(w_ct_max, w_ct[w]);

  VL hs;
  VL ws;

  rep(h, H) if (h_ct[h] == h_ct_max) hs.push_back(h);
  rep(w, W) if (w_ct[w] == w_ct_max) ws.push_back(w);

  ll res = w_ct_max + h_ct_max;

  // 爆弾の個数は M 個。組み合わせが M+1 以上の場合、 M+1 個の組を見終える前に
  // drop されるため O(M)
  for (ll h : hs) {
    for (ll w : ws) {
      if (hw[h].count(w) == 0) drop(res);
    }
  }

  res--;
  cout << res << "\n";
}
