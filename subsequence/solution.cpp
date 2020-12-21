// O(N log N)

#include <bits/stdc++.h>

using namespace std;

const int mod = 998244353;

struct Fenwick {
  int n;
  vector<int> bit;
  Fenwick(int _n) : n(_n) {
    bit.assign(n+1, 0);
  }
  void update(int x, int v) {
    v %= mod;
    for (; x <= n; x += x&-x)
      bit[x] = (bit[x] + v) % mod;
  }
  int get(int x) {
    int r = 0;
    for (; x; x -= x&-x)
      r = (r + bit[x]) % mod;
    return r;
  }
};

int main() {
  int n;
  scanf("%d", &n);
  vector<int> a(n);
  for (int i = 0; i < n; ++i)
    scanf("%d", &a[i]);
  vector<int> distinct = a;
  sort(distinct.begin(), distinct.end());
  distinct.erase(unique(distinct.begin(), distinct.end()), distinct.end());
  auto getPos = [&distinct](int val){
    return lower_bound(distinct.begin(), distinct.end(), val) - distinct.begin();
  };
  Fenwick dpx(distinct.size()), dp(distinct.size());
  long long dpx_all = 0, dp_all = 0;
  for (int x : a) {
    int pos = getPos(x) + 1;
    x %= mod;
    long long dp_down = dp.get(pos), dpx_down = dpx.get(pos);
    long long dp_up = dp_all - dp_down, dpx_up = dpx_all - dpx_down;
    long long cur = ((1LL * x * dp_down - dpx_down) + (dpx_up - 1LL * x * dp_up) + 1) % mod;
    if (cur < 0)
      cur += mod;
    dp.update(pos, cur);
    dp_all = (dp_all + cur) % mod;
    long long mul = 1LL * cur * x % mod;
    if (mul < 0)
      mul += mod;
    dpx.update(pos, mul);
    dpx_all = (dpx_all + mul) % mod;
  }
  long long ans = (dp_all - n) % mod;
  if (ans < 0)
    ans += mod;
  printf("%lld\n", ans);
  return 0;
}
