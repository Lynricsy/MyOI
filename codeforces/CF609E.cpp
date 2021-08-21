/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <algorithm>
#include <bits/stdc++.h>
#include <cstdint>
#include <cstdio>
#include <shared_mutex>
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
long long totM;
long long head[maxN];
long long cnt_edges;
long long nums[maxN];
long long num[maxN];
long long fath[maxN];
long long siz[maxN];
long long Sson[maxN];
long long dep[maxN];
long long ID[maxN];
long long top[maxN];
long long cntNODE;
long long MINTree;
long long nfa[maxN];
struct Edge {
  long long nxt;
  long long to;
  long long val;
} edges[maxN * 4], preges[maxN * 4];
void add_edge(long long x, long long y, long long w) {
  ++cnt_edges;
  edges[cnt_edges].nxt = head[x];
  head[x] = cnt_edges;
  edges[cnt_edges].to = y;
  edges[cnt_edges].val = w;
}
struct NTedge {
  long long u, v;
  long long w;
} nedges[maxN * 2], bedges[maxN * 2];
bool operator<(NTedge a, NTedge b) { return a.w < b.w; }

struct Node {
  long long val;
  Node *lch, *rch;
  long long tag;
  long long l, r;
  void pushup() { val = min(lch->val, rch->val); }
  Node(long long L, long long R) {
    tag = 0;
    if (L == R) {
      val = num[L];
      lch = rch = NULL;
      return;
    }
    long long Mid = (L + R) >> 1;
    lch = new Node(L, Mid);
    rch = new Node(Mid + 1, R);
  }
  bool INrange(long long L, long long R) { return (L <= l) && (r <= R); }
  bool OUTrange(long long L, long long R) { return (L > r) || (l > R); }
  long long query(long long L, long long R) {
    if (INrange(L, R)) {
      return val;
    } else if (OUTrange(L, R)) {
      return INF;
    }
    return min(lch->query(L, R), rch->query(L, R));
  }
};

void DFS1(long long nowX, long long fa) {
  dep[nowX] = dep[fa] + 1;
  fath[nowX] = fa;
  siz[nowX] = 1;
  for (int i = head[nowX]; i; i = edges[i].nxt) {
    long long vir = edges[i].to;
    if (vir == fa) {
      continue;
    }
    siz[nowX] += siz[vir];
    if (siz[vir] > siz[Sson[nowX]]) {
      Sson[nowX] = vir;
    }
  }
}

void DFS2(long long nowX, long long topp) {
  ++cntNODE;
  ID[nowX] = ++cntNODE;
  num[cntNODE] = nums[nowX];
  if (nowX == Sson[fath[nowX]]) {
    top[nowX] = topp;
  }
  for (int i = head[nowX]; i; i = edges[i].nxt) {
    long long vir = edges[i].to;
    if (vir == Sson[nowX] || vir == fath[nowX]) {
      continue;
    }
    DFS2(i, nowX);
  }
}

Node *rot;

long long Qroad(long long u, long long v) {
  long long minn = INF + 1;
  while (top[u] != top[v]) {
    if (dep[u] < dep[v]) {
      swap(u, v);
    }
    minn = min(minn, rot->query(ID[u], ID[top[u]]));
    u = fath[top[u]];
  }
  minn = min(minn, rot->query(u, v));
  return minn;
}

long long find(long long x) {
  if (x == nfa[x]) {
    return x;
  }
  return nfa[x] = find(nfa[x]);
}

void Kruskal() {
  for (int i = 1; i <= totM; ++i) {
    if (find(nedges[i].u) == find(nedges[i].v)) {
      continue;
    } else {
      add_edge(nedges[i].u, nedges[i].v, nedges[i].w);
      add_edge(nedges[i].v, nedges[i].u, nedges[i].w);
      MINTree += nedges[i].w;
    }
  }
}

int main() {
  totN = read();
  totM = read();
  for (int i = 1, x, y, z; i <= totM; ++i) {
    x = read();
    y = read();
    z = read();
    nedges[i].u = x;
    nedges[i].v = y;
    nedges[i].w = z;
    bedges[i].u = x;
    bedges[i].v = y;
    bedges[i].w = z;
  }
  sort(nedges + 1, nedges + totM + 1);
  Kruskal();
  DFS1(1, 0);
  DFS2(1, 1);
  rot = new Node(1, totN);
  for (int i = 1; i <= totM; ++i) {
    write(MINTree - Qroad(nedges[i].u, nedges[i].v) + bedges[i].w);
    putchar('\n');
  }
  return 0;
} // Thomitics Code