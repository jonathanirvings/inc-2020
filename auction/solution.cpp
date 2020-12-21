// INCLUDE LIST
#include <cstdio>
#include <bitset>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <cstring>
#include <algorithm>
#include <map>
#include <set>
#include <list>
#include <vector>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <iomanip>
using namespace std;

int st[5000000];
int s[100010];

void build(int node, int l, int r) {
  if (l == r) {
    st[node] = s[l];
    return;
  }
  
  int mid   = (l + r) / 2;
  int left  = node * 2;
  int right = node * 2 + 1;
  
  build(left, l, mid);
  build(right, mid + 1, r);
  
  st[node] = min(st[left], st[right]);
}

void update(int node, int l, int r, int indx, int val) {
  if (l == r) {
    st[node] = val;
    return;
  }
    
  int mid = (l + r) / 2;
  
  if (indx <= mid) update(node * 2, l, mid, indx, val);
  else update(node * 2 + 1, mid + 1, r, indx, val);
  
  st[node] = min(st[node * 2], st[node * 2 + 1]);
}

int getMin(int node, int l, int r, int i, int j) {
  if (i <= l && r <= j)
    return st[node];
  
  if (r < i || j < l)
    return 2000000000;
  
  int mid   = (l + r) / 2;
  int left  = getMin(node * 2, l, mid, i, j);
  int right = getMin(node * 2 + 1, mid + 1, r, i, j);
  
  return min(left, right);
}

bool test(int p, int n, int M) {
  int p2 = getMin(1, 1, n, 1, M);
  return p2 < p;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int n, q, p;
  set<int> ans;
  
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> s[i];
  
  build(1, 1, n);
  
  cin >> q;
  while (q--) {
    cin >> p;
    p++;
    
    int L = 1;
    int R = n;
    int X = -1;
    
    while (L <= R) {
      int M  = (L + R) / 2;
      
      if (test(p, n, M)) {
        R = M - 1;
        X = M;
      } else L = M + 1;
    }
    
    if (X != -1) {
      ans.insert(X);
      update(1, 1, n, X, p);
    }
  }
  
  cout << ans.size() << endl;
  return 0;
}


