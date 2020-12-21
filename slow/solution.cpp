#pragma GCC optimize "-O2"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

const int maxn = 1005;
const int inf = 1000000007;

struct tdata { int node, cost; };
struct tflow { int node, cap, flow; };
bool operator < (const tdata &a, const tdata &b) { return a.cost > b.cost; }

int N, M;
vector<tdata> con[maxn];

vector<int> ShortestPathFrom(int start) {
  vector<int> ret(N+1, inf);
  priority_queue <tdata> pq;
  ret[start] = 0;
  pq.push((tdata){start, 0});
  while (!pq.empty()) {
    tdata p = pq.top(); pq.pop();
    if (p.cost != ret[p.node]) continue;
    for (auto &v : con[p.node]) {
      if (ret[v.node] <= p.cost + v.cost) continue;
      ret[v.node] = ret[p.node] + v.cost;
      pq.push((tdata){v.node, ret[v.node]});
    }
  }
  return ret;
}

vector <int> edge[maxn];
int cap[maxn][maxn] = {0};
int flow[maxn][maxn] = {0};

bool Augment(int s, int t) {
  queue <int> q;
  bool visit[maxn] = { false };
  int parent[maxn];

  q.push(s); visit[s] = true; parent[s] = -1;

  while (!q.empty()) {
    int curr = q.front(); q.pop();
    for (auto &i : edge[curr]) {
      if (visit[i] || cap[curr][i]-flow[curr][i] <= 0) continue;
      q.push(i); visit[i] = true; parent[i] = curr;
      if (i == t) { 
        int p = t, value = inf;
        while (parent[p] != -1) {
          value = min(value, cap[parent[p]][p]-flow[parent[p]][p]);
          p = parent[p];
        }
        p = t;
        while (parent[p] != -1) {
          flow[parent[p]][p] += value;
          flow[p][parent[p]] -= value;
          p = parent[p];
        }
        return true;
      }
    }
  }

  return false;
}

int MaxFlow(int s, int t) {
  int ret = 0;
  while (Augment(s, t)) ++ret;
  return ret;
}


int main(int argc, char *argv[]) {
  scanf("%d %d", &N, &M) != EOF;
  for (int i = 0; i < M; ++i) {
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w) != EOF;
    con[u].push_back((tdata){v, w});
    con[v].push_back((tdata){u, w});
  }

  vector<int> A = ShortestPathFrom(1);
  vector<int> B = ShortestPathFrom(N);

  for (int i = 1; i <= N; ++i)
    for (auto &v : con[i])
      if (A[i] + v.cost + B[v.node] == A[N]) {
        cap[i][v.node] = 1;
        edge[i].push_back(v.node);
        edge[v.node].push_back(i);
      }

  int ans = MaxFlow(1, N);

  printf("%d\n", ans);

  return 0;
}
