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

const long long maxN = 190;
long long totN;
long long totQ;
long long DP[maxN][maxN];

struct Edge {
  long long nxt;
  long long to;
  long long val;
} edges[maxN * 4];
long long head[maxN * 4];
long long cnt_edges;
long long siz[maxN];
void add_edge(long long x, long long y, long long w) {
  ++cnt_edges;
  edges[cnt_edges].nxt = head[x];
  head[x] = cnt_edges;
  edges[cnt_edges].to = y;
  edges[cnt_edges].val = w;
}

void DFS(long long now, long long fa) {
  for (int i = head[now]; i; i = edges[i].nxt) {
    if (edges[i].to == fa)
      continue;
    long long vir = edges[i].to;
    DFS(vir, now);
    siz[now] += siz[vir] + 1;
    // for (int i = 1; i <= min(siz[now], totQ); ++i) {
    for (long long j = min(siz[now], totQ); j >= 1; --j) {
      for (int k = min(j - 1, siz[vir]); k >= 0; --k) {
        DP[now][j] =
            max(DP[now][j], DP[now][j - k - 1] + DP[vir][k] + edges[i].val);
      }
    }
  }
}

int main() {
  totN = read();
  totQ = read();
  for (long long i = 1, x, y, z; i <= totN - 1; ++i) {
    x = read();
    y = read();
    z = read();
    add_edge(x, y, z);
    add_edge(y, x, z);
  }
  DFS(1, 0);
  write(DP[1][totQ]);
  return 0;
} // Thomitics Code