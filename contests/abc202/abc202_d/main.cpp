// https://atcoder.jp/contests/abc202/tasks/abc202_d

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
  ll A, B, K;
  cin >> A >> B >> K;

  VVL memo(A + 1, VL(B + 1, -1));

  auto get_ct = [&](auto self, ll a, ll b) -> ll {
    assert(a >= 0);
    assert(b >= 0);
    if (a == 0 && b == 0) return 1;
    if (memo[a][b] != -1) return memo[a][b];

    ll res = 0;
    if (a > 0) res += self(self, a - 1, b);
    if (b > 0) res += self(self, a, b - 1);

    return memo[a][b] = res;
  };

  map<char, ll> rest_ch;
  rest_ch['a'] = A;
  rest_ch['b'] = B;
  ll rest = K;

  string res = "";

  auto use = [&](char c) {
    res.push_back(c);
    rest_ch[c]--;
  };

  rep(i, A + B) {
    if (rest_ch['a'] == 0) {
      use('b');
      continue;
    } else if (rest_ch['b'] == 0) {
      use('a');
      continue;
    }

    ll ct_for_a_is_head = get_ct(get_ct, rest_ch['a'] - 1, rest_ch['b']);

    if (rest > ct_for_a_is_head) {
      use('b');
      rest -= ct_for_a_is_head;
    } else {
      use('a');
    }
  }

  cout << res << "\n";
}
