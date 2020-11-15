// https://atcoder.jp/contests/agc049/tasks/agc049_b

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

void solve() {
  ll N;
  string S, T;
  cin >> N >> S >> T;

  deque<ll> s_is, t_is;
  rep(i, N) if (S[i] == '1') s_is.push_back(i);
  rep(i, N) if (T[i] == '1') t_is.push_back(i);

  ll res = 0;

  while (s_is.size() && t_is.size()) {
    ll si = s_is.front();
    ll ti = t_is.front();

    if (si < ti) {
      s_is.pop_front();
      if (s_is.empty()) drop(-1);

      ll si2 = s_is.front();
      res += si2 - si;

      s_is.pop_front();
      continue;
    }

    res += si - ti;
    s_is.pop_front();
    t_is.pop_front();
  }

  if (t_is.size()) drop(-1);
  unless(s_is.size() % 2 == 0) drop(-1);

  while (s_is.size()) {
    ll f = s_is.front();
    s_is.pop_front();
    ll s = s_is.front();
    s_is.pop_front();
    res += s - f;
  }

  cout << res << "\n";
}
