// https://atcoder.jp/contests/abc219/tasks/abc219_f

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
  string S;
  ll K;
  cin >> S >> K;

  VPL ps;
  ll shift_x = 0;
  ll shift_y = 0;

  {
    set<PL> p_set;

    // L146 で負の座標に対する助産を避けるためにずらしておく
    ll ORIGIN = 1e6;
    PL cur{ORIGIN, ORIGIN};
    p_set.emplace(ORIGIN, ORIGIN);

    map<char, PL> c_to_diff{
        {'R', {1, 0}},
        {'L', {-1, 0}},
        {'U', {0, -1}},
        {'D', {0, 1}},
    };

    for (char c : S) {
      auto [dx, dy] = c_to_diff[c];

      cur.fi += dx;
      cur.se += dy;
      p_set.insert(cur);
    }

    shift_x = cur.fi - ORIGIN;
    shift_y = cur.se - ORIGIN;

    for (auto p : p_set) ps.push_back(p);
  }

  ll N = ps.size();

  if (shift_x == 0 && shift_y == 0) drop(N);

  // ds[i] = k ⇔ ps[i] を l 回平行移動すると ps の点と重なる & k は最小の l;
  VL ds(N, INF);

  {
    map<PL, VPL> mp;  // (x, y) の mod -> {平行移動回数, id}

    rep(i, N) {
      auto& [x, y] = ps[i];
      ll ct = shift_x != 0 ? x / shift_x : y / shift_y;
      mp[{x - ct * shift_x, y - ct * shift_y}].emplace_back(ct, i);
    }

    for (auto& [_, vals] : mp) {
      sort(all(vals));

      rep(i, (ll)vals.size() - 1) {
        ds[vals[i].se] = vals[i + 1].fi - vals[i].fi;
      }
    }
  }

  ll res = 0;
  for (auto& d : ds) res += min(d, K);

  cout << res << "\n";
}
