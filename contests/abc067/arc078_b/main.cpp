// https://atcoder.jp/contests/abc067/tasks/arc078_b

#include "algorithm"
#include "cmath"
#include "functional"
#include "iomanip"
#include "iostream"
#include "numeric"
#include "queue"
#include "set"
#include "string"
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

const ll INF = 1e18;

void solve() {
  ll N;
  cin >> N;

  VVL edgeList(N, VL(0));

  rep(i, N - 1) {
    ll a, b;
    cin >> a >> b;
    a--, b--;
    edgeList[a].push_back(b);
    edgeList[b].push_back(a);
  }

  VL colors(N, -1);  // B: 0, W: 1
  colors[0] = 0;
  colors[N - 1] = 1;

  queue<ll> bq;
  bq.push(0);
  queue<ll> wq;
  wq.push(N - 1);

  while (!bq.empty() || !wq.empty()) {
    auto rec = [&](queue<ll>& q, ll color) {
      if (q.empty()) return;

      queue<ll> next_q;

      while (!q.empty()) {
        ll next = q.front();
        q.pop();

        for (auto to : edgeList[next]) {
          if (colors[to] != -1) continue;
          colors[to] = color;
          next_q.push(to);
        }
      }

      q = next_q;
    };

    rec(bq, 0);
    rec(wq, 1);
  }

  ll bct = 0, wct = 0;
  for (auto c : colors) {
    if (c == 0)
      bct++;
    else
      wct++;
  }

  if (bct <= wct) {
    cout << "Snuke" << endl;
  } else {
    cout << "Fennec" << endl;
  }
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
