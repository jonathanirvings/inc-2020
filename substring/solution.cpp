#pragma GCC optimize "-O2"
#include <bits/stdc++.h>
using namespace std;

const int maxn = 100005;
const int inf  = 0x7fffffff;

int N, K;
char S[maxn];

int main(int argc, char *argv[]) {
  scanf("%d %d", &N, &K) != EOF;
  scanf("%s", S) != EOF;

  int ans = inf;

  for (char c = 'A'; c <= 'Z'; ++c) {
    int cost = 0;
    for (int i = 0, j = 0; j < N; ++j) {
      if (S[j] != c) {
        ++cost;
      }
      if (j-i+1 > K) {
        if (S[i] != c) {
          --cost;
        }
        ++i;
      }
      if (j-i+1 == K) {
        ans = min(ans, cost);
      }
    }
  }

  printf("%d\n", ans);
  
  return 0;
}
