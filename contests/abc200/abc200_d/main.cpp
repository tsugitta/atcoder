// https://atcoder.jp/contests/abc200/tasks/abc200_d

#include <atcoder/all>

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
#define rep(i, to) for (ll i = 0; i < ((ll)to); ++i)
#define rep1(i, to) for (ll i = 1; i <= ((ll)to); ++i)
#define repf(i, from, to) for (ll i = from; i < ((ll)to); ++i)
#define repr(i, from) for (ll i = from - 1; i >= 0; --i)
#define all(vec) vec.begin(), vec.end()
#define unless(cond) if (!(cond))
#define fi first
#define se second
#define i128 __int128_t
using namespace std;
using namespace atcoder;
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
void solve2();

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

void solve() {
  ll N;
  cin >> N;

  VL as(N);
  rep(i, N) cin >> as[i];

  ll MOD = 200;

  // dp[i][rem][is_empty]: i 番目までで余りが rem の個数。
  V<VVL> dp(N + 1, VVL(MOD, VL(2)));
  dp[0][0][true] = 1;

  struct Node {
    ll i, rem, is_empty, i_is_selected;
  };

  VVV<V<Node>> prev(N + 1, VVV<Node>(MOD, VV<Node>(2)));

  rep(i, N) rep(rem, MOD) rep(is_empty, 2) {
    unless(dp[i][rem][is_empty] > 0) continue;

    rep(select_i, 2) {
      ll n_rem = select_i ? (rem + as[i]) % MOD : rem;
      bool n_is_empty = !select_i && is_empty;

      dp[i + 1][n_rem][n_is_empty] += dp[i][rem][is_empty];
      chmin(dp[i + 1][n_rem][n_is_empty], (ll)2);

      if (prev[i + 1][n_rem][n_is_empty].size() < 2) {
        prev[i + 1][n_rem][n_is_empty].push_back({i, rem, is_empty, select_i});
      }
    }
  }

  auto get_res_indices = [&](ll index, ll rem, bool is_empty,
                             bool prefer_later) -> VL {
    VL res;

    ll cur_index = index;
    ll cur_rem = rem;
    bool cur_is_empty = is_empty;

    for (ll i = N; i >= 1; --i) {
      V<Node> next_indices = prev[cur_index][cur_rem][cur_is_empty];

      ll choosed_index = prefer_later ? next_indices.size() - 1 : 0;

      auto [next_index, next_rem, next_is_empty, next_i_is_selected] =
          next_indices[choosed_index];

      if (next_i_is_selected) res.push_back(next_index + 1);

      cur_index = next_index;
      cur_rem = next_rem;
      cur_is_empty = next_is_empty;
    }

    reverse(all(res));

    return res;
  };

  rep(rem, MOD) {
    if (dp[N][rem][false] == 2) {
      VL b_indices = get_res_indices(N, rem, false, false);
      VL c_indices = get_res_indices(N, rem, false, true);

      cout << "Yes"
           << "\n";

      cout << b_indices.size() << " ";
      rep(i, b_indices.size()) {
        if (i > 0) cout << " ";
        cout << b_indices[i];
      }
      cout << "\n";

      cout << c_indices.size() << " ";
      rep(i, c_indices.size()) {
        if (i > 0) cout << " ";
        cout << c_indices[i];
      }
      cout << "\n";

      throw exit_exception();
    }
  }

  cout << "No"
       << "\n";
}

void solve2() {
  ll MOD = 200;

  ll N;
  cin >> N;

  VL as(N);
  rep(i, N) cin >> as[i];

  // 先頭 8 個で全探索すれば十分
  ll M = min(N, 8ll);

  rep(b_bit, 1 << M) rep(c_bit, 1 << M) {
    if (b_bit == 0 || c_bit == 0) continue;
    if (b_bit == c_bit) continue;

    auto get_rem = [&](ll bit) {
      ll res = 0;

      rep(i, M) {
        if (bit & (1 << i)) res = (res + as[i]) % MOD;
      }

      return res;
    };

    unless(get_rem(b_bit) == get_rem(c_bit)) continue;

    auto get_res_array = [&](ll bit) {
      VL res;

      rep(i, M) {
        if (bit & (1 << i)) res.push_back(i + 1);
      }

      return res;
    };

    cout << "Yes"
         << "\n";

    VL b_res = get_res_array(b_bit);
    VL c_res = get_res_array(c_bit);

    cout << b_res.size() << " ";
    rep(i, b_res.size()) {
      if (i > 0) cout << " ";
      cout << b_res[i];
    }
    cout << "\n";

    cout << c_res.size() << " ";
    rep(i, c_res.size()) {
      if (i > 0) cout << " ";
      cout << c_res[i];
    }
    cout << "\n";

    throw exit_exception();
  }

  cout << "No"
       << "\n";
}
