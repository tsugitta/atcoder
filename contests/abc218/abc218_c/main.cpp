// https://atcoder.jp/contests/abc218/tasks/abc218_c

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
  ll N;
  cin >> N;

  auto get_set = [&]() -> set<PL> {
    set<PL> res;

    rep(h, N) {
      string s;
      cin >> s;

      rep(w, N) {
        if (s[w] == '#') res.emplace(h, w);
      }
    }

    return res;
  };

  auto rotate = [&](set<PL> s) -> set<PL> {
    set<PL> new_s;

    for (auto [h, w] : s) {
      new_s.emplace(N - 1 - w, h);
    }

    return new_s;
  };

  auto as = get_set();
  auto bs = get_set();

  auto matched = [&](set<PL> a, set<PL> b) -> bool {
    if (a.size() != b.size()) return false;

    auto [t_ah, t_aw] = *a.begin();
    auto [t_bh, t_bw] = *b.begin();

    for (auto it = a.begin(); it != a.end(); ++it) {
      auto [ah, aw] = *it;
      unless(b.count({ah - t_ah + t_bh, aw - t_aw + t_bw})) return false;
    }

    return true;
  };

  rep(i, 4) {
    if (matched(as, bs)) drop("Yes");
    set<PL> new_as = rotate(as);
    swap(as, new_as);
  }

  cout << "No"
       << "\n";
}
