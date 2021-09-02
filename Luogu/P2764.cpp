/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <csetjmp>
#include <cstdio>
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

const long long maxN = 100090;
long long totN;
long long totM;
long long totS;
long long totT;
long long now[maxN];
long long DIS[maxN];
long long fa[maxN];
long long cntR;

struct Edge {
  long long from;
  long long nxt;
  long long to;
  long long flow;
} edges[maxN << 2];
long long head[maxN << 2];
long long cnt_edges = 1;
void add_edge(long long u, long long v, long long f) {
  ++cnt_edges;
  edges[cnt_edges].nxt = head[u];
  head[u] = cnt_edges;
  edges[cnt_edges].to = v;
  edges[cnt_edges].flow = f;
  edges[cnt_edges].from = u;

  ++cnt_edges;
  edges[cnt_edges].nxt = head[v];
  head[v] = cnt_edges;
  edges[cnt_edges].to = u;
  edges[cnt_edges].flow = 0;
  edges[cnt_edges].from = v;
}

bool BFS() {
  memset(DIS, 0x3f, sizeof DIS);
  queue<long long> Q;
  DIS[totS] = 0;
  now[totS] = head[totS];
  Q.push(totS);
  while (!Q.empty()) {
    long long nowX = Q.front();
    Q.pop();
    for (int i = head[nowX]; i; i = edges[i].nxt) {
      long long vir = edges[i].to;
      if ((DIS[vir] != INF) || (!edges[i].flow)) {
        continue;
      }
      Q.push(vir);
      DIS[vir] = DIS[nowX] + 1;
      now[vir] = head[vir];
      if (vir == totT) {
        return true;
      }
    }
  }
  return false;
}

long long DFS(long long nowX, long long inFLOW) {
  if ((nowX == totT) || (!inFLOW)) {
    return inFLOW;
  }
  long long outFLOW = 0;
  long long nowOUT = 0;
  for (int i = now[nowX]; i && inFLOW; i = edges[i].nxt) {
    long long vir = edges[i].to;
    now[nowX] = i;
    if ((DIS[vir] != DIS[nowX] + 1) || (!edges[i].flow)) {
      continue;
    }
    nowOUT = DFS(vir, min(edges[i].flow, inFLOW));
    inFLOW -= nowOUT;
    outFLOW += nowOUT;
    edges[i].flow -= nowOUT;
    edges[i ^ 1].flow += nowOUT;
  }
  return outFLOW;
}

long long find(long long x) {
  if (fa[x] == x) {
    return x;
  }
  return find(fa[x]);
}

void op(long long x) {
  write(x);
  putchar(' ');
  for (int i = head[x]; i; i = edges[i].nxt) {
    if (!edges[i].flow && edges[i].to >= totN + 1) {
      op(edges[i].to - totN - 1);
    }
  }
}

int main() {
  totN = read();
  totM = read();
  totS = 0;
  totT = totN * 2 + 3;
  for (int i = 1, u, v; i <= totM; ++i) {
    u = read();
    v = read();
    add_edge(u, v + totN + 1, 1);
  }
  for (int i = 1; i <= totN; ++i) {
    add_edge(totS, i, 1);
  }
  for (int i = 1; i <= totN; ++i) {
    add_edge(i + totN + 1, totT, 1);
  }
  while (BFS()) {
    DFS(totS, INF);
  }
  for (int i = 1; i <= totN; ++i) {
    fa[i] = i;
  }
  for (int i = 2; i <= cnt_edges; ++i) {
    if (edges[i].from >= 1 && edges[i].from <= totN && !edges[i].flow &&
        edges[i].to >= totN + 2 && edges[i].to <= totN * 2 + 1) {
      fa[find(edges[i].to - totN - 1)] = find(edges[i].from);
    }
  }
  for (int i = 1; i <= totN; ++i) {
    if (find(i) == i) {
      op(i);
      ++cntR;
      putchar('\n');
    }
  }
  write(cntR);
  return 0;
} // Thomitics Code