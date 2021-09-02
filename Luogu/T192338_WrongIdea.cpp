/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <cstring>
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
void write(const long long &x) {
  if (!x) {
    putchar('0');
    return;
  }
  char f[100];
  long long tmp = x;
  if (tmp < 0) {
    tmp = -tmp;
    putchar('-');
  }
  long long s = 0;
  while (tmp > 0) {
    f[s++] = tmp % 10 + '0';
    tmp /= 10;
  }
  while (s > 0) {
    putchar(f[--s]);
  }
}

const long long maxNODE = 100090;
const long long maxR = 109;

long long DPm[maxNODE][maxR];
long long DPz[maxNODE][maxR];

long long totN;
long long totR;

long long totMIN = INF;

struct Edge {
  long long to, next;
  long long tag;
} edges[maxNODE << 1];
long long head[maxNODE << 1];
long long cnt_edges;
void addEdge(long long from, long long to, long long tag) {
  ++cnt_edges;
  edges[cnt_edges].to = to;
  edges[cnt_edges].next = head[from];
  edges[cnt_edges].tag = tag;
  head[from] = cnt_edges;
}

void DP_min(long long x, long long fa) {
  long long cntOUT = 0;
  // DPm[x][0] = 0;
  // for (long long i = 1; i <= totR; ++i) {
  //   DPm[x][i] = i;
  // }
  for (int i = head[x]; i; i = edges[i].next) {
    long long to = edges[i].to;
    if (to == fa) {
      continue;
    }
    DP_min(to, x);
    ++cntOUT;
    if (edges[i].tag == 0) {
      // for (long long j = 1; j <= 3; ++j) {
      //   for (int k = 1; k <= 3; ++k) {
      //     if (j == k) {
      //       continue;
      //     }
      //     DPm[x][j] = min(DPm[x][j], DPm[to][k] + j);
      //   }
      // }
      DPm[x][1] += DPm[to][2];
      DPm[x][2] += DPm[to][1];
    }
    if (edges[i].tag == 1) {
      DPm[x][1] += min(DPm[to][1], DPm[to][2]);
      DPm[x][2] += min(DPm[to][1], DPm[to][2]);
    }
    if (edges[i].tag == 2) {
      DPm[x][1] += DPm[to][1];
      DPm[x][2] += DPm[to][2];
    }
  }
  if (cntOUT == 0) {
    // for (long long j = 1; j <= totR; ++j) {
    //   DPm[x][j] = min(DPm[x][j], j);
    // }
    DPm[x][1] = 1;
    DPm[x][2] = 2;
  }
}

int main() {
  totN = read();
  totR = read();
  for (int i = 1, x, y, t; i <= totN - 1; ++i) {
    x = read();
    y = read();
    t = read();
    addEdge(x, y, t);
    addEdge(y, x, t);
  }
  // memset(DPm, 0x3f, sizeof(DPm));
  DP_min(1, 0);
  for (int i = 1; i <= totR; ++i) {
    totMIN = min(totMIN, DPm[1][i]);
  }
  write(totMIN);
  return 0;
} // Thomitics Code