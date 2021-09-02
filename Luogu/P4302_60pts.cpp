/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
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

const long long maxN = 1090;
char str[maxN];
long long LEN;
long long cntNUM[maxN];
long long DP[maxN][maxN];

bool check(long long l, long long r, long long len) {
  for (int i = l; i <= r; ++i) {
    if (str[i] != str[(i - l) % len + l]) {
      return false;
    }
  }
  return true;
}

int main() {
  memset(DP, 0x3f, sizeof(DP));
  for (int i = 1; i <= 9; ++i) {
    cntNUM[i] = 1;
  }
  for (int i = 10; i <= 99; ++i) {
    cntNUM[i] = 2;
  }
  cntNUM[100] = 3;
  scanf("%s", str + 1);
  LEN = strlen(str + 1);
  for (int i = 1; i <= LEN; ++i) {
    DP[i][i] = 1;
  }
  for (int l = 2; l <= LEN; ++l) {
    for (int i = 1, j = i + l - 1; j <= LEN; ++i, ++j) {
      for (int k = i; k < j; ++k) {
        DP[i][j] = min(DP[i][j], DP[i][k] + DP[k + 1][j]);
      }
      for (int k = i; k < j; ++k) {
        long long len = k - i + 1;
        if (i % len != 0)
          continue;
        if (check(i, j, len)) {
          DP[i][j] = min(DP[i][j], DP[i][k] + 2 + cntNUM[l / len]);
        }
      }
    }
  }
  write(DP[1][LEN]);
  return 0;
} // Thomitics Code