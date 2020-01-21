// https://atcoder.jp/contests/abc152/tasks/abc152_d

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
  ll N;
  cin >> N;

  // 末尾は 0 でない
  VVL cts(10, VL(10));

  rep1(f, 9) rep1(b, 9) {
    if (f == b && f <= N) {
      cts[f][b]++;
    }

    ll digit = 2;
    for (ll digit = 2; f * pow(10, digit - 1) + b <= N; digit++) {
      ll low = f * pow(10, digit - 1) + b;
      ll high = (f + 1) * pow(10, digit - 1) - 10 + b;

      if (high <= N) {
        cts[f][b] += pow(10, digit - 2);
        continue;
      }

      // N の先頭と末尾を除いた数 + 0 only
      ll mid_ct = N / 10 - f * pow(10, digit - 2) + 1;

      if (N % 10 >= b) {
        cts[f][b] += mid_ct;
      } else if (N % 10 < b) {
        cts[f][b] += mid_ct - 1;
      }
    }
  }

  ll res = 0;

  rep1(f, 9) rep1(b, 9) { res += cts[f][b] * cts[b][f]; }

  cout << res << endl;
}

void solve2() {
  ll N;
  cin >> N;

  // 末尾は 0 でない
  VVL cts(10, VL(10));

  rep1(num, N) {
    string str = to_string(num);

    ll f = str.front() - '0';
    ll b = str.back() - '0';

    if (b == 0) continue;

    cts[f][b]++;
  }

  ll res = 0;

  rep1(f, 9) rep1(b, 9) { res += cts[f][b] * cts[b][f]; }

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
