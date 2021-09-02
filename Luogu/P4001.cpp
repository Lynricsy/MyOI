/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
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

const long long maxN = 10000090;
long long totN;
long long totM;
long long now[maxN];
long long DIS[maxN];
long long totS;
long long totT;
long long maxFLOW;

long long getHash(long long x, long long y) { return (x - 1) * totM + y; }

struct Edge {
  long long nxt;
  long long to;
  long long flow;
} edges[maxN << 1];
long long head[maxN << 1];
long long cnt_edges = 1;
void add_edges(long long u, long long v, long long f) {
  ++cnt_edges;
  edges[cnt_edges].nxt = head[u];
  head[u] = cnt_edges;
  edges[cnt_edges].to = v;
  edges[cnt_edges].flow = f;

  ++cnt_edges;
  edges[cnt_edges].nxt = head[v];
  head[v] = cnt_edges;
  edges[cnt_edges].to = u;
  edges[cnt_edges].flow = f;
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
  for (int i = now[nowX]; i && nowOUT < inFLOW; i = edges[i].nxt) {
    long long vir = edges[i].to;
    now[nowX] = i;
    if ((DIS[vir] != DIS[nowX] + 1) || (!edges[i].flow)) {
      continue;
    }
    nowOUT = DFS(vir, min(edges[i].flow, inFLOW - outFLOW));
    if (!nowOUT) {
      DIS[vir] = -1;
      continue;
    }
    // inFLOW -= nowOUT;
    outFLOW += nowOUT;
    edges[i].flow -= nowOUT;
    edges[i ^ 1].flow += nowOUT;
  }
  return outFLOW;
}

int main() {
  totN = read();
  totM = read();
  long long tmp;
  totS = 1;
  totT = getHash(totN, totM);
  for (int i = 1; i <= totN; ++i) {
    for (int j = 1; j <= totM - 1; ++j) {
      tmp = read();
      add_edges(getHash(i, j), getHash(i, j + 1), tmp);
    }
  }
  for (int i = 1; i <= totN - 1; ++i) {
    for (int j = 1; j <= totM; ++j) {
      tmp = read();
      add_edges(getHash(i, j), getHash(i + 1, j), tmp);
    }
  }
  for (int i = 1; i <= totN - 1; ++i) {
    for (int j = 1; j <= totM - 1; ++j) {
      tmp = read();
      add_edges(getHash(i, j), getHash(i + 1, j + 1), tmp);
    }
  }
  while (BFS()) {
    maxFLOW += DFS(totS, INF);
  }
  write(maxFLOW);
  return 0;
} // Thomitics Code