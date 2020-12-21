#include <bits/stdc++.h>
using namespace std;

const int kMaxN = 10005;
const int MOD = 998244353;

const int kMaxF = kMaxN * 100;
int fact[kMaxF], ifact[kMaxF];

int power(int x, int y) {
  int ret = 1;
  for (; y > 1; y >>= 1) {
    if (y & 1) ret = 1LL * ret * x % MOD;
    x = 1LL * x * x % MOD;
  }
  return 1LL * ret * x % MOD;
}

void initC() {
  fact[0] = 1;
  for (int i = 1; i < kMaxF; ++i) {
    fact[i] = 1LL * fact[i-1] * i % MOD;
  }
  ifact[kMaxF - 1] = power(fact[kMaxF - 1], MOD - 2);
  for (int i = kMaxF - 2; i >= 0; --i) {
    ifact[i] = 1LL * ifact[i + 1] * (i + 1) % MOD;
  }
}

int C(int n, int k) {
  if (k < 0 || k > n) return 0;
  return 1LL * fact[n] * ifact[k] % MOD * ifact[n - k] % MOD;
}

// Counting multisets (n stars and k bars)
int M(int n, int k) {
  return C(n + k - 1, k - 1);
}

int n;
vector<pair<int, int>> edges[kMaxN];

int dfs(int u, int p) {
  int ret = 1;
  int sumChild = 0, cntPar = 1;
  for (int i = 0; i < edges[u].size(); ++i) {
    int v, w;
    tie(v, w) = edges[u][i];

    if (v == p) {
      cntPar = w;
    } else {
      ret = 1LL * ret * ifact[w] % MOD * dfs(v, u) % MOD;
      sumChild += w;
    }
  }

  ret = 1LL * ret * fact[sumChild] % MOD;
  return 1LL * ret * M(sumChild, cntPar) % MOD;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);
    --u, --v, w >>= 1;

    edges[u].emplace_back(v, w);
    edges[v].emplace_back(u, w);
  }

  initC();

  printf("%d\n", dfs(0, -1));
  return 0;
}
