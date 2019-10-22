// https://atcoder.jp/contests/arc092/tasks/arc092_a

#include "algorithm"
#include "iostream"
#include "queue"
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

struct BipartiteMatching {
  vector<vector<ll>> edges;
  vector<ll> match;
  vector<bool> used;

  BipartiteMatching(ll n)
      : edges(vector<vector<ll>>(n)), match(vector<ll>(n, -1)) {}

  void add(ll from, ll to) {
    edges[from].push_back(to);
    edges[to].push_back(from);
  }

  bool dfs(ll v) {
    used[v] = true;

    for (auto u : edges[v]) {
      ll w = match[u];
      if (w == -1 || !used[w] && dfs(w)) {
        match[u] = v;
        match[v] = u;
        return true;
      }
    }

    return false;
  }

  ll call() {
    ll res = 0;

    rep(v, edges.size()) {
      if (match[v] == -1) {
        used = vector<bool>(edges.size());

        if (dfs(v)) {
          res++;
        }
      }
    }

    return res;
  }
};

void solve() {
  ll N;
  cin >> N;

  VPL reds(N);
  rep(i, N) {
    ll x, y;
    cin >> x >> y;
    reds[i] = {x, y};
  }

  VPL blues(N);
  rep(i, N) {
    ll x, y;
    cin >> x >> y;
    blues[i] = {x, y};
  }

  auto bm = BipartiteMatching(2 * N);

  rep(r, N) rep(b, N) {
    if (reds[r].first < blues[b].first && reds[r].second < blues[b].second) {
      bm.add(r, b + N);
    }
  }

  ll res = bm.call();
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
