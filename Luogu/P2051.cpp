/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
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

const long long maxN = 109;
const long long MOD = 9999973;

long long totN;
long long totM;
long long DP[maxN][maxN][maxN];
long long jie[maxN];
long long totANS;

void init() {
  jie[0] = 1;
  for (int i = 1; i <= 106; ++i) {
    jie[i] = jie[i - 1] * i % MOD;
  }
}

// long long C(long long n, long long m) {
//   if (n < m)
//     return 0;
//   if (n == m) {
//     return 1;
//   }
//   return jie[n] * C(n - m, m) % MOD * C(n - m, m - 1) % MOD;
// }

long long C2(long long x) { return (x * (x - 1) / 2) % MOD; }

int main() {
  totN = read();
  totM = read();
  DP[0][0][0] = 1;
  for (int i = 1; i <= totN; ++i) {
    for (int j = 0; j <= totM; ++j) {
      for (int k = 0; k <= totM - j; ++k) {
        DP[i][j][k] = DP[i - 1][j][k];
        if (k >= 1) {
          DP[i][j][k] += DP[i - 1][j + 1][k - 1] * (j + 1) % MOD;
        }
        if (j >= 1) {
          DP[i][j][k] += DP[i - 1][j - 1][k] * (totM - (j - 1) - k) % MOD;
        }
        if (j >= 2) {
          DP[i][j][k] += DP[i - 1][j - 2][k] * C2((totM - (j - 2) - k)) % MOD;
        }
        if (k >= 2) {
          DP[i][j][k] += DP[i - 1][j + 2][k - 2] * C2(j + 2) % MOD;
        }
        if (k >= 1) {
          DP[i][j][k] +=
              DP[i - 1][j - 1 + 1][k - 1] * (totM - j - (k - 1)) * j % MOD;
        }
        DP[i][j][k] %= MOD;
      }
    }
  }
  for (int i = 0; i <= totM; ++i) {
    for (int j = 0; j <= totM; ++j) {
      totANS += DP[totN][i][j];
      totANS %= MOD;
    }
  }
  write(totANS);
  return 0;
} // Thomitics Code