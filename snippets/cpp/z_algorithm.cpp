#include "algorithm"
#include "iostream"
#include "map"
#include "vector"
#define rep(i, from, to) for (ll i = from; i < (to); ++i)
using namespace std;
template <typename T>
using V = vector<T>;
using VL = V<ll>;
typedef long long ll;

// O(|S|)
// res[i]: S と S[i:] が先頭から何文字一致しているか
VL z_algorithm(const string &S) {
  ll N = S.size();
  VL res(N);
  res[0] = N;
  ll i = 1, j = 0;

  while (i < N) {
    while (i + j < N && S[j] == S[i + j]) ++j;
    res[i] = j;

    if (j == 0) {
      ++i;
      continue;
    }

    ll k = 1;
    while (i + k < N && k + res[k] < j) res[i + k] = res[k], ++k;
    i += k, j -= k;
  }

  return res;
}
