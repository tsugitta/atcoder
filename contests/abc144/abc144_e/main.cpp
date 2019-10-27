// https://atcoder.jp/contests/abc144/tasks/abc144_e

#include "algorithm"
#include "iostream"
#include "queue"
#include "set"
#include "vector"
#define rep(i, to) for (ll i = 0; i < (to); ++i)
#define repf(i, from, to) for (ll i = from; i < (to); ++i)
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
  ll N, K;
  cin >> N >> K;
  VL as(N);
  rep(i, N) cin >> as[i];
  VL fs(N);
  rep(i, N) cin >> fs[i];

  sort(as.begin(), as.end());
  sort(fs.rbegin(), fs.rend());

  ll ng = -1;
  ll ok = 1e18;

  while (ok - ng > 1) {
    ll mid = (ok + ng) / 2;
    ll rest = K;
    ll failed = false;

    rep(i, N) {
      ll target = mid / fs[i];  // A は target 以下にならないといけない

      ll diff = as[i] - target;
      if (diff < 0) continue;
      if (diff > rest) {
        failed = true;
        break;
      }

      rest -= diff;
    }

    if (failed) {
      ng = mid;
    } else {
      ok = mid;
    }
  }

  cout << ok << endl;
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
