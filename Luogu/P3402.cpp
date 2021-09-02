/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
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

const long long maxN = 3000090;
struct Node {
  long long lch, rch;
} nodes[maxN];
long long fa[maxN];
long long depth[maxN];
long long cntRT;
long long totN;
long long totM;
long long vers[maxN];

void build(long long &rot, long long l, long long r) {
  rot = ++cntRT;
  if (l == r) {
    fa[rot] = l;
    return;
  }
  long long mid = (l + r) >> 1;
  build(nodes[rot].lch, l, mid);
  build(nodes[rot].rch, mid + 1, r);
}

void update(long long &rot, long long l, long long r, long long pos,
            long long fath, long long last) {
  rot = ++cntRT;
  if (l == r) {
    fa[rot] = fath;
    depth[rot] = depth[last];
    return;
  }
  nodes[rot].lch = nodes[last].lch;
  nodes[rot].rch = nodes[last].rch;
  long long mid = (l + r) >> 1;
  if (pos <= mid)
    update(nodes[rot].lch, l, mid, pos, fath, nodes[last].lch);
  else
    update(nodes[rot].rch, mid + 1, r, pos, fath, nodes[last].rch);
}

long long query(long long &rot, long long l, long long r, long long pos) {
  if (l == r)
    return rot;
  long long mid = (l + r) >> 1;
  if (pos <= mid)
    return query(nodes[rot].lch, l, mid, pos);
  else
    return query(nodes[rot].rch, mid + 1, r, pos);
}

void add(long long &rot, long long l, long long r, long long pos) {
  if (l == r) {
    depth[rot]++;
    return;
  }
  long long mid = (l + r) >> 1;
  if (pos <= mid)
    add(nodes[rot].lch, l, mid, pos);
  else
    add(nodes[rot].rch, mid + 1, r, pos);
}

long long get_fa(long long ed, long long nowX) {
  long long nfa = query(ed, 1, totN, nowX);
  if (nowX == fa[nfa]) {
    return nfa;
  }
  return get_fa(ed, fa[nfa]);
}

int main() {
  totN = read();
  totM = read();
  build(vers[0], 1, totN);
  for (long long i = 1, wor, x, y, k; i <= totM; i++) {
    wor = read();
    if (wor == 1) {
      vers[i] = vers[i - 1];
      x = read();
      y = read();
      long long fathX = get_fa(vers[i], x);
      long long fathY = get_fa(vers[i], y);
      if (fa[fathX] == fa[fathY]) {
        continue;
      }
      if (depth[fathX] > depth[fathY]) {
        swap(fathX, fathY);
      }
      update(vers[i], 1, totN, fa[fathX], fa[fathY], vers[i - 1]);
      if (depth[fathX] == depth[fathY]) {
        add(vers[i], 1, totN, fa[fathY]);
      }
    }
    if (wor == 2) {
      k = read();
      vers[i] = vers[k];
    }
    if (wor == 3) {
      vers[i] = vers[i - 1];
      x = read();
      y = read();
      long long fathX = get_fa(vers[i], x);
      long long fathY = get_fa(vers[i], y);
      if (fa[fathX] == fa[fathY]) {
        puts("1");
      } else {
        puts("0");
      }
    }
  }
  return 0;
} // Thomitics Code