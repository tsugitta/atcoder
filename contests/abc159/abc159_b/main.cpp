// https://atcoder.jp/contests/abc159/tasks/abc159_b

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

bool is_kaibun(string s) {
  ll n = s.size();

  rep(i, n) {
    unless(i < n - 1 - i) break;
    unless(s[i] == s[n - 1 - i]) return false;
  }

  return true;
}

bool is_kaibun2(string s) {
  string t(s.rbegin(), s.rend());
  return s == t;
}

void solve() {
  string S;
  cin >> S;
  ll N = S.size();

  ll f_from = 0;
  ll f_to = (N - 1) / 2 - 1;

  ll s_from = (N + 3) / 2 - 1;
  ll s_to = N - 1;

  bool res = is_kaibun(S) && is_kaibun(S.substr(f_from, f_to - (f_from - 1))) &&
             is_kaibun(S.substr(s_from, s_to - (s_from - 1)));

  if (res) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }
}

void solve2() {
  string S;
  cin >> S;
  ll N = S.size();

  ll f_from = 0;
  ll f_to = (N - 1) / 2;

  ll s_from = (N + 3) / 2 - 1;
  ll s_to = N;

  bool res = is_kaibun2(S) &&
             is_kaibun2(string(S.begin() + f_from, S.begin() + f_to)) &&
             is_kaibun2(string(S.begin() + s_from, S.begin() + s_to));

  if (res) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }
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
