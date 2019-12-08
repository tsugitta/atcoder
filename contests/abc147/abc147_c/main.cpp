// https://atcoder.jp/contests/abc147/tasks/abc147_c

#include "algorithm"
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

void solve() {
  ll N;
  cin >> N;

  struct Statement {
    ll person;
    bool is_true;
  };

  V<V<Statement>> st(N, V<Statement>(0));

  rep(i, N) {
    ll a;
    cin >> a;

    rep(j, a) {
      ll x;
      bool y;
      cin >> x >> y;
      x--;

      st[i].push_back({x, y});
    }
  }

  ll res = 0;

  auto satisfied = [st, N](ll digit) -> bool {
    VL is_trues(N, -1);

    rep(i, N) {
      auto is_true = (digit >> i) & 1;

      if (is_trues[i] != -1 && is_trues[i] != is_true) return false;

      is_trues[i] = is_true;

      if (!is_true) continue;

      for (auto s : st[i]) {
        if (is_trues[s.person] != -1 && is_trues[s.person] != s.is_true)
          return false;

        is_trues[s.person] = s.is_true;
      }
    }

    return true;
  };

  rep(digit, 1 << N) {
    if (!satisfied(digit)) continue;

    ll ct = 0;

    for (ll mask = 1; mask != 0; mask <<= 1) {
      if ((digit & mask) != 0) ct++;
    }

    chmax(res, ct);
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
