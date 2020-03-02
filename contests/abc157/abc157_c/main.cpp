// https://atcoder.jp/contests/abc157/tasks/abc157_c

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
  ll N, M;
  cin >> N >> M;

  VL digits(N, -1);

  rep(i, M) {
    ll s, c;
    cin >> s >> c;
    s--;

    if (s == 0 && c == 0 && N >= 2) drop(-1);
    if (digits[s] != -1 && digits[s] != c) drop(-1);

    digits[s] = c;
  }

  if (N == 1) {
    if (digits[0] == -1) drop(0);
    drop(digits[0]);
  }

  if (digits[0] == -1) digits[0] = 1;

  rep(i, N) {
    if (digits[i] == -1) {
      digits[i] = i == 0 ? 1 : 0;
    }
  }

  rep(i, N) cout << digits[i];

  cout << endl;
}

void solve2() {
  ll N, M;
  cin >> N >> M;

  VPL cons(M);
  rep(i, M) cin >> cons[i].fi >> cons[i].se;

  rep(num, 1000) {
    string str = to_string(num);
    unless(str.size() == N) continue;

    bool ok = true;

    for (auto c : cons) {
      unless(str[c.fi - 1] - '0' == c.se) {
        ok = false;
        break;
      }
    }

    if (ok) drop(num);
  }

  drop(-1);
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
