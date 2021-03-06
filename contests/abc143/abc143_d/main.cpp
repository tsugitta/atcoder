// https://atcoder.jp/contests/abc143/tasks/abc143_d

#include "algorithm"
#include "iostream"
#include "set"
#include "vector"
#define rep(i, from, to) for (ll i = from; i < (to); ++i)
using namespace std;
typedef long long ll;
template <typename T>
using V = vector<T>;
using VL = V<ll>;
using VVL = V<VL>;
template <typename T>
inline bool chmax(T& a, T b);
template <typename T>
inline bool chmin(T& a, T b);
void print_ints(vector<ll> v);
template <typename T>
void drop(T a);

void solve() {
  ll N;
  cin >> N;

  VL ls(N);

  rep(i, 0, N) { cin >> ls[i]; }

  sort(ls.begin(), ls.end());

  ll res = 0;

  rep(i, 0, N) rep(j, i + 1, N) {
    ll m = ls[i] + ls[j];
    auto sep = lower_bound(ls.begin(), ls.end(), m) - ls.begin();
    res += sep - j - 1;
  }

  cout << res << endl;
}

// 尺取り
void solve2() {
  ll N;
  cin >> N;

  VL ls(N);

  rep(i, 0, N) { cin >> ls[i]; }

  sort(ls.begin(), ls.end());

  ll res = 0;

  rep(b, 0, N) {
    ll c_r = b + 1;
    ll c_l = b + 1;

    rep(a, 0, b) {
      ll m = ls[a] + ls[b];

      // c: [c_l, c_r)
      while (c_r < N && ls[c_r] < m) c_r++;

      res += c_r - c_l;
    }
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
  rep(i, 0, v.size()) {
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
