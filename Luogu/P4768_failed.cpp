/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
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

const long long maxN = 1e5 + 5;
long long totT;
long long totN;
long long totM;
struct Edge {
  long long to;
  long long nxt;
  long long val;
  long long h;
} edges[maxN * 2];
long long head[maxN];
long long cnt_edges;
bool vis[maxN];
void add_edge(long long u, long long v, long long w, long long h) {
  ++cnt_edges;
  edges[cnt_edges].to = v;
  edges[cnt_edges].nxt = head[u];
  edges[cnt_edges].val = w;
  edges[cnt_edges].h = h;
}
long long DIS[maxN];
struct Node {
  long long dis;
  long long id;
};
bool operator<(const Node &a, const Node &b) { return a.dis > b.dis; }

void Dijsktra(long long s) {
  memset(vis, 0, sizeof(vis));
  memset(DIS, 0x3f, sizeof(DIS));
  DIS[s] = 0;
  priority_queue<Node> Q;
  Q.push({0, s});
  vis[s] = true;
  while (!Q.empty()) {
    Node tmp = Q.top();
    Q.pop();
    long long u = tmp.id;
    long long du = tmp.dis;
    if (vis[u]) {
      continue;
    }
    vis[u] = true;
    for (long long i = head[u]; i; i = edges[i].nxt) {
      long long v = edges[i].to;
      long long dv = edges[i].val;
      if (du + dv < DIS[v]) {
        DIS[v] = du + dv;
        if (!vis[v]) {
          Q.push({DIS[v], v});
        }
      }
    }
  }
  memset(vis, 0, sizeof(vis));
}
long long p;
long long fa[maxN];
long long minn[maxN];
long long lc[maxN];
long long rc[maxN];

void build(long long &u, long long l, long long r) {
  u = ++p;
  if (l == r) {
    minn[u] = DIS[fa[u] = l];
    return;
  }
  long long mid = (l + r) >> 1;
  build(lc[u], l, mid);
  build(rc[u], mid + 1, r);
}
long long ins(long long *u, long long y, long long t) {
  long long l = 1;
  long long r = totN;
  long long mid;
  while (l <= r) {
    *u = ++p;
    mid = (l + r) >> 1;
    if (t <= mid) {
      r = mid;
      rc[*u] = rc[y];
      u = lc + *u;
      y = lc[y];
    } else {
      l = mid + 1;
      lc[*u] = lc[y];
      u = rc + *u;
      y = rc[y];
    }
  }
  return *u = ++p;
}
long long getfa(long long rot, long long t) {
  long long u;
  long long l, r;
  long long mid;
  while (true) {
    u = rot;
    l = 1;
    r = totN;
    while (l <= r) {
      mid = (l + r) >> 1;
      if (t <= mid) {
        r = mid;
        u = lc[u];
      } else {
        l = mid + 1;
        u = rc[u];
      }
    }
    if (t == fa[u]) {
      t = fa[u];
    }
    return u;
  }
}
int main() {
  totT = read();
  while (totT--) {
    totN = read();
    totM = read();
    p = 0;
    for (int i = 1; i <= totM; ++i) {
      long long u = read();
      long long v = read();
      long long w = read();
      long long h = read();
    }
  }
  return 0;
} // Thomitics Code