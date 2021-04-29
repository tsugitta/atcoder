// https://atcoder.jp/contests/abc198/tasks/abc198_d

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
  ll S_CT = 3;

  V<string> S(S_CT);
  rep(i, S_CT) cin >> S[i];

  set<char> char_set;

  for (auto s : S) {
    for (auto c : s) {
      char_set.insert(c);
    }
  }

  string UNSOLVABLE = "UNSOLVABLE";
  if (char_set.size() > 10) drop(UNSOLVABLE);

  V<char> chars(all(char_set));

  V<int> numbers(10);
  rep(i, 10) numbers[i] = i;

  do {
    map<char, int> char_to_number;
    rep(i, chars.size()) char_to_number[chars[i]] = numbers[i];

    if (any_of(all(S), [&](string s) { return char_to_number[s[0]] == 0; })) {
      continue;
    }

    auto s_to_i = [&](string s) -> ll {
      ll res = 0;

      for (auto c : s) {
        res = 10 * res + char_to_number[c];
      }

      return res;
    };

    VL s_nums(S_CT);
    rep(i, S_CT) s_nums[i] = s_to_i(S[i]);

    if (s_nums[0] + s_nums[1] == s_nums[2]) {
      rep(i, S_CT) cout << s_nums[i] << "\n";
      throw exit_exception();
    }
  } while (next_permutation(all(numbers)));

  cout << UNSOLVABLE << "\n";
}
