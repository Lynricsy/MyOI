/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <algorithm>
#include <bits/stdc++.h>
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
template <typename T> inline void write(T x) {
  if (x < 0ll) {
    putchar('-');
    x = -x;
  }
  if (x > 9ll)
    write(x / 10ll);
  putchar(x % 10ll + '0');
}

const long long maxN = 90;
long long totN;
long long totC;
long long sum[maxN];
long long DP[maxN][maxN][2];
long long pos[maxN];
long long w[maxN];

int main() {
  totN = read();
  totC = read();
  memset(DP, 0x3f, sizeof(DP));
  for (int i = 1; i <= totN; ++i) {
    pos[i] = read();
    w[i] = read();
    sum[i] = sum[i - 1] + w[i];
  }
  DP[totC][totC][0] = 0;
  DP[totC][totC][1] = 0;
  for (int l = 2; l <= totN; ++l) {
    for (int i = 1; i + l - 1 <= totN; ++i) {
      long long j = i + l - 1;
      DP[i][j][0] = min(DP[i + 1][j][0] + (sum[totN] - sum[j] + sum[i]) *
                                              (pos[i + 1] - pos[i]),
                        DP[i + 1][j][1] +
                            (sum[totN] - sum[j] + sum[i]) * (pos[j] - pos[i]));
      DP[i][j][1] =
          min(DP[i][j - 1][1] +
                  (sum[totN] - sum[j - 1] + sum[i - 1]) * (pos[j] - pos[j - 1]),
              DP[i][j - 1][0] +
                  (sum[totN] - sum[j - 1] + sum[i - 1]) * (pos[j] - pos[i]));
    }
  }
  write(min(DP[1][totN][0], DP[1][totN][1]));
  return 0;
} // Thomitics Code