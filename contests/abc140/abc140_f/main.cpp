// https://atcoder.jp/contests/abc140/tasks/abc140_f

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

ll pow(ll a, ll e) {
  if (a < 0 || e < 0) {
    return 0;
  }

  if (e == 0) {
    return 1;
  }

  if (e % 2 == 0) {
    ll half = pow(a, e / 2);
    return half * half;
  }

  return a * pow(a, e - 1);
}

void solve() {
  ll N;
  cin >> N;

  ll length = 1 << N;

  VL ss(length);
  rep(i, length) {
    ll s;
    cin >> s;
    s *= -1;
    ss[i] = s;
  }

  sort(all(ss));

  multiset<ll> used;
  multiset<ll> not_used;

  used.insert(ss[0]);
  repf(i, 1, length) not_used.insert(ss[i]);

  while (!not_used.empty()) {
    VL used_this_time(0);

    for (auto s : used) {
      auto it = not_used.upper_bound(s);

      if (it == not_used.end()) drop("No");

      used_this_time.push_back(*it);
      not_used.erase(it);
    }

    for (auto s : used_this_time) {
      used.insert(s);
    }
  }

  cout << "Yes" << endl;
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
