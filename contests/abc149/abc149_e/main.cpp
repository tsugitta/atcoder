// https://atcoder.jp/contests/abc149/tasks/abc149_e

#include "algorithm"
#include "bitset"
#include "cmath"
#include "complex"
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
  ll N, M;
  cin >> N >> M;

  VL as(N);
  rep(i, N) cin >> as[i];

  sort(all(as));

  VL acc(N + 1);
  rep(i, N) acc[i + 1] = acc[i] + as[i];

  // 合計値 a が上位 M に含まれるか
  auto is_ok = [&](ll a) -> bool {
    ll a_over_ct = 0;

    rep(i, N) {
      ll pair_limit_i = upper_bound(all(as), a - as[i]) - as.begin();
      a_over_ct += N - pair_limit_i;
    }

    return a_over_ct < M;
  };

  ll ng = 0;
  ll ok = 2 * as[N - 1];

  while (ok - ng > 1) {
    ll mid = (ok + ng) / 2;

    if (is_ok(mid)) {
      ok = mid;
    } else {
      ng = mid;
    }
  }

  ll res = 0;
  ll added = 0;

  rep(i, N) {
    ll limit_i = lower_bound(all(as), ok - as[i]) - as.begin();
    ll ct = N - limit_i;
    added += ct;
    res += acc[N] - acc[limit_i];
    res += as[i] * ct;
  }

  res -= ok * (added - M);

  cout << res << endl;
}

// 尺取
void solve2() {
  ll N, M;
  cin >> N >> M;

  VL as(N);
  rep(i, N) cin >> as[i];

  sort(all(as));

  VL acc(N + 1);
  rep(i, N) acc[i + 1] = acc[i] + as[i];

  auto is_ok = [&](ll a) -> bool {
    ll a_over_ct = 0;

    ll pair_limit_i = N;
    rep(i, N) {
      while (pair_limit_i > 0 && as[i] + as[pair_limit_i - 1] > a) {
        pair_limit_i--;
      }

      a_over_ct += N - pair_limit_i;
    }

    return a_over_ct < M;
  };

  ll ng = 0;
  ll ok = 2 * as[N - 1];

  while (ok - ng > 1) {
    ll mid = (ok + ng) / 2;

    if (is_ok(mid)) {
      ok = mid;
    } else {
      ng = mid;
    }
  }

  ll res = 0;
  ll added = 0;

  ll pair_limit_i = N;

  rep(i, N) {
    while (pair_limit_i > 0 && as[i] + as[pair_limit_i - 1] >= ok) {
      pair_limit_i--;
    }

    ll ct = N - pair_limit_i;
    added += ct;
    res += acc[N] - acc[pair_limit_i];
    res += as[i] * ct;
  }

  res -= ok * (added - M);

  cout << res << endl;
}

// FFT borrowed from tsutaj-san
using Complex = complex<double>;
vector<Complex> dft(vector<Complex> A, int N, int sgn = 1) {
  if (N == 1) return A;

  vector<Complex> F(N / 2), G(N / 2);
  for (int i = 0; i < N / 2; i++) {
    F[i] = A[2 * i + 0];
    G[i] = A[2 * i + 1];
  }

  F = dft(F, N / 2, sgn);
  G = dft(G, N / 2, sgn);

  Complex zeta(cos(2.0 * M_PI / N), sin(2.0 * M_PI / N) * sgn);
  Complex pow_zeta = 1;

  for (int i = 0; i < N; i++) {
    A[i] = F[i % (N / 2)] + pow_zeta * G[i % (N / 2)];
    pow_zeta *= zeta;
  }
  return A;
}

vector<Complex> inv_dft(vector<Complex> A, int N) {
  A = dft(A, N, -1);
  for (int i = 0; i < N; i++) {
    A[i] /= N;
  }
  return A;
}

vector<Complex> multiply(vector<Complex> A, vector<Complex> B) {
  int sz = A.size() + B.size() + 1;
  int N = 1;
  while (N < sz) N *= 2;

  A.resize(N), B.resize(N);
  A = dft(A, N);
  B = dft(B, N);

  vector<Complex> F(N);
  for (int i = 0; i < N; i++) {
    F[i] = A[i] * B[i];
  }
  return inv_dft(F, N);
}

void solve3() {
  ll N, M;
  cin >> N >> M;

  V<Complex> vs(1e5 + 1);

  rep(i, N) {
    ll a;
    cin >> a;
    vs[a] += 1;
  }

  V<Complex> m = multiply(vs, vs);

  ll rest = M;
  ll res = 0;

  repr(num, m.size()) {
    ll ct = m[num].real() + 0.5;

    if (ct > 0) {
      ll can = min(ct, rest);
      res += num * can;
      rest -= can;
    }

    if (rest == 0) break;
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
