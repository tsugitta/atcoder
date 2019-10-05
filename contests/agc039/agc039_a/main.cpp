// https://atcoder.jp/contests/agc039/tasks/agc039_a

#include "algorithm"
#include "iostream"
#include "set"
#include "vector"
#define rep(i, from, to) for (ll i = from; i < (to); ++i)
using namespace std;
typedef long long ll;
template <typename T>
using V = vector<T>;
template <typename T>
inline bool chmax(T& a, T b);
template <typename T>
inline bool chmin(T& a, T b);
void print_ints(vector<ll> v);
template <typename T>
void drop(T a);

string s;
ll k;

ll partial(string t) {
  ll len = t.size();
  ll ct = 0;
  auto prev = t[0];

  rep(i, 1, len) {
    if (t[i] == prev) {
      ct++;
      i++;
    }

    prev = t[i];
  }

  return ct;
}

void solve() {
  cin >> s >> k;
  ll len = s.size();

  {
    auto all_same = true;

    rep(i, 0, len - 1) {
      if (s[i] != s[i + 1]) {
        all_same = false;
        break;
      }
    }

    if (all_same) {
      drop((len * k) / 2);
    }
  }

  ll inside = partial(s);

  if (s[0] != s[len - 1]) {
    drop(inside * k);
  }

  // 等差で増えていく。 「s の最後の連結を後続の s の先頭に合わせて書き換える +
  // 以降の最良のやり方を足す」が繰り返されるため。
  ll twice = partial(s + s);
  ll diff = twice - inside;

  ll res = inside + (k - 1) * diff;
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
