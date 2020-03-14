// https://atcoder.jp/contests/panasonic2020/tasks/panasonic2020_e

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

void solve() {
  V<string> ss(3);
  rep(i, 3) cin >> ss[i];

  ll max_len = max(max(ss[0].size(), ss[1].size()), ss[2].size());

  ll res = INF;

  sort(all(ss));

  do {
    // 左端の順番が ss の順番であるとする、順に a, b, c とする。
    // oks[i][j][k]: s[i] と s[j] について、オフセットが k の時重なるか
    V<V<V<bool>>> oks(3, V<V<bool>>(3, V<bool>(max_len)));

    // ss[i] と ss[j] の重なりについて、 i < j について考える。 ss[j]
    // のオフセットは左端の条件より正となる
    rep(j, 3) rep(i, j) rep(k, ss[i].size()) {
      bool ok = true;

      rep(ji, ss[j].size()) {
        ll ii = k + ji;
        unless(ii < ss[i].size()) break;
        if (ss[i][ii] == '?' || ss[j][ji] == '?') continue;
        if (ss[i][ii] != ss[j][ji]) ok = false;
      }

      oks[i][j][k] = ok;
    }

    auto is_ok = [&](ll i, ll j, ll k) {
      if (k >= ss[i].size()) return true;
      bool res = oks[i][j][k];
      return res;
    };

    rep(offset2, max_len + 1) rep(offset3, max_len + 1) {
      if (!is_ok(0, 1, offset2)) continue;
      if (!is_ok(1, 2, offset3)) continue;
      if (!is_ok(0, 2, offset2 + offset3)) continue;

      ll r = ss[0].size();
      chmax<ll>(r, offset2 + ss[1].size());
      chmax<ll>(r, offset2 + offset3 + ss[2].size());

      chmin(res, r);
    }
  } while (next_permutation(all(ss)));

  cout << res << endl;
}

void solve2() {
  V<string> ss(3);
  rep(i, 3) cin >> ss[i];

  ll max_len = max(max(ss[0].size(), ss[1].size()), ss[2].size());

  ll res = INF;

  sort(all(ss));

  do {
    V<V<V<bool>>> oks(3, V<V<bool>>(3, V<bool>(max_len, true)));

    // ss[i] と ss[j] の重なりについて、 i < j について考える。 ss[j]
    // のオフセットは左端の条件より正となる
    rep(j, 3) rep(i, j) {
      // ss[i] の各位置から ss[j] の全文字がマッチするかを見に行くのでなく、
      // ss[i] の各文字に ss[j] // の各文字をマップし、
      // その一致不一致が影響を受けるスタート地点のオフセットを切り替えにいくアプローチ
      rep(ii, ss[i].size()) rep(ji, ss[j].size()) {
        unless(ii - ji >= 0) continue;

        auto match = [](char c1, char c2) {
          return (c1 == '?' || c2 == '?' || c1 == c2);
        };

        if (!match(ss[i][ii], ss[j][ji])) oks[i][j][ii - ji] = false;
      }
    }

    auto is_ok = [&](ll i, ll j, ll k) {
      if (k >= ss[i].size()) return true;
      bool res = oks[i][j][k];
      return res;
    };

    rep(offset2, max_len + 1) rep(offset3, max_len + 1) {
      if (!is_ok(0, 1, offset2)) continue;
      if (!is_ok(1, 2, offset3)) continue;
      if (!is_ok(0, 2, offset2 + offset3)) continue;

      ll r = ss[0].size();
      chmax<ll>(r, offset2 + ss[1].size());
      chmax<ll>(r, offset2 + offset3 + ss[2].size());

      chmin(res, r);
    }
  } while (next_permutation(all(ss)));

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
