// https://atcoder.jp/contests/agc024/tasks/agc024_b

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

  VL ps(N);
  rep(i, N) cin >> ps[i];

  // sort_length[num]: num の位置から後方に続く num-1
  // 以下を無視したソート列の長さ
  VL sort_length(N + 1);

  {
    repr(i, N) {
      if (ps[i] == N) {
        sort_length[N] = 1;
      } else {
        sort_length[ps[i]] = sort_length[ps[i] + 1] + 1;
      }
    }
  }

  ll res = N;

  // num を先頭に持ってくる場合の数.
  // num が 0 -> 何も先頭に持ってこない
  // num が N -> 何も後方に持ってこない
  rep(num, N + 1) {
    ll _res = 0;
    _res += num;  // num と、num 未満の数全てを先頭に持ってくる
    // 残りは、 （残り - num+1 以上のソート配列）を後方に持ってくる
    if (num < N) {
      _res += (N - num - sort_length[num + 1]);
    }

    chmin(res, _res);
  }

  cout << res << endl;
}

void solve2() {
  ll N;
  cin >> N;

  VL ps(N);
  rep(i, N) cin >> ps[i];

  // sort_length[num]: num の位置から後方に続く num-1
  // 以下を無視したソート列の長さ
  VL sort_length(N + 1);

  ll max_sort_length = 0;
  {
    repr(i, N) {
      if (ps[i] == N) {
        sort_length[N] = 1;
      } else {
        sort_length[ps[i]] = sort_length[ps[i] + 1] + 1;
      }

      chmax(max_sort_length, sort_length[ps[i]]);
    }
  }

  // 最長ソート列以外の数を移動すれば答えとなる
  ll res = N - max_sort_length;

  cout << res << endl;
}

void solve3() {
  ll N;
  cin >> N;

  VL ps(N);
  rep(i, N) cin >> ps[i];

  // sort_length[num]: num の位置を最後とするソート列の長さ
  VL sort_length(N + 1);

  ll max_sort_length = 0;
  {
    rep(i, N) {
      if (ps[i] == 0) {
        sort_length[ps[i]] = 1;
      } else {
        sort_length[ps[i]] = sort_length[ps[i] - 1] + 1;
      }

      chmax(max_sort_length, sort_length[ps[i]]);
    }
  }

  // 最長ソート列以外の数を移動すれば答えとなる
  ll res = N - max_sort_length;

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
    solve3();
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
