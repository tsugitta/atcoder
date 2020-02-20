// https://atcoder.jp/contests/abc155/tasks/abc155_d

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
  ll N, K;
  cin >> N >> K;

  VL as(N);
  rep(i, N) cin >> as[i];

  sort(all(as));

  // X 以下の個数が K 個以上となる最小の X が答え
  ll ok = INF + 1;
  ll ng = -ok;

  // X 以下の個数が K 個以上であるか
  auto satisfied = [&](ll X) -> ll {
    ll ct = 0;

    rep(i, N) {
      ll a = as[i];

      // かけて X 以下となる数は a が正の場合左端から、 a
      // が負の場合右端から連続している その境界を二分探索で求める
      if (a < 0) {
        ll ok = N;
        ll ng = -1;

        while (ok - ng > 1) {
          ll mid = (ok + ng) / 2;
          if (a * as[mid] <= X) {
            ok = mid;
          } else {
            ng = mid;
          }
        }

        ct += N - ok;
      } else {
        ll ok = -1;
        ll ng = N;

        while (ng - ok > 1) {
          ll mid = (ok + ng) / 2;
          if (a * as[mid] <= X) {
            ok = mid;
          } else {
            ng = mid;
          }
        }

        ct += ok + 1;
      }

      // 同じ要素は選べないがカウントされているためその分減らす
      if (a * a <= X) ct--;
    }

    // 一つのペアがそれぞれの要素のカウントで二重にカウントされているため減らす
    ct /= 2;

    return ct >= K;
  };

  while (ok - ng > 1) {
    ll mid = (ok + ng) / 2;

    if (satisfied(mid)) {
      ok = mid;
    } else {
      ng = mid;
    }
  }

  cout << ok << endl;
}

void solve2() {
  ll N, K;
  cin >> N >> K;

  VL as(N);
  rep(i, N) cin >> as[i];

  sort(all(as));

  ll ok = INF + 1;
  ll ng = -ok;

  auto satisfied = [&](ll X) -> ll {
    ll ct = 0;

    rep(i, N) {
      ll a = as[i];

      // その要素より右の要素とのペアだけを加算する
      if (a < 0) {
        ll ok = N;
        ll ng = i;

        while (ok - ng > 1) {
          ll mid = (ok + ng) / 2;
          if (a * as[mid] <= X) {
            ok = mid;
          } else {
            ng = mid;
          }
        }

        ct += N - ok;
      } else {
        ll ok = i;
        ll ng = N;

        while (ng - ok > 1) {
          ll mid = (ok + ng) / 2;
          if (a * as[mid] <= X) {
            ok = mid;
          } else {
            ng = mid;
          }
        }

        ct += ok - i;
      }
    }

    return ct >= K;
  };

  while (ok - ng > 1) {
    ll mid = (ok + ng) / 2;

    if (satisfied(mid)) {
      ok = mid;
    } else {
      ng = mid;
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
