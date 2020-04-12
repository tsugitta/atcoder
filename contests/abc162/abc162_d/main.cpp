// https://atcoder.jp/contests/abc162/tasks/abc162_d

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
void solve2();

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

void solve() {
  ll N;
  string S;
  cin >> N >> S;

  map<char, VL> total;
  total['R'] = VL(N + 1);
  total['G'] = VL(N + 1);
  total['B'] = VL(N + 1);

  rep(i, N) {
    total['R'][i + 1] = total['R'][i] + (S[i] == 'R');
    total['G'][i + 1] = total['G'][i] + (S[i] == 'G');
    total['B'][i + 1] = total['B'][i] + (S[i] == 'B');
  }

  auto get_other = [](char a, char b) {
    string cur = "";
    cur.push_back(a);
    cur.push_back(b);
    sort(all(cur));

    if (cur == "BG") return 'R';
    if (cur == "BR") return 'G';
    if (cur == "GR") return 'B';
  };

  ll res = 0;

  rep(k, N) rep(j, k) {
    if (S[j] == S[k]) continue;

    ll ct = 0;
    ct += total[get_other(S[j], S[k])][j];

    ll i_index = j - (k - j);
    if (0 <= i_index && get_other(S[j], S[k]) == S[i_index]) ct--;

    res += ct;
  }

  cout << res << "\n";
}

void solve2() {
  ll N;
  string S;
  cin >> N >> S;

  map<char, ll> total;

  rep(i, N) total[S[i]]++;

  auto get_other = [](char a, char b) {
    string cur = "";
    cur.push_back(a);
    cur.push_back(b);
    sort(all(cur));

    if (cur == "BG") return 'R';
    if (cur == "BR") return 'G';
    if (cur == "GR") return 'B';
  };

  ll res = total['R'] * total['G'] * total['B'];

  rep(k, N) rep(j, k) {
    if (S[j] == S[k]) continue;

    ll i_index = j - (k - j);
    if (0 <= i_index && get_other(S[j], S[k]) == S[i_index]) res--;
  }

  cout << res << "\n";
}
