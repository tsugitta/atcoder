// https://atcoder.jp/contests/nikkei2019-qual/tasks/nikkei2019_qual_d

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

  VVL edges(N, VL(0));
  VL in_counts(N);

  rep(i, N - 1 + M) {
    ll a, b;
    cin >> a >> b;
    a--, b--;

    edges[a].push_back(b);
    in_counts[b]++;
  }

  ll root = -1;
  rep(i, N) if (in_counts[i] == 0) root = i;

  VL parents(N, -1);

  queue<ll> q;
  q.push(root);

  while (!q.empty()) {
    ll u = q.front();
    q.pop();

    for (ll v : edges[u]) {
      parents[v] = u;
      in_counts[v]--;

      if (in_counts[v] == 0) q.push(v);
    }
  }

  rep(i, N) cout << (i == root ? 0 : parents[i] + 1) << endl;
}

struct TopologicalSort {
  VVL edges;
  VL sorted, length;

  TopologicalSort(ll n) : edges(VVL(n, VL(0))), length(VL(n, 1)) {}

  void add(ll from, ll to) { edges[from].push_back(to); }

  // 戻り値: isLoop
  bool sort() {
    ll n = edges.size();
    VL in_count(n);

    rep(i, n) {
      for (auto to : edges[i]) in_count[to]++;
    }

    set<ll> in_count_zeros;

    rep(i, n) {
      if (in_count[i] == 0) in_count_zeros.insert(i);
    }

    VL res(0);

    while (in_count_zeros.size() > 0) {
      ll popped = *in_count_zeros.begin();

      res.push_back(popped);
      in_count_zeros.erase(popped);

      for (auto to : edges[popped]) {
        chmax(length[to], length[popped] + 1);

        in_count[to]--;

        if (in_count[to] == 0) in_count_zeros.insert(to);
      }
    }

    sorted = res;

    return res.size() != edges.size();
  }
};

void solve2() {
  ll N, M;
  cin >> N >> M;

  VVL edges(N, VL(0));

  TopologicalSort ts(N);

  rep(i, N - 1 + M) {
    ll a, b;
    cin >> a >> b;
    a--, b--;

    edges[a].push_back(b);
    ts.add(a, b);
  }

  ts.sort();

  VL parents(N, -1);

  for (ll u : ts.sorted) {
    for (ll v : edges[u]) parents[v] = u;
  }

  rep(i, N) cout << (i == ts.sorted[0] ? 0 : parents[i] + 1) << endl;
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
