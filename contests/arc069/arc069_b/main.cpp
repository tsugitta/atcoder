// https://atcoder.jp/contests/arc069/tasks/arc069_b

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
  string S;
  cin >> N >> S;

  auto get_next = [](char prev, char cur, char ch) -> char {
    if (cur == 'S' && ch == 'o') return prev == 'S' ? 'S' : 'W';
    if (cur == 'S' && ch == 'x') return prev == 'S' ? 'W' : 'S';
    if (cur == 'W' && ch == 'o') return prev == 'S' ? 'W' : 'S';
    if (cur == 'W' && ch == 'x') return prev == 'S' ? 'S' : 'W';
  };

  auto to_s = [](ll v) -> char { return v == 0 ? 'S' : 'W'; };

  rep(f, 2) rep(s, 2) {
    string res;

    res.push_back(to_s(f));
    res.push_back(to_s(s));

    repf(cur_i, 1, N - 1) {
      char n = get_next(res[cur_i - 1], res[cur_i], S[cur_i]);
      res.push_back(n);
    }

    if (get_next(res[N - 2], res[N - 1], S[N - 1]) == res[0] &&
        get_next(res[N - 1], res[0], S[0]) == res[1])
      drop(res);
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
