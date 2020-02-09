// https://atcoder.jp/contests/abc089/tasks/abc089_d

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
inline bool chmax(T& a, T b);
template <typename T>
inline bool chmin(T& a, T b);
void print_ints(vector<ll> v);
template <typename T>
void drop(T a);

const ll INF = 1e18;

void solve() {
  ll H, W, D;
  cin >> H >> W >> D;

  VL num_to_h(H * W + 1);
  VL num_to_w(H * W + 1);

  rep(h, H) rep(w, W) {
    ll val;
    cin >> val;

    num_to_h[val] = h;
    num_to_w[val] = w;
  }

  VVL rem_acc(D + 1, VL(0));

  rep1(first, D) {
    ll cur = first;
    ll acc = 0;

    rem_acc[first].emplace_back(acc);

    while (cur + D <= H * W) {
      ll next = cur + D;
      ll cost = abs(num_to_h[cur] - num_to_h[next]) +
                abs(num_to_w[cur] - num_to_w[next]);
      acc += cost;
      rem_acc[first].emplace_back(acc);
      cur = next;
    }
  }

  ll Q;
  cin >> Q;

  rep(i, Q) {
    ll L, R;
    cin >> L >> R;

    ll first = L % D == 0 ? D : L % D;
    ll l_index = (L - first) / D;
    ll r_index = (R - first) / D;

    ll res = rem_acc[first][r_index] - rem_acc[first][l_index];
    cout << res << endl;
  }
}

void solve2() {
  ll H, W, D;
  cin >> H >> W >> D;

  VL num_to_h(H * W + 1);
  VL num_to_w(H * W + 1);

  rep(h, H) rep(w, W) {
    ll val;
    cin >> val;

    num_to_h[val] = h;
    num_to_w[val] = w;
  }

  VL acc(H * W + 1);
  rep1(num, H * W) {
    unless(num + D <= H * W) continue;

    ll cost = abs(num_to_h[num] - num_to_h[num + D]) +
              abs(num_to_w[num] - num_to_w[num + D]);
    acc[num + D] = acc[num] + cost;
  }

  ll Q;
  cin >> Q;

  rep(i, Q) {
    ll L, R;
    cin >> L >> R;

    ll res = acc[R] - acc[L];

    cout << res << endl;
  }
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
