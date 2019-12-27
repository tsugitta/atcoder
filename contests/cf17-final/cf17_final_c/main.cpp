// https://atcoder.jp/contests/cf17-final/tasks/cf17_final_c

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

  VL ds(N);

  map<ll, ll> cts;
  cts[0]++;

  rep(i, N) {
    ll d;
    cin >> d;

    ds[i] = d;
    cts[d]++;
  }

  if (cts[0] >= 2 || cts[12] >= 2) drop(0);
  rep1(i, 11) if (cts[i] >= 3) drop(0);

  ll res = 0;

  rep(bit, (1ll << 12) - 1) {
    VL ts(0);

    if (cts[0] > 0) ts.push_back(0);
    if (cts[12] > 0) ts.push_back(12);

    rep1(time, 11) {
      if (cts[time] == 0) continue;

      if (cts[time] == 2) {
        ts.push_back(time);
        ts.push_back(24-time);
        continue;
      }

      ll mask = 1ll << (time - 1);
      if ((bit & mask) == mask) {
        // 右側
        ts.push_back(time);
      } else {
        // 左側
        ts.push_back(24 - time);
      }
    }

    ll min_d = INF;

    rep(j, ts.size()) rep(i, j) {
      ll t_diff = abs(ts[i] - ts[j]);
      ll d = min(t_diff, 24- t_diff);
      chmin(min_d, d);
    }

    chmax(res, min_d);
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
