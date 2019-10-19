// https://atcoder.jp/contests/dp/tasks/dp_g

#include "algorithm"
#include "iostream"
#include "set"
#include "vector"
#define rep(i, from, to) for (ll i = from; i < (to); ++i)
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

VL ls;  // そのノードから出る最長パス
VVL edges;

ll get_longest(ll u) {
  if (ls[u] > 0) {
    return ls[u];
  }

  ll max = -1;

  for (auto v : edges[u]) {
    chmax(max, get_longest(v));
  }

  ll res = 1 + max;
  ls[u] = res;

  return res;
}

void solve() {
  ll N, M;
  cin >> N >> M;

  edges.assign(N, VL(0));

  rep(i, 0, M) {
    ll from, to;
    cin >> from >> to;
    from--;
    to--;
    edges[from].push_back(to);
  }

  ls.assign(N, -1);

  ll res = 0;
  rep(i, 0, N) { chmax(res, get_longest(i)); }

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
