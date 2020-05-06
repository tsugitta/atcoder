// https://atcoder.jp/contests/past202004-open/tasks/past202004_f

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
  ll N;
  cin >> N;

  VVL tasks(N, VL(0));  // tasks[i]: i 日目以降に着手できる task のポイント

  rep(i, N) {
    ll a, b;
    cin >> a >> b;
    a--;
    tasks[a].emplace_back(b);
  }

  priority_queue<ll> q;

  ll cur = 0;

  rep(i, N) {
    for (ll b : tasks[i]) q.push(b);
    cur += q.top();
    q.pop();
    cout << cur << "\n";
  }
}

void solve2() {
  ll N;
  cin >> N;

  VVL tasks(N, VL(0));  // tasks[i]: i 日目以降に着手できる task のポイント

  ll max_b = 0;

  rep(i, N) {
    ll a, b;
    cin >> a >> b;
    a--;
    tasks[a].emplace_back(b);
    chmax(max_b, b);
  }

  VL can_use_ct(max_b + 1);

  ll cur = 0;

  rep(i, N) {
    for (ll b : tasks[i]) can_use_ct[b]++;

    ll next_b = -1;
    rep1(b, max_b) if (can_use_ct[b]) chmax(next_b, b);
    cur += next_b;
    can_use_ct[next_b]--;
    cout << cur << "\n";
  }
}
