// https://atcoder.jp/contests/dp/tasks/dp_f

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
  string s, t;
  cin >> s >> t;

  // dp[i][j]: S の i 文字目 (1-indexed) と t の j 文字目までを使用した場合の
  // LCS 長
  auto dp = VVL(s.size() + 1, VL(t.size() + 1, 0));

  rep(i, 0, s.size()) {
    rep(j, 0, t.size()) {
      if (s[i] == t[j]) {
        dp[i + 1][j + 1] = dp[i][j] + 1;
      } else {
        dp[i + 1][j + 1] = max(dp[i + 1][j], dp[i][j + 1]);
      }
    }
  }

  string res = "";

  auto si = s.size();
  auto ti = t.size();

  while (si > 0 && ti > 0) {
    if (dp[si][ti] == dp[si - 1][ti]) {
      si--;
      continue;
    }

    if (dp[si][ti] == dp[si][ti - 1]) {
      ti--;
      continue;
    }

    // si, ti は LCS に含まれる
    res += s[si - 1];
    si--;
    ti--;
  }

  reverse(res.begin(), res.end());

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
