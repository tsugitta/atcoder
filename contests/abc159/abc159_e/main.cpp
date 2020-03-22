// https://atcoder.jp/contests/abc159/tasks/abc159_e

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
  ll H, W, K;
  cin >> H >> W >> K;

  V<string> mat(H);
  rep(i, H) cin >> mat[i];

  char BL = '0';
  char WH = '1';

  ll res = INF;

  rep(bit, 1 << (H - 1)) {
    VL h_to_id(H);

    rep(i, H - 1) h_to_id[i + 1] = h_to_id[i] + !!(bit & (1 << i));

    bool possible = true;
    ll ope_ct = 0;
    VL id_to_ct(H);

    rep(w, W) {
      VL col_id_to_ct(H);

      bool ope_necessary = false;

      rep(h, H) {
        ll id = h_to_id[h];

        id_to_ct[id] += mat[h][w] == WH;
        col_id_to_ct[id] += mat[h][w] == WH;

        if (col_id_to_ct[id] > K) {
          possible = false;
          break;
        }

        if (id_to_ct[id] > K) {
          ope_necessary = true;
        }
      }

      if (!possible) break;

      if (ope_necessary) {
        ++ope_ct;
        id_to_ct = col_id_to_ct;
      }
    }

    if (!possible) continue;

    ll horizontal_ope_ct = __builtin_popcountll(bit);
    chmin(res, horizontal_ope_ct + ope_ct);
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
    solve();
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
