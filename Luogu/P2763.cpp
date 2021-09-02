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
#include <ratio>
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
long long totK;
long long totN;
long long pergrp[maxN];
long long totS;
long long totT;
long long now[maxN];
long long maxFLOW;

struct Edge {
  long long nxt;
  long long to;
  long long flow;
} edges[maxN << 1];
long long head[maxN << 1];
long long cnt_edges = 1;
void add_edge(long long u, long long v, long long f) {
  ++cnt_edges;
  edges[cnt_edges].nxt = head[u];
  head[u] = cnt_edges;
  edges[cnt_edges].to = v;
  edges[cnt_edges].flow = f;

  ++cnt_edges;
  edges[cnt_edges].nxt = head[v];
  head[v] = cnt_edges;
  edges[cnt_edges].to = u;
  edges[cnt_edges].flow = 0;
}

long long DIS[maxN];

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

int main() {
  totK = read();
  totN = read();
  for (int i = 1; i <= totK; ++i) {
    pergrp[i] = read();
  }
  totS = 0;
  totT = 2 * totN + 3;
  for (int i = 1, x; i <= totN; ++i) {
    x = read();
    for (int j = 1, v; j <= x; ++j) {
      v = read();
      add_edge(v + totN + 1, i, 1);
    }
  }
  for (int i = 1; i <= totK; ++i) {
    add_edge(totS, i + totN + 1, pergrp[i]);
  }
  for (int i = 1; i <= totN; ++i) {
    add_edge(i, totT, 1);
  }
  while (BFS()) {
    maxFLOW += DFS(totS, INF);
  }
  for (int i = head[totS]; i; i = edges[i].nxt) {
    if (edges[i].flow) {
      puts("No Solution!");
      return 0;
    }
  }
  for (int i = totN + 2; i <= totN + totK + 1; ++i) {
    write(i - totN - 1);
    putchar(':');
    putchar(' ');
    for (int j = head[i]; j; j = edges[j].nxt) {
      long long vir = edges[j].to;
      if (vir != totS && !edges[j].flow) {
        write(vir);
        putchar(' ');
      }
    }
    putchar('\n');
  }
  return 0;
} // Thomitics Code