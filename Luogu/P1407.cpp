/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <cstdio>
#include <iostream>
#include <map>
#include <stack>
#include <utility>
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

struct Edge {
  long long to;
  long long nxt;
} edges[maxN << 1];
long long head[maxN << 1];
long long cnt_edges;
void addEdge(long long u, long long v) {
  ++cnt_edges;
  edges[cnt_edges].to = v;
  edges[cnt_edges].nxt = head[u];
  head[u] = cnt_edges;
}
long long low[maxN];
long long dfn[maxN];
bool inS[maxN];
long long inSCC[maxN];
long long cntSCC;
stack<long long> St;
set<string> S;
map<string, long long> M;
long long cntSTR;
pair<string, string> maried[maxN];

void Tarjan(long long u) {
  low[u] = dfn[u] = ++cntSTR;
  St.push(u);
  inS[u] = true;
  for (long long i = head[u]; i; i = edges[i].nxt) {
    long long v = edges[i].to;
    if (!dfn[v]) {
      Tarjan(v);
      low[u] = min(low[u], low[v]);
    } else if (inS[v]) {
      low[u] = min(low[u], dfn[v]);
    }
  }
  if (low[u] == dfn[u]) {
    long long v;
    do {
      v = St.top();
      St.pop();
      inSCC[v] = cntSCC;
      inS[v] = false;
    } while (v != u);
    ++cntSCC;
  }
}

int main() {
  // totN = read();
  // for (int i = 1, u, v; i <= totN; ++i) {
  //   string s, t;
  //   cin >> s;
  //   if (S.find(s) == S.end()) {
  //     ++cntSTR;
  //     S.insert(s);
  //     M[s] = cntSTR;
  //     u = cntSTR;
  //   } else {
  //     u = M[s];
  //   }
  //   cin >> t;
  //   if (S.find(t) == S.end()) {
  //     ++cntSTR;
  //     S.insert(t);
  //     M[t] = cntSTR;
  //     v = cntSTR;
  //   } else {
  //     v = M[t];
  //   }
  //   addEdge(u, v);
  //   maried[i] = make_pair(s, t);
  // }
  // totM = read();
  // for (int i = 1, u, v; i <= totM; ++i) {
  //   string s, t;
  //   cin >> s;
  //   if (S.find(s) == S.end()) {
  //     ++cntSTR;
  //     S.insert(s);
  //     M[s] = cntSTR;
  //     u = cntSTR;
  //   } else {
  //     u = M[s];
  //   }
  //   cin >> t;
  //   if (S.find(t) == S.end()) {
  //     ++cntSTR;
  //     S.insert(t);
  //     M[t] = cntSTR;
  //     v = cntSTR;
  //   } else {
  //     v = M[t];
  //   }
  //   addEdge(v, u);
  // }
  totN = read();
  for (int i = 1, u, v; i <= totN; ++i) {
    string s, t;
    cin >> s;
    M[s] = i;
    cin >> t;
    M[t] = i + totN;
    addEdge(i, i + totN);
  }
  totM = read();
  for (int i = 1, u, v; i <= totM; ++i) {
    string s, t;
    cin >> s;
    cin >> t;
    addEdge(M[t], M[s]);
  }
  for (long long i = 1; i <= 2 * totN; ++i) {
    if (!dfn[i]) {
      Tarjan(i);
    }
  }
  for (long long i = 1; i <= totN; ++i) {
    // if (inSCC[i] == inSCC[M[maried[i].first]] &&
    //     inSCC[i] == inSCC[M[maried[i].second]]) {
    //   puts("Unsafe");
    // } else {
    //   puts("Safe");
    // }
    if (inSCC[i] == inSCC[i + totN]) {
      puts("Unsafe");
    } else {
      puts("Safe");
    }
  }
  return 0;
} // Thomitics Code