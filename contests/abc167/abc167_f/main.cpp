// https://atcoder.jp/contests/abc167/tasks/abc167_f

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

  struct Diff {
    ll min_h, h_diff;
  };

  V<Diff> ls, rs;

  string Yes = "Yes";
  string No = "No";

  rep(i, N) {
    string s;
    cin >> s;

    ll h_diff = 0;
    ll min_h = 0;

    for (char c : s) {
      if (c == '(') {
        ++h_diff;
      } else {
        --h_diff;
      }

      chmin(min_h, h_diff);
    }

    if (h_diff >= 0) {
      ls.push_back({min_h, h_diff});
    } else {
      rs.push_back({min_h - h_diff, -h_diff});
    }
  }

  {
    ll l_sum = 0;
    ll r_sum = 0;

    for (auto l : ls) l_sum += l.h_diff;
    for (auto r : rs) r_sum += r.h_diff;

    if (l_sum != r_sum) drop(No);
  }

  auto is_ok_seq = [](V<Diff>& seq) -> bool {
    sort(all(seq), [](Diff a, Diff b) { return a.min_h > b.min_h; });

    ll cur = 0;

    for (auto d : seq) {
      unless(cur + d.min_h >= 0) return false;
      cur += d.h_diff;
    }

    return true;
  };

  unless(is_ok_seq(ls) && is_ok_seq(rs)) drop(No);
  drop(Yes);
}
