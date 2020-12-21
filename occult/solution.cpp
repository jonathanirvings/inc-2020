#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> hardcoded = {{0, 0, 0, 3, 4},
                                 {2, 4, 0, 0, 1},
                                 {0, 0, 3, 4, 0},
                                 {5, 0, 0, 0, 2},
                                 {0, 3, 4, 0, 0}};

int val(int P, int x, int y) {
  if (P == hardcoded.size()) {
    return hardcoded[x][y];
  }
  if (x < P / 2 - 1) {
    return y == x + 1 ? P : 0;
  }
  if (x == P / 2 - 1) {
    return y == 0 ? 2 : (y == P - 1 ? P - 2 : 0);
  }
  if (x == P / 2) {
    return y == P / 2 ? P : 0;
  }
  if (x == P / 2 + 1) {
    return y == 0 ? P - 2 : (y == P - 1 ? 2 : 0); 
  }
  return y == x - 1 ? P : 0;
}

int main() {
  int P;
  scanf("%d", &P);
  if (P <= 3) {
    puts("-1");
  } else {
    for (int i = 0; i < P; ++i) {
      for (int j = 0; j < P; ++j) {
        printf("%d%c", val(P, i, j), " \n"[j == P - 1]);
      }
    }
  }
}
