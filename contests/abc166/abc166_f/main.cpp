// https://atcoder.jp/contests/abc166/tasks/abc166_f

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

void solve() {
  ll N;
  map<char, ll> ct;
  cin >> N >> ct['A'] >> ct['B'] >> ct['C'];

  V<string> ops(N);

  rep(i, N) cin >> ops[i];

  V<char> res(0);

  auto move = [&](char dest, char src) {
    ct[dest] += 1;
    ct[src] -= 1;
    res.push_back(dest);
  };

  auto handle = [&](char x, char y, ll index) {
    if (ct[x] == 0 && ct[y] == 0) drop("No");

    if (ct[x] < ct[y]) {
      move(x, y);
      return;
    }

    if (ct[x] > ct[y] || index == N - 1) {
      move(y, x);
      return;
    }

    if (ops[index + 1].find(x) != string::npos) {
      move(x, y);
    } else {
      move(y, x);
    }
  };

  rep(i, N) {
    string o = ops[i];
    handle(o[0], o[1], i);
  }

  cout << "Yes"
       << "\n";

  rep(i, N) cout << res[i] << "\n";
}
