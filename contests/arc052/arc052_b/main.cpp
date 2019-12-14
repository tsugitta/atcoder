// https://atcoder.jp/contests/arc052/tasks/arc052_b

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
const double PI = 3.14159265358979323846;

void solve() {
  ll N, Q;
  cin >> N >> Q;

  struct Cone {
    double x;
    double r;
    double h;
  };

  V<Cone> cs(N);

  rep(i, N) {
    double x, r, h;
    cin >> x >> r >> h;
    cs[i] = Cone{x, r, h};
  }

  auto query = [&](ll a, ll b) -> double {
    double res = 0;

    for (auto c : cs) {
      if (c.x + c.h <= a || b <= c.x) continue;

      double original_v = PI * c.r * c.r * c.h / 3;
      double v = original_v;

      if (c.x < a) {
        double extra = original_v * (1 - pow((c.x + c.h - a) / c.h, 3));
        v -= extra;
      }

      if (c.x + c.h > b) {
        double extra = original_v * pow((c.x + c.h - b) / c.h, 3);
        v -= extra;
      }

      res += v;
    }

    return res;
  };

  cout << fixed << setprecision(6);

  rep(i, Q) {
    ll a, b;
    cin >> a >> b;

    double res = query(a, b);
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
