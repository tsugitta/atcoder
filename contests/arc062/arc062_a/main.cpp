// https://atcoder.jp/contests/arc062/tasks/arc062_a

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

  ll f, s;
  cin >> f >> s;

  rep(i, N - 1) {
    ll fr, sr;
    cin >> fr >> sr;

    if (f * sr == s * fr) continue;

    ll min_n_f = fr * ((f + fr - 1) / fr);  // f を超える最小の fr の倍数
    ll min_n_s = sr * ((s + sr - 1) / sr);

    VL f_cand(0);
    VL s_cand(0);

    if (min_n_f / fr * sr >= s) {
      f_cand = {min_n_f, min_n_f / fr * sr};
    }

    if (min_n_s / sr * fr >= f) {
      s_cand = {min_n_s / sr * fr, min_n_s};
    }

    if (f_cand.size() != 0 &&
        (s_cand.size() == 0 ||
         f_cand[0] + f_cand[1] <= s_cand[0] + s_cand[1])) {
      f = f_cand[0];
      s = f_cand[1];
    } else {
      f = s_cand[0];
      s = s_cand[1];
    }
  }

  cout << f + s << endl;
}

void solve2() {
  ll N;
  cin >> N;

  ll f, s;
  cin >> f >> s;

  rep(i, N - 1) {
    ll fr, sr;
    cin >> fr >> sr;

    ll times = max((f + fr - 1) / fr, (s + sr - 1) / sr);

    f = fr * times;
    s = sr * times;
  }

  cout << f + s << endl;
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
