// https://atcoder.jp/contests/abc096/tasks/abc096_c

#include "algorithm"
#include "iostream"
#include "set"
#include "vector"
#define rep(i, from, to) for (ll i = from; i < (to); ++i)
using namespace std;
typedef long long ll;

template <class T>
inline bool chmax(T& a, T b);
template <class T>
inline bool chmin(T& a, T b);

void solve() {
  ll H, W;
  cin >> H >> W;

  string G[H];
  rep(i, 0, H) cin >> G[i];

  int dy[4] = {0, -1, 1, 0};
  int dx[4] = {-1, 0, 0, 1};

  auto yes = "Yes";
  auto no = "No";

  rep(i, 0, H) {
    rep(j, 0, W) {
      if (G[i][j] == '.') {
        continue;
      }

      auto ok = false;

      rep(k, 0, 4) {
        if (G[i + dy[k]][j + dx[k]] == '#') {
          ok = true;
        }
      }

      if (!ok) {
        cout << no << endl;
        return;
      }
    }
  }

  cout << yes << endl;
}

#ifndef TEST
int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  solve();
  return 0;
}
#endif

template <class T>
inline bool chmax(T& a, T b) {
  if (a < b) {
    a = b;
    return 1;
  }
  return 0;
}

template <class T>
inline bool chmin(T& a, T b) {
  if (a > b) {
    a = b;
    return 1;
  }
  return 0;
}
