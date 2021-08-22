/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
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

const long long maxN = 1000090;
long long totN;
long long col[maxN];
long long head[maxN];
long long cnt_edges;
long long siz[maxN];
long long Sson[maxN];
long long ap[maxN];
long long maxx;
long long sum;
long long ans[maxN];
struct Edge {
  long long nxt, to;
} edges[maxN];

void add_edge(long long x, long long y) {
  ++cnt_edges;
  edges[cnt_edges].nxt = head[x];
  edges[cnt_edges].to = y;
  head[x] = cnt_edges;
}

void get_giant_son(long long nowX, long long fa) {
  siz[nowX] = 1;
  long long maxx=0;
  for (long long i = head[nowX]; i; i = edges[i].nxt) {
    long long to = edges[i].to;
    if (to == fa)
      continue;
    get_giant_son(to, nowX);
    siz[nowX] += siz[to];
    if (siz[to] > siz[Sson[nowX]]) {
      Sson[nowX] = to;
    }
  }
}

void DFS(long long nowX, long long fa) {
  ++ap[col[nowX]];
  if (ap[col[nowX]] > maxx) {
    maxx = ap[col[nowX]];
    sum = col[nowX];
  } else if (ap[col[nowX] == maxx]) {
    sum += col[nowX];
  }
  for (int i = head[nowX]; i; i = edges[i].nxt) {
    long long vir = edges[i].to;
    if (vir == fa || vir == Sson[nowX]) {
      continue;
    }
    DFS(vir, nowX);
  }
}
inline void init(long long nowX, long long fa) {
  --ap[col[nowX]];
  for (int i = head[nowX]; i; i = edges[i].nxt) {
    long long vir = edges[i].to;
    if (vir == fa) {
      continue;
    }
    init(vir, nowX);
  }
}
void dfs(long long nowX, long long fa) {
  for (int i = head[nowX]; i; i = edges[i].nxt) {
    long long vir = edges[i].to;
    if (vir == fa) {
      continue;
    }
    if (vir != Sson[nowX]) {
      dfs(vir, nowX);
      init(vir, nowX);
      sum = maxx = 0;
    }
  }
  if (Sson[nowX]) {
    dfs(Sson[nowX], nowX);
  }
  DFS(nowX, fa);
  ans[nowX] = sum;
}

int main() {
  totN = read();
  for (int i = 1; i <= totN; ++i) {
    col[i] = read();
  }
  for (int i = 1, x, y; i <= totN; ++i) {
    x = read();
    y = read();
  }
  get_giant_son(1, 0);
  dfs(1, 0);
  for (int i = 1; i <= totN; ++i) {
    write(ans[i]);
    putchar(' ');
  }
  return 0;
} // Thomitics Code