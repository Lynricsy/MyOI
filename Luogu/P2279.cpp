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

const long long maxN = 100090;
long long totN;

struct Edge {
  long long to;
  long long nxt;
} edges[maxN << 1];
long long head[maxN << 1];
long long cnt_edges;
long long DP[maxN][5];
void add_edge(long long u, long long v) {
  ++cnt_edges;
  edges[cnt_edges].to = v;
  edges[cnt_edges].nxt = head[u];
  head[u] = cnt_edges;
}

void DFS(long long nowX) {
  DP[nowX][0] = 1;
  DP[nowX][3] = 0;
  DP[nowX][4] = 0;
  for (long long i = head[nowX]; i; i = edges[i].nxt) {
    long long vir = edges[i].to;
    DFS(vir);
    DP[nowX][0] += DP[vir][4];
    DP[nowX][3] += DP[vir][2];
    DP[nowX][4] += DP[vir][3];
  }
  if (head[nowX] == 0) {
    DP[nowX][1] = DP[nowX][2] = 1;
  } else {
    DP[nowX][1] = DP[nowX][2] = INF;
    for (long long i = head[nowX]; i; i = edges[i].nxt) {
      long long vir = edges[i].to;
      long long Tmp1 = DP[vir][0];
      long long Tmp2 = DP[vir][1];
      for (int j = head[nowX]; j; j = edges[j].nxt) {
        long long vir2 = edges[j].to;
        if (i == j) {
          continue;
        }
        Tmp1 += DP[vir2][3];
        Tmp2 += DP[vir2][2];
      }
      DP[nowX][1] = min(DP[nowX][1], Tmp1);
      DP[nowX][2] = min(DP[nowX][2], Tmp2);
    }
    for (int i = 1; i <= 4; ++i) {
      DP[nowX][i] = min(DP[nowX][i], DP[nowX][i - 1]);
    }
  }
}

int main() {
  totN = read();
  for (int i = 2, x; i <= totN; ++i) {
    x = read();
    add_edge(x, i);
  }
  DFS(1);
  write(DP[1][2]);
  return 0;
} // Thomitics Code