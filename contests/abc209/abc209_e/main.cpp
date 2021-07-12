// https://atcoder.jp/contests/abc209/tasks/abc209_e

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
  ll N;
  cin >> N;

  ll CHAR_CT = 52;
  ll SIZE = pow(CHAR_CT, 3);

  V<string> words(N);
  rep(i, N) cin >> words[i];

  auto char_to_int = [](char c) -> ll {
    if (isupper(c)) return c - 'A';
    return c - 'a' + 26;
  };

  auto string_to_int = [&](char a, char b, char c) {
    return char_to_int(a) * 52 * 52 + char_to_int(b) * 52 + char_to_int(c);
  };

  auto id_to_head = [&](ll id) {
    string w = words[id];
    return string_to_int(w[0], w[1], w[2]);
  };

  auto id_to_tail = [&](ll id) {
    string w = words[id];
    ll len = w.size();
    return string_to_int(w[len - 3], w[len - 2], w[len - 1]);
  };

  VVL head_num_to_ids(SIZE);
  rep(i, N) head_num_to_ids[id_to_head(i)].push_back(i);

  VVL tail_num_to_ids(SIZE);
  rep(i, N) tail_num_to_ids[id_to_tail(i)].push_back(i);

  VVL edge_list(N);
  VVL rev_edge_list(N);

  VL out_cts(N);

  rep(i, N) {
    ll head = id_to_head(i);

    for (ll j : tail_num_to_ids[head]) {
      rev_edge_list[i].push_back(j);
      edge_list[j].push_back(i);
      out_cts[j]++;
    }
  }

  ll DRAW = -1;
  ll LOSE = 0;
  ll WIN = 1;

  VL res(N, DRAW);

  queue<ll> q;

  rep(i, N) if (out_cts[i] == 0) {
    q.push(i);
    res[i] = WIN;
  }

  while (q.size()) {
    ll u = q.front();
    q.pop();

    for (ll v : rev_edge_list[u]) {
      out_cts[v]--;

      unless(res[v] == DRAW) continue;

      if (res[u] == WIN) {
        res[v] = LOSE;
        q.push(v);
      } else if (res[u] == LOSE && out_cts[v] == 0) {
        res[v] = WIN;
        q.push(v);
      }
    }
  }

  rep(i, N) {
    string r = res[i] == DRAW   ? "Draw"
               : res[i] == LOSE ? "Aoki"
               : res[i] == WIN  ? "Takahashi"
                                : "";
    cout << r << "\n";
  }
}
