/**************************************************************
 * Problem: Luogu P3435
 * Author: 芊枫
 * Date: 2021 July 22
 * Algorithm: KMP
 **************************************************************/

#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
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
inline void write(const long long &x) {
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

const int MAXN = 90;
char A[MAXN], B[MAXN];
long long KMP[MAXN];
long long LA, LB;
long long totANS;

void prefix() {
  int j = 0;
  for (int i = 2; i <= LB; ++i) {
    while (j && (B[i] != B[j + 1])) {
      j = KMP[j];
    }
    if (B[i] == B[j + 1]) {
      ++j;
    }
    KMP[i] = j;
  }
}

int main() {
  LB = read();
  scanf("%s", B + 1);
  prefix();
  long long j;
  for (int i = 1; i <= LB; ++i) {
    j = i;
    while (KMP[j]) {
      j = KMP[j];
    }
    if (KMP[i]) {
      KMP[i] = j;
    }
    totANS += i - j;
  }
  write(totANS);
  return 0;
} // Thomitics Code
