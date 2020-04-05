// https://atcoder.jp/contests/abc161/tasks/abc161_e

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

struct exit_exception : public std::exception {
  const char* what() const throw() { return "Exited"; }
};

template <typename T>
void drop(T res) {
  cout << res << endl;
  throw exit_exception();
}

const ll INF = 1e18;

void solve() {
  ll N, K, C;
  string S;
  cin >> N >> K >> C >> S;

  VL front(N, -1);

  {
    ll worked = 0;

    rep(i, N) {
      if (S[i] == 'x') continue;

      front[i] = worked;
      ++worked;
      if (worked == K) break;
      i += C;
    }
  }

  VL back(N, -1);

  {
    ll worked = K - 1;

    repr(i, N) {
      if (S[i] == 'x') continue;

      back[i] = worked;
      --worked;
      if (worked == -1) break;
      i -= C;
    }
  }

  rep(i, N) {
    if (front[i] != -1 && front[i] == back[i]) {
      cout << i + 1 << "\n";
    }
  }
}

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
