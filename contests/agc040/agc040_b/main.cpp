// https://atcoder.jp/contests/agc040/tasks/agc040_b

#include "algorithm"
#include "iostream"
#include "numeric"
#include "queue"
#include "set"
#include "vector"
#define rep(i, to) for (ll i = 0; i < (to); ++i)
#define repf(i, from, to) for (ll i = from; i < (to); ++i)
#define repr(i, from) for (ll i = from - 1; i >= 0; --i)
#define all(vec) vec.begin(), vec.end()
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

void solve() {
  ll N;
  cin >> N;

  ll max_l = 0;
  ll min_r = 1e18;

  VPL originals(N);
  rep(i, N) {
    ll l, r;
    cin >> l >> r;
    // [l, r)
    r++;
    originals[i] = {l, r};
    chmax(max_l, l);
    chmin(min_r, r);
  }

  ll res = 0;

  // max_l, min_r を与えるものを同一グループにするケース
  {
    for (auto p : originals) {
      chmax(res, max(min_r - max_l, 0ll) + p.se - p.fi);
    }
  }

  // max_l, min_r を与えるものを同一グループにしないケース
  {
    VPL ps(N);  // f: max(r_i - max_l, 0), s: max(min_r - l_i, 0)

    // s, t の 2 グループに分ける
    // s には max_l を与えるものを、t には min_r を与えるものを入れる
    // s グループの値は min(max(p.second - max_l, 0))
    // t グループの値は min(max(min_r - p.first, 0))
    // となる。
    // 上記２つの値を持った pair N 個を 2 グループに分け、 s については first, t
    // については second の min を取る
    rep(i, N) {
      ps[i] = {
          max(originals[i].se - max_l, 0ll),
          max(min_r - originals[i].fi, 0ll),
      };
    }

    // s について fi の min が x だったとすると、
    // fi が x 以上のものを s に入れても min は変わらないが
    // t に入れると se の min が小さくなり得る。
    // よって fi が x 以上のものは全て s に入れるのが最善。
    // よって fi で昇順に並び替えた時、 s
    // には後ろの連続した要素を入れることを考えれば良い。
    sort(all(ps));

    ll min_t = 1e18;

    rep(i, N - 1) {
      PL new_t = ps[i];

      chmin(min_t, new_t.se);
      ll min_s = ps[i + 1].fi;

      chmax(res, min_t + min_s);
    }
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
