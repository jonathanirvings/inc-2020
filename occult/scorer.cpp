#include <bits/stdc++.h>
using namespace std;

int ac() {
  puts("AC");
  return 0;
}

int wa(string message) {
  fprintf(stderr, "%s\n", message.c_str());
  puts("WA");
  return 0;
}

const int IMPOSSIBLE_KEY = -1;

int main(int argc, char *argv[])
{
  FILE *in = fopen(argv[1], "r");
  FILE *out = fopen(argv[2], "r");  // Judge's
  FILE *con = fopen(argv[3], "r");

  int P;
  fscanf(in, "%d", &P);

  int judge;
  fscanf(out, "%d", &judge);

  if (fscanf(out, "%d", &judge) == EOF) {
    int contestant;
    if (fscanf(con, "%d", &contestant) != 1) {
      return wa("Unexpected EOF.");
    }
    if (contestant != IMPOSSIBLE_KEY) {
      return wa("Judge answer is `impossible`, contestant answer is not.");
    }
  } else {
    vector<int> sum_row(P), sum_col(P), sum_diag(2), cnt(P + 1);

    for (int i = 0; i < P; ++i) {
      for (int j = 0; j < P; ++j) {
        int s;
        if (fscanf(con, "%d", &s) != 1) {
          return wa("Unexpected EOF.");
        }
        if (s < 0 || s > P) {
          return wa("Integer out of bound.");
        }
        sum_row[i] += s;
        sum_col[j] += s;
        ++cnt[s];
        if (i == j) {
          sum_diag[0] += s;
        }
        if (i + j == P - 1) {
          sum_diag[1] += s;
        }
      }
    }
    int cnt_distinct = 0;
    for (int i = 1; i <= P; ++i) {
      cnt_distinct += cnt[i] > 0;
      if (cnt[i] > i) {
        return wa("Integer " + to_string(i) + " appears too often.");
      }
    }
    if (cnt_distinct < 2) {
      return wa("Too few distinct integers.");
    }

    if (!equal(sum_row.begin() + 1, sum_row.end(), sum_row.begin())) {
      return wa("Sums of rows are not the same.");
    }
    if (sum_row != sum_col) {
      return wa("Sums of rows are not the same with sums of cols."); 
    }
    if (!equal(sum_diag.begin(), sum_diag.end(), sum_row.begin())) {
      return wa("Sums of diags are not the same with sums of rows[:2].");
    }
  }

  fscanf(con, "\n");
  char dummy;
  if (fscanf(con, "%c", &dummy) == 1) {
    return wa("Expected EOF.");
  }

  return ac();
}
