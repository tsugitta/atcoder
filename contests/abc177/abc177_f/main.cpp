// https://atcoder.jp/contests/abc177/tasks/abc177_f

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
inline bool chmax(T &a, T b) {
  if (a < b) {
    a = b;
    return 1;
  }
  return 0;
}

template <typename T>
inline bool chmin(T &a, T b) {
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
  const char *what() const throw() { return "Exited"; }
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
  } catch (exit_exception &e) {
  }

  return 0;
}
#endif

void solve() {
  ll H, W;
  cin >> H >> W;

  map<int, int> pos_to_start;
  multiset<int> min_steps;

  rep(w, W) {
    pos_to_start[w] = w;
    min_steps.insert(0);
  }

  rep(h, H) {
    ll l, r;
    cin >> l >> r;
    --l;

    auto it = pos_to_start.lower_bound(l);

    int most_right = -1;

    while (it != pos_to_start.end()) {
      auto [pos, start] = *it;
      unless(pos <= r) break;

      chmax(most_right, start);
      int diff = pos - start;
      min_steps.erase(min_steps.find(diff));
      pos_to_start.erase(it++);
    }

    if (most_right != -1 && r < W) {
      min_steps.insert(r - most_right);
      pos_to_start[r] = most_right;
    }

    int res = -1;
    if (min_steps.size() > 0) {
      res = *min_steps.begin() + (h + 1);
    }

    cout << res << "\n";
  }
}
