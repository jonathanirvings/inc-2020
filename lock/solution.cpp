#include <bits/stdc++.h>
using namespace std;

int main() {
  int R, C;
  scanf("%d %d", &R, &C);

  vector<string> S(R, string(C, '0'));
  for (int i = 0; i < R; ++i) {
    scanf("\n");
    for (int j = 0; j < C; ++j) {
      scanf("%c", &S[i][j]);
    }
  }

  int answer = INT_MAX;
  for (int m = 0; m < 10; ++m) {
    int cnt_m = 0;
    vector<vector<int>> right(R, vector<int>(C, INT_MAX));
    vector<vector<int>> up(R, vector<int>(C, INT_MAX));
    vector<vector<int>> op(R, vector<int>(C, 0));
    int min_sum = INT_MAX;
    for (int i = 0; i < R; ++i) {
      for (int j = C - 1; j >= 0; --j) {
        op[i][j] = m - (S[i][j] - '0');
        if (op[i][j] < 0) {
          op[i][j] += 10;
        }
        if (op[i][j] == 0) {
          op[i][j] = -1;
          ++cnt_m;
        }
        if (i > 0) {
          up[i][j] = op[i][j] + min(up[i - 1][j], op[i - 1][j]);
        }
        if (j + 1 < C) {
          right[i][j] = op[i][j] + min(right[i][j + 1], op[i][j + 1]);
        }
        if (i > 0 && j + 1 < C) {
          min_sum = min(min_sum, up[i][j] + right[i][j] - op[i][j]);
        }
      }
    }
    answer = min(answer, min_sum + cnt_m);
  }
  printf("%d\n", answer);
}
