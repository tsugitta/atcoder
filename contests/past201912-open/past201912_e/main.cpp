// https://atcoder.jp/contests/past201912-open/tasks/past201912_e

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
  ll N, Q;
  cin >> N >> Q;

  V<V<bool>> edge_mat(N, V<bool>(N));

  rep(i, Q) {
    ll type;
    cin >> type;

    if (type == 1) {
      ll a, b;
      cin >> a >> b;
      a--, b--;
      edge_mat[a][b] = true;

    } else if (type == 2) {
      ll a;
      cin >> a;
      a--;

      rep(i, N) {
        if (edge_mat[i][a]) edge_mat[a][i] = true;
      }
    } else if (type == 3) {
      ll a;
      cin >> a;
      a--;

      queue<ll> q;
      rep(i, N) {
        if (edge_mat[a][i]) q.push(i);
      }

      while (!q.empty()) {
        ll i = q.front();
        q.pop();

        rep(j, N) {
          if (edge_mat[i][j]) {
            edge_mat[a][j] = true;
          }
        }
      }
    }
  }

  rep(i, N) {
    string res = "";

    rep(j, N) {
      if (i == j) {
        res.push_back('N');
        continue;
      }

      res.push_back(edge_mat[i][j] ? 'Y' : 'N');
    }

    cout << res << endl;
  }
}

// bitset
void solve2() {
  ll N, Q;
  cin >> N >> Q;

  V<bitset<100>> edge_mat(N);

  rep(i, Q) {
    ll type;
    cin >> type;

    if (type == 1) {
      ll a, b;
      cin >> a >> b;
      a--, b--;
      edge_mat[a][b] = true;

    } else if (type == 2) {
      ll a;
      cin >> a;
      a--;

      rep(i, N) {
        if (edge_mat[i][a]) edge_mat[a][i] = true;
      }
    } else if (type == 3) {
      ll a;
      cin >> a;
      a--;

      queue<ll> q;
      rep(i, N) {
        if (edge_mat[a][i]) q.push(i);
      }

      while (!q.empty()) {
        ll i = q.front();
        q.pop();

        edge_mat[a] |= edge_mat[i];
      }
    }
  }

  rep(i, N) {
    string res = "";

    rep(j, N) {
      if (i == j) {
        res.push_back('N');
        continue;
      }

      res.push_back(edge_mat[i][j] ? 'Y' : 'N');
    }

    cout << res << endl;
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
