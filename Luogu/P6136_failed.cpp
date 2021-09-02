/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f
#define IINF 0x3f3f3f3f
#define arand() rand() % 114514
#define mrg() rot = merge(X, Y)

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
long long totANS;
long long Last;
long long totM;
struct Node {
  Node *lch, *rch;
  long long val;
  long long siz;
  long long rnd;
  void update() {
    siz = 1;
    if (lch) {
      siz += lch->siz;
    }
    if (rch) {
      siz += rch->siz;
    }
  }
  Node(long long w) {
    lch = rch = NULL;
    val = w;
    siz = 1;
    rnd = arand();
  }
};
Node *X, *Y, *Z;
Node *rot;
long long totN;
Node *merge(Node *Atree, Node *Btree) {
  if (!Atree || !Btree) {
    return !Atree ? Btree : Atree;
  } else if (Atree->rnd < Btree->rnd) {
    Atree->rch = merge(Atree->rch, Btree);
    Atree->update();
    return Atree;
  } else {
    Btree->lch = merge(Atree, Btree->lch);
    Btree->update();
    return Btree;
  }
}
void split(Node *sptTree, long long K, Node *Xtree, Node *Ytree) {
  if (!sptTree) {
    Xtree = Ytree = 0;
    return;
  } else {
    if (sptTree->val <= K) {
      Xtree = sptTree;
      split(sptTree->rch, K, sptTree->rch, Ytree);
    } else {
      Ytree = sptTree;
      split(sptTree->lch, K, Xtree, sptTree->lch);
    }
    sptTree->update();
  }
}
long long Kth(Node *nTree, long long K) {
  if (!nTree) {
    return 0;
  }
  while (true) {
    if (K <= nTree->siz) {
      nTree = nTree->lch;
    } else if (K == nTree->siz + 1) {
      return nTree->val;
    } else {
      K -= nTree->siz + 1;
      nTree = nTree->rch;
    }
  }
}
void del(long long K) {
  split(rot, K, X, Z);
  split(X, K - 1, X, Y);
  Y = merge(Y->lch, Y->rch);
  rot = merge(merge(X, Y), Z);
}
void insert(long long K) {
  split(rot, K, X, Y);
  Node *tmp = new Node(K);
  rot = merge(merge(X, tmp), Y);
}
long long pre(long long K) {
  split(rot, K - 1, X, Y);
  return X ? Kth(X, X->siz) : 0;
}
long long nxt(long long K) {
  split(rot, K, X, Y);
  return Kth(Y, 1);
}
long long thK(long long K) {
  split(rot, K - 1, X, Y);
  return X->siz + 1;
}

int main() {
  totN = read();
  totM = read();
  for (int i = 1, x; i <= totN; ++i) {
    x = read();
    insert(x);
  }
  long long readX, readY;
  while (totM--) {
    readX = read();
    readY = read();
    switch (readX) {
    case 1:
      insert(readY ^ Last);
      break;
    case 2:
      del(readY ^ Last);
      break;
    case 3:
      totANS ^= Last = thK(readY ^ Last);
      mrg();
      break;
    case 4:
      totANS ^= Last = Kth(rot, readY ^ Last);
      break;
    case 5:
      totANS ^= Last = pre(readY ^ Last);
      mrg();
      break;
    case 6:
      totANS ^= Last = nxt(readY ^ Last);
      mrg();
      break;
    }
  }
  write(totANS);
  return 0;
} // Thomitics Code