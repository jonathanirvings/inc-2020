#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int SQRT = 400;

int n, m, q;
int a[N];

vector<int> sources[N];
vector<int> linked[N];
vector<int> heavySources[N];

long long totalSum[N];
long long totalSquaredSum[N];

bool isHeavy(int idx) {
  return linked[idx].size() > SQRT;
}

void read() {
  scanf("%d %d", &n, &m);
  for (int i = 1 ; i <= n ; i++) {
    scanf("%d", &a[i]);
  }
  for (int i = 1 ; i <= m ; i++) {
    int sz; scanf("%d", &sz);
    for (int j = 0 ; j < sz ; j++) {
      int x; scanf("%d", &x);
      sources[i].push_back(x);
      linked[x].push_back(i);
    }
  }
}

void prepare() {
  for (int i = 1 ; i <= n ; i++) {
    if (isHeavy(i)) {
      for (int j : linked[i]) {
        heavySources[j].push_back(i);
      }
      continue;
    }

    for (int j : linked[i]) {
      totalSum[j] += a[i];
      totalSquaredSum[j] += 1ll * a[i] * a[i];
    }
  }
}

void update(int idx, int newVal) {
  if (isHeavy(idx)) {
    a[idx] = newVal;
    return;
  }

  long long diff = newVal - a[idx];
  long long squaredDiff = 1ll * newVal * newVal - 1ll * a[idx] * a[idx];
  a[idx] = newVal;

  for (int j : linked[idx]) {
    totalSum[j] += diff;
    totalSquaredSum[j] += squaredDiff;
  }
}

long long query(int idx) {
  long long sum = totalSum[idx];
  long long squaredSum = totalSquaredSum[idx];

  for (int i : heavySources[idx]) {
    sum += a[i];
    squaredSum += 1ll * a[i] * a[i];
  }

  long long ret = (sum * sum - squaredSum) / 2;
  return ret;
}

void work() {
  scanf("%d", &q);
  for (int i = 0 ; i < q ; i++) {
    int opt; scanf("%d", &opt);

    if (opt == 1) {
      int idx, newVal;
      scanf("%d %d", &idx, &newVal);
      update(idx, newVal);
    } else {
      int idx; scanf("%d", &idx);
      printf("%lld\n", query(idx));
    }
  }
}

int main() {
  read();
  prepare();
  work();
  return 0;
}
