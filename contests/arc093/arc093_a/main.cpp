// https://atcoder.jp/contests/arc093/tasks/arc093_a

#include "algorithm"
#include "iostream"
#include "set"
#include "vector"
#define rep(i, from, to) for (ll i = from; i < (to); ++i)
using namespace std;
typedef long long ll;
template <typename T>
using V = vector<T>;
template <typename T>
inline bool chmax(T& a, T b);
template <typename T>
inline bool chmin(T& a, T b);
void print_ints(vector<ll> v);
template <typename T>
void drop(T a);

ll N;
V<ll> as;

void solve() {
  cin >> N;
  as.resize(N + 2);
  as[0] = 0;
  as[N + 1] = 0;
  rep(i, 0, N) cin >> as[i + 1];

  V<ll> acc(N + 2);
  acc[0] = 0;

  rep(i, 1, N + 2) { acc[i] = acc[i - 1] + abs(as[i] - as[i - 1]); }

  rep(i, 1, N + 1) {
    ll add = abs(as[i + 1] - as[i - 1]);
    ll res = acc[i - 1] + (acc[N + 1] - acc[i + 1]) + add;
    cout << res << endl;
  }
}

void solve2() {
  cin >> N;
  as.resize(N);
  rep(i, 0, N) cin >> as[i];

  V<ll> acc(N + 2);  // acc[i]: 0 から i 番目までの累積和. acc[1]: 番目まで、
                     // acc[N+1]: 0 に戻ってくるまで
  acc[0] = 0;

  rep(i, 0, N + 1) {
    ll prev = i == 0 ? 0 : as[i - 1];
    ll curr = i == N ? 0 : as[i];

    acc[i + 1] = acc[i] + abs(curr - prev);
  }

  rep(i, 0, N) {
    ll add = i == 0 ? abs(as[1])
                    : i == N - 1 ? abs(as[N - 2]) : abs(as[i + 1] - as[i - 1]);
    ll res = (acc[i]) + (acc[N + 1] - acc[i + 2]) + add;
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
  rep(i, 0, v.size()) {
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
