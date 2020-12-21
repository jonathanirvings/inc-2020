#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  scanf("%d", &N);
  vector<int> C(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &C[i]);
  }

  vector<bool> win(N, false);
  for (int i = 0; i < N; ++i) {
    for (int d = -1; d <= 1; ++d) {
      if (0 <= i + d && i + d < N && C[i] > 0 && !win[i + d]) {
        --C[i];
        win[i + d] = true;
      }
    }
  }
  printf("%d\n", count(win.begin(), win.end(), true));
}
