// https://atcoder.jp/contests/abc210/tasks/abc210_c

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
#include "unordered_map"
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
void solve2();

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

void solve() {
  ll N, K;
  cin >> N >> K;

  queue<ll> q;
  rep(i, N) {
    ll c;
    cin >> c;
    q.push(c);
  }

  unordered_map<ll, ll> color_to_ct;
  queue<ll> to_be_deleted;

  rep(i, K) {
    ll next = q.front();
    q.pop();

    color_to_ct[next]++;
    to_be_deleted.push(next);
  }

  ll res = color_to_ct.size();

  while (q.size()) {
    ll deleted_next = to_be_deleted.front();
    to_be_deleted.pop();

    color_to_ct[deleted_next]--;
    if (color_to_ct[deleted_next] == 0) color_to_ct.erase(deleted_next);

    ll next = q.front();
    q.pop();

    color_to_ct[next]++;
    to_be_deleted.push(next);

    chmax(res, (ll)color_to_ct.size());
  }

  cout << res << "\n";
}

void solve2() {
  ll N, K;
  cin >> N >> K;

  VL cs(N);
  rep(i, N) cin >> cs[i];

  unordered_map<ll, ll> color_to_ct;

  rep(i, K) color_to_ct[cs[i]]++;

  ll res = color_to_ct.size();

  repf(i, K, N) {
    ll deleted = cs[i - K];
    color_to_ct[deleted]--;
    if (color_to_ct[deleted] == 0) color_to_ct.erase(deleted);

    ll added = cs[i];
    color_to_ct[added]++;

    chmax(res, (ll)color_to_ct.size());
  }

  cout << res << "\n";
}
