/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <cmath>
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
long long DIS[maxN];
long long now[maxN];
long long maxFLOW;
long long totSUM;
long long totANS;

long long getHash(long long x, long long y) { return (x - 1) * totM + y; }
long long delt[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

struct Edge {
  long long nxt;
  long long to;
  long long flow;
} edges[maxN];
long long cnt_edges;
long long head[maxN];
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
  totN = read();
  totM = read();
  totS = 0;
  totT = totN * totM + 1;
  long long tmp;
  for (int i = 1; i <= totN; ++i) {
    for (int j = 1; j <= totM; ++j) {
      tmp = read();
      totSUM += tmp;
      if (!((i + j) & 1)) {
        add_edge(totS, getHash(i, j), tmp);
        for (int k = 0; k <= 3; ++k) {
          long long x = i + delt[k][0];
          long long y = j + delt[k][1];
          if (x >= 1 && x <= totN && y >= 1 && y <= totM) {
            add_edge(getHash(i, j), getHash(x, y), INF);
          }
        }
      } else {
        add_edge(getHash(i, j), totT, tmp);
      }
    }
  }
  if (BFS()) {
    maxFLOW += DFS(totS, INF);
  }
  totANS = totSUM - maxFLOW;
  write(totANS);
  return 0;
} // Thomitics Code