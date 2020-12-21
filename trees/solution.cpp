#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  scanf("%d", &N);
  vector<int> row(N), column(N), max_column(N);

  for (int i = 0; i < N; ++i) {
    int max_row = 0;
    for (int j = 0; j < N; ++j) {
      int H;
      scanf("%d", &H);
      if (H > max_row) {
        ++row[i];
        max_row = H;
      }
      if (H > max_column[j]) {
        ++column[j];
        max_column[j] = H;
      }
    }
  }
  for (int i = 0; i < N; ++i) {
    printf("%d%c", column[i], " \n"[i == N - 1]);
  }
  for (int i = 0; i < N; ++i) {
    printf("%d\n", row[i]);
  }
}
