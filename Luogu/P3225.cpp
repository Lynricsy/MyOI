/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <cstdio>
#include <cstdlib>
#include <stack>
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
  if (!x * f) {
    exit(0);
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

const long long maxN = 1000090;
long long totN;

struct Edge {
  long long nxt;
  long long to;
} edges[maxN * 2];
long long head[maxN << 1];
long long cnt_edges;
void add_edge(long long u, long long v) {
  ++cnt_edges;
  edges[cnt_edges].to = v;
  edges[cnt_edges].nxt = head[u];
  head[u] = cnt_edges;
}
long long dfn[maxN << 1], low[maxN << 1];
stack<long long> S;
long long dfs_cnt;
long long rot;
bool is_CUT[maxN << 1];
long long rotsons;
long long grp[maxN << 1];
long long nowCUT;
long long nowNUM;
long long ANScnt = 1;
long long ANSmin = 0;
long long Group;
long long NOWcase;
long long totNODE;

void Tarjan(long long x, long long fa) {
  long long v;
  ++dfs_cnt;
  dfn[x] = low[x] = dfs_cnt;
  // S.push(x);
  for (long long i = head[x]; i; i = edges[i].nxt) {
    v = edges[i].to;
    if (!dfn[v]) {
      Tarjan(v, x);
      low[x] = min(low[x], low[v]);
      if (low[v] >= dfn[x]) {
        if (x != rot) {
          is_CUT[x] = true;
        } else {
          ++rotsons;
        }
      }
    } else {
      if (v != fa) {
        low[x] = min(low[x], dfn[v]);
      }
    }
  }
}

void DFS(long long x) {
  long long v;
  grp[x] = Group;
  ++nowNUM;
  for (long long i = head[x]; i; i = edges[i].nxt) {
    v = edges[i].to;
    if (is_CUT[v] && grp[v] != Group) {
      ++nowCUT;
      grp[v] = Group;
    }
    if (!grp[v]) {
      DFS(v);
    }
  }
}

void init() {
  cnt_edges = 0;
  dfs_cnt = 0;
  rot = 0;
  rotsons = 0;
  nowCUT = 0;
  nowNUM = 0;
  ANScnt = 1;
  ANSmin = 0;
  Group = 0;
  totNODE = 0;
  memset(head, 0, sizeof(head));
  memset(dfn, 0, sizeof(dfn));
  memset(low, 0, sizeof(low));
  memset(is_CUT, 0, sizeof(is_CUT));
  memset(grp, 0, sizeof(grp));
}

int main() {
  while (true) {
    ++NOWcase;
    init();
    totN = read();
    if (!totN) {
      break;
    }
    long long u, v;
    for (long long i = 1; i <= totN; ++i) {
      u = read();
      v = read();
      add_edge(u, v);
      add_edge(v, u);
      totNODE = max(totNODE, max(u, v));
    }
    for (long long i = 1; i <= totNODE; ++i) {
      if (!dfn[i]) {
        rot = i;
        rotsons = 0;
        Tarjan(i, i);
        if (rotsons >= 2) {
          is_CUT[i] = true;
        }
      }
    }
    for (long long i = 1; i <= totNODE; ++i) {
      if (!grp[i] && !is_CUT[i]) {
        ++Group;
        nowNUM = nowCUT = 0;
        DFS(i);
        if (!nowCUT) {
          ANSmin += 2;
          ANScnt *= (nowNUM - 1) * nowNUM / 2;
        }
        if (nowCUT == 1) {
          ++ANSmin;
          ANScnt *= nowNUM;
        }
      }
    }
    printf("Case %lld: %lld %lld\n", NOWcase, ANSmin, ANScnt);
  }
  return 0;
} // Thomitics Code