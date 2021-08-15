// https://atcoder.jp/contests/abc214/tasks/abc214_e

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
  ll T;
  cin >> T;

  auto partial = []() -> bool {
    ll N;
    cin >> N;

    VPL cs(N);
    for (auto& [l, r] : cs) cin >> l >> r;

    sort(all(cs));

    multiset<ll> rs;

    set<ll> pos_s;
    for (auto [l, r] : cs) pos_s.insert(l);

    map<ll, vector<ll>> l_to_is;
    rep(i, N) l_to_is[cs[i].fi].push_back(i);

    while (!pos_s.empty()) {
      ll pos = *pos_s.begin();
      pos_s.erase(pos_s.begin());

      for (ll i : l_to_is[pos]) {
        auto [l, r] = cs[i];
        rs.insert(r);
      }

      if (rs.empty()) continue;

      ll min_r = *rs.begin();
      if (min_r < pos) return false;

      rs.erase(rs.begin());
      pos_s.insert(pos + 1);
    }

    return true;
  };

  rep(i, T) {
    string res = partial() ? "Yes" : "No";
    cout << res << "\n";
  }
}
