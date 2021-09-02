/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <queue>
#define INF 0x3f3f3f3f3f3f3f3f
#define IINF 0x3f3f3f3f

using namespace std;

inline long long read() {
  long long x = 0;
  int f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = (x << 1) + (x << 3) + (ch ^ 48);
    ch = getchar();
  }
  return x * f;
}
template <typename T> inline void write(T x) {
  if (x < 0ll) {
    putchar('-');
    x = -x;
  }
  if (x > 9ll)
    write(x / 10ll);
  putchar(x % 10ll + '0');
}

long long totN;
long long totM;

long long DIS[1090];
bool vis[1090];
long long totANS;

struct Edge {
  long long to;
  long long nxt;
} edges[300090 << 1];
long long head[300090 << 1];
long long cnt_edges;
void add_edge(long long u, long long v) {
  ++cnt_edges;
  edges[cnt_edges].nxt = head[u];
  head[u] = cnt_edges;
  edges[cnt_edges].to = v;
}

void BFS(long long nowX) {
  memset(vis, 0, sizeof vis);
  queue<long long> Q;
  Q.push(nowX);
  vis[nowX] = true;
  DIS[nowX] = 0;
  while (!Q.empty()) {
    long long nS = Q.front();
    Q.pop();
    for (int i = head[nS]; i; i = edges[i].nxt) {
      long long vir = edges[i].to;
      if (!vis[vir]) {
        DIS[vir] = DIS[nS] + 1;
        totANS = max(totANS, DIS[vir]);
        Q.push(vir);
        vis[vir] = true;
      }
    }
  }
}

int main() {
  while (true) {
    totN = read();
    totM = read();
    if (!totN && !totM) {
      return 0;
    }
    totANS = -1;
    memset(head, 0, sizeof head);
    cnt_edges = 0;
    for (int i = 1, u, v; i <= totM; ++i) {
      u = read();
      v = read();
      add_edge(u, v);
      add_edge(v, u);
    }
    for (int i = 1; i <= totN; ++i) {
      BFS(i);
      for (int j = 1; j <= totN; ++j) {
      }
    }
    write(totANS * 100);
    putchar('\n');
  }
  return 0;
} // Thomitics Code