/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <cstdio>
#include <set>
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
long long cnt;
struct Len {
  long long l, r;
};
bool operator<(Len a, Len b) { return a.r < b.l; }
set<Len> S;

int main() {
  totN = read();
  for (int i = 1; i <= totN; ++i) {
    char nowch;
    scanf(" %c", &nowch);
    if (nowch == 'A') {
      cnt = 0;
      long long x, y;
      x = read();
      y = read();
      Len tmp = (Len){x, y};
      auto it = S.find(tmp);
      while (it != S.end()) {
        S.erase(it);
        it = S.find(tmp);
        ++cnt;
      }
      S.insert(tmp);
      write(cnt);
      putchar('\n');
    }
    if (nowch == 'B') {
      write(S.size());
      putchar('\n');
    }
  }
  return 0;
} // Thomitics Code