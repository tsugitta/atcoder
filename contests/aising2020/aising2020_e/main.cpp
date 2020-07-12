// https://atcoder.jp/contests/aising2020/tasks/aising2020_e

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
  ll T;
  cin >> T;

  auto solve_case = []() {
    ll N;
    cin >> N;

    struct Camel {
      ll K, diff, min;
    };

    // priority_queue で diff の昇順で取り出すようにする
    //（大きい時に true が返る compare を用意しないといけない）
    struct CompareCamel {
      bool operator()(Camel const& lhs, Camel const& rhs) {
        return lhs.diff > rhs.diff;
      }
    };

    V<Camel> front(0);  // L >= R
    V<Camel> back(0);   // L < R

    rep(i, N) {
      ll K, L, R;
      cin >> K >> L >> R;

      if (L >= R) {
        front.push_back({K, L - R, min(L, R)});
      } else {
        // 「後ろから何番目」に変換
        back.push_back({N - K, R - L, min(L, R)});
      }
    }

    auto solve_partial = [&](V<Camel>& camels) -> ll {
      ll res = 0;
      ll camel_ct = camels.size();
      for (auto& c : camels) res += c.min;

      map<ll, V<Camel>> k_to_camel;

      for (auto& c : camels) {
        ll k = min(c.K, camel_ct);
        k_to_camel[k].push_back(c);
      }

      priority_queue<Camel, V<Camel>, CompareCamel> q;

      rep1(i, camel_ct) {
        for (auto& c : k_to_camel[i]) q.push(c);
        while (q.size() > i) q.pop();
      }

      while (q.size()) {
        auto c = q.top();
        res += c.diff;
        q.pop();
      }

      return res;
    };

    ll res = solve_partial(front) + solve_partial(back);
    cout << res << "\n";
  };

  rep(i, T) solve_case();
}
