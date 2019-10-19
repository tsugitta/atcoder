// https://atcoder.jp/contests/abc143/tasks/abc143_f

#include "algorithm"
#include "iostream"
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
template <typename T>
inline bool chmax(T& a, T b);
template <typename T>
inline bool chmin(T& a, T b);
void print_ints(vector<ll> v);
template <typename T>
void drop(T a);

// O(N log^2 N)
void solve() {
  ll N;
  cin >> N;

  // 異なる数字の頻度配列を用意すると、その配列の異なる要素 K 個を 1
  // 減らせる回数が答えになる。 ここで、操作回数として実現したい値を T
  // とすると、同じ要素はたかだか T 個しか使用できないから、それを T
  // に置き換えて良い。この時、変換後の配列の和が T*K 以上であれば、 T
  // 回取ることができる。
  //
  // 帰納的に証明できる。和がちょうど T*K の時にこれが満たせることを示せば十分。
  // T = 1 で前提が満たされている時、和が K であって、最大の要素数が 1 だから、
  // 要素は K 種類ある。よって 1 回 K 個取ることができる。
  //
  // T = l で前提が満たされている時、最大の要素数が l のものが K+1
  // 個以上あるとすると、和が l*(K+1) 以上となり、 l*K であることと矛盾。
  // よって要素数が l のものは高々 K 個。そこで、要素数が l
  // のものを全て含むように K 個取ることとすると、 和は (l-1)*K
  // となり、最大の要素数は高々 l-1 となる。 よって、 T = l
  // で前提が満たされている時、 T = l-1 で前提を満たすように取ることができる。
  //
  // 以上より、ある数 T についてそれが可能な回数かどうかの判定が可能。
  // また、 T には単調性があるため、二分探索で求めることができる。

  // 数値の頻度配列
  VL as(N, 0);

  rep(i, N) {
    ll x;
    cin >> x;
    as[x - 1]++;
  }

  sort(as.begin(), as.end());

  auto sums = VL(N + 1);  // sum [0, i)
  rep(i, N) sums[i + 1] = sums[i] + as[i];

  repf(k, 1, N + 1) {
    ll ok = 0;
    ll ng = N / k + 1;

    while (ng - ok > 1) {
      ll m = (ok + ng) / 2;

      auto satisfied = [&](ll c) {
        ll i = lower_bound(as.begin(), as.end(), c) - as.begin();
        ll sum = c * (N - i) + sums[i];

        return sum >= c * k;
      };

      if (satisfied(m))
        ok = m;
      else
        ng = m;
    }

    cout << ok << endl;
  }
}

// O(N log N)
void solve2() {
  ll N;
  cin >> N;

  // 二分探索のボーダーが単調に推移するため、毎回二分探索するのでなく、しゃくとり法的なアプローチをとることができる。

  // 数値の頻度配列
  VL as(N, 0);

  rep(i, N) {
    ll x;
    cin >> x;
    as[x - 1]++;
  }

  sort(as.begin(), as.end());

  auto sums = VL(N + 1);  // sum [0, i)
  rep(i, N) sums[i + 1] = sums[i] + as[i];

  ll res = N;

  repf(k, 1, N + 1) {
    while (1) {
      auto satisfied = [&](ll c) {
        ll i = lower_bound(as.begin(), as.end(), c) - as.begin();
        ll sum = c * (N - i) + sums[i];

        return sum >= c * k;
      };

      if (satisfied(res)) break;
      --res;
    }

    cout << res << endl;
  }
}

// O(N)
void solve3() {
  ll N;
  cin >> N;

  // 数値の頻度配列
  VL as(N, 0);

  rep(i, N) {
    ll x;
    cin >> x;
    as[x - 1]++;
  }

  sort(as.begin(), as.end());

  auto sums = VL(N + 1);  // sum [0, i)
  rep(i, N) sums[i + 1] = sums[i] + as[i];

  ll res = N;
  ll i = N;

  repf(k, 1, N + 1) {
    while (1) {
      auto satisfied = [&](ll c) {
        while (i >= 0 && as[i - 1] >= c) --i;
        ll sum = c * (N - i) + sums[i];

        return sum >= c * k;
      };

      if (satisfied(res)) break;
      --res;
    }

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
    solve3();
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
