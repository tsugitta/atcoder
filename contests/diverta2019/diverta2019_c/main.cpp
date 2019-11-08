// https://atcoder.jp/contests/diverta2019/tasks/diverta2019_c

#include "algorithm"
#include "functional"
#include "iostream"
#include "numeric"
#include "queue"
#include "set"
#include "vector"
#define rep(i, to) for (ll i = 0; i < (to); ++i)
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

void solve() {
  ll N;
  cin >> N;

  V<string> ss(N);
  rep(i, N) cin >> ss[i];

  auto get_ab_count = [](string s) {
    ll res = 0;

    repf(i, 0, s.size() - 1) {
      if (s[i] == 'A' & s[i + 1] == 'B') res++;
    }

    return res;
  };

  VL ab_counts(N);
  rep(i, N) ab_counts[i] = get_ab_count(ss[i]);

  ll a_ends = 0;
  ll b_begins = 0;
  ll a_ends_and_b_begins = 0;

  for (auto s : ss) {
    if (s[0] == 'B' && s[s.size() - 1] == 'A') a_ends_and_b_begins++;
    if (s[0] == 'B') b_begins++;
    if (s[s.size() - 1] == 'A') a_ends++;
  }

  ll res = accumulate(all(ab_counts), 0ll);

  if (a_ends_and_b_begins == a_ends && a_ends_and_b_begins == b_begins &&
      a_ends_and_b_begins > 0) {
    res += a_ends_and_b_begins - 1;
  } else {
    res += min(a_ends, b_begins);
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
