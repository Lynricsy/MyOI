/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <type_traits>
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
long long nums[maxN];

struct Tag {
  long long cha, head;
  Tag() { cha = head = 0; }
  void clear() { cha = head = 0; }
};

bool operator!(Tag a) { return (!a.cha) && (!a.head); }

struct Node {
  long long l, r;
  long long val;
  Tag tag;
  Node *lch, *rch;
  void pushup() {}
  Node(long long L, long long R) {
    l = L;
    r = R;
    tag.clear();
    if (l == r) {
      val = nums[l];
      lch = rch = NULL;
      return;
    }
    long long Mid = (L + R) >> 1;
    lch = new Node(L, Mid);
    rch = new Node(Mid + 1, R);
    pushup();
  }
  void maketag(long long k, long long h) {
    tag.head += h;
    tag.cha += k;
    val += ((r - l) * k + 2 * h) * (r - l) / 2;
  }
  void pushdown() {
    if (!tag) {
      return;
    }
    lch->maketag(tag.cha, tag.head);
    rch->maketag(tag.cha, tag.head);
    pushup();
    tag.clear();
  }
  bool INrange(long long L, long long R) { return (L <= l) && (r <= R); }
  bool OUTrange(long long L, long long R) { return (l > R) || (L > r); }
  void update(long long L, long long R, long long k, long long h) {
    if (INrange(L, R)) {
      maketag(k, h + (l - L) * k);
    } else if (!OUTrange(L, R)) {
      pushdown();
      lch->update(L, R, k, h);
      rch->update(L, R, k, h);
      pushup();
    }
  }
  long long query(long long v) {
    if (l == r == v) {
      return val;
    } else if (v >= lch->l && v <= lch->r) {
      return lch->query(v);
    } else if (v >= rch->l && v <= rch->r) {
      return rch->query(v);
    } else {
      return 0;
    }
  }
};

int main() {
  totN = read();
  totM = read();
  for (int i = 1; i <= totN; ++i) {
    nums[i] = read();
  }

  return 0;
} // Thomitics Code
