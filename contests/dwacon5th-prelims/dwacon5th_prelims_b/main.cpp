// https://atcoder.jp/contests/dwacon5th-prelims/tasks/dwacon5th_prelims_b

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

int msb(int bits) {
  int num = 0;

  for (; bits != 0; bits &= bits - 1) {
    num++;
  }

  return num;
}

void solve() {
  ll N, K;
  cin >> N >> K;

  VL as(N);
  rep(i, N) cin >> as[i];

  VL acc(N + 1);
  rep(i, N) { acc[i + 1] = as[i] + acc[i]; }

  VL vs(0);

  ll max_v = 0;
  // [i, j)
  rep(j, N + 1) rep(i, j) {
    ll v = acc[j] - acc[i];
    vs.push_back(v);
    chmax(max_v, v);
  }

  V<bool> is_cand(vs.size(), true);

  ll msb = 0;
  while (max_v != 0) {
    max_v /= 2;
    msb++;
  }

  repr(i, msb) {
    ll mask = 1ll << i;

    set<ll> indices;
    rep(j, vs.size()) {
      if (is_cand[j] && (vs[j] & mask) == mask) {
        indices.insert(j);
      }
    }

    if (indices.size() >= K) {
      rep(j, vs.size()) {
        if (indices.count(j) == 0) is_cand[j] = false;
      }
    }
  }

  ll res = (1ll << 60) - 1;

  rep(i, vs.size()) {
    if (is_cand[i]) res &= vs[i];
  }

  cout << res << endl;
}

void solve2() {
  ll N, K;
  cin >> N >> K;

  VL as(N);
  rep(i, N) cin >> as[i];

  VL acc(N + 1);
  rep(i, N) { acc[i + 1] = as[i] + acc[i]; }

  VL vs(0);

  ll max_v = 0;
  // [i, j)
  rep(j, N + 1) rep(i, j) {
    ll v = acc[j] - acc[i];
    vs.push_back(v);
    chmax(max_v, v);
  }

  ll msb = 0;
  while (max_v != 0) {
    max_v /= 2;
    msb++;
  }

  ll res = 0;

  repr(i, msb) {
    ll mask = 1ll << i;

    ll ct = 0;

    rep(j, vs.size()) {
      ll comp = res | mask;
      if ((vs[j] & comp) == comp) {
        ct++;
      }
    }

    if (ct >= K) {
      res |= mask;
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
    solve2();
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
