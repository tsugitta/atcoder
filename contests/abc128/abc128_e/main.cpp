// https://atcoder.jp/contests/abc128/tasks/abc128_e

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

// type: 0: delete, 1: insert, 2: query
// f: (f: time, s: type), s: x
using event = P<PL, ll>;

void solve() {
  ll N, Q;
  cin >> N >> Q;

  V<event> es;

  rep(i, N) {
    ll s, t, x;
    cin >> s >> t >> x;
    es.emplace_back(PL(s - x, 1), x);
    es.emplace_back(PL(t - x, 0), x);
  }

  rep(i, Q) {
    ll d;
    cin >> d;
    es.emplace_back(PL(d, 2), 0);  // second は使わない
  }

  sort(es.begin(), es.end());

  VL res;
  multiset<ll> se;

  for (auto p : es) {
    ll tx = p.first.first;
    ll type = p.first.second;
    ll x = p.second;

    if (type == 0)
      se.erase(x);
    else if (type == 1)
      se.insert(x);
    else
      res.push_back(se.empty() ? -1 : *(se.begin()));
  }

  for (auto r : res) cout << r << endl;
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
