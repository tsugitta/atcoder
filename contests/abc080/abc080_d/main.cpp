// https://atcoder.jp/contests/abc080/tasks/abc080_d

#include "algorithm"
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
  ll N, C;
  cin >> N >> C;

  struct Program {
    ll s;
    ll t;
    ll c;
  };

  V<Program> ps(0);

  {
    // 同一チャンネルの連続した番組をまとめる

    V<Program> ps_original(N);

    rep(i, N) {
      ll s, t, c;
      cin >> s >> t >> c;

      ps_original[i] = {s, t, c};
    }

    sort(all(ps_original), [](Program a, Program b) {
      if (a.c != b.c) return a.c < b.c;
      return a.s < b.s;
    });

    rep(i, N) {
      auto p = ps_original[i];

      if (ps.size() > 0) {
        auto last_p = ps[ps.size() - 1];

        if (last_p.c == p.c && last_p.t == p.s) {
          ps[ps.size() - 1].t = p.t;
          continue;
        }
      }

      ps.push_back(p);
    }
  }

  sort(all(ps), [](Program a, Program b) { return a.s < b.s; });

  ll res = 0;
  ll available = 0;
  priority_queue<ll, VL, greater<ll>> add_event;  // 追加する時刻

  for (auto p : ps) {
    while (!add_event.empty() && add_event.top() <= p.s) {
      add_event.pop();
      available++;
    }

    if (available == 0) {
      res++;
    } else {
      available--;
    }

    add_event.push(p.t + 1);
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
