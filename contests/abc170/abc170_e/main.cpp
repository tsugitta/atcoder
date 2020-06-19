// https://atcoder.jp/contests/abc170/tasks/abc170_e

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
  ll N, Q;
  cin >> N >> Q;

  // 園児： p (person)
  // 幼稚園： f (facility)

  ll f_ct = 2 * 1e5;

  VL p_rates(N);
  VL p_to_f(N);
  V<multiset<ll>> f_rates(f_ct);
  multiset<ll> maxes;

  rep(i, N) {
    ll a, b;
    cin >> a >> b;
    --b;

    p_rates[i] = a;
    p_to_f[i] = b;
    f_rates[b].insert(a);
  }

  rep(i, f_ct) {
    if (f_rates[i].size()) {
      ll max = *f_rates[i].rbegin();
      maxes.insert(max);
    }
  }

  rep(i, Q) {
    ll c, d;
    cin >> c >> d;
    --c, --d;
    ll rate = p_rates[c];

    ll from = p_to_f[c];
    ll to = d;
    p_to_f[c] = to;

    ll from_previous_max = *f_rates[from].rbegin();
    maxes.erase(maxes.find(from_previous_max));

    if (f_rates[to].size()) {
      ll to_previous_max = *f_rates[to].rbegin();
      maxes.erase(maxes.find(to_previous_max));
    }

    f_rates[from].erase(f_rates[from].find(rate));
    f_rates[to].insert(rate);

    if (f_rates[from].size()) {
      maxes.insert(*f_rates[from].rbegin());
    }

    maxes.insert(*f_rates[to].rbegin());

    cout << *maxes.begin() << "\n";
  }
}
