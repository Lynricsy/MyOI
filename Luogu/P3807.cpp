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

long long jie[1000005];

long long quick_pow(long long a, long long b, long long mod) {
  long long ans = 1;
  while (b) {
    if (b & 1)
      ans = ans * a % mod;
    a = a * a % mod;
    b >>= 1;
  }
  return ans;
}

long long totP;
long long totN;
long long totM;
long long totT;

void init() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cout.setf(ios::fixed);
  cout.precision(20);
  jie[0] = 1;
  for (long long i = 1; i <= totP; ++i) {
    jie[i] = jie[i - 1] * i % totP;
  }
}

long long C(long long n, long long m) {
  if (n < m) {
    return 0;
  }
  if (n == m)
    return 1ll;
  long long ans = 1ll;
  ans = ans * jie[n] % totP;
  ans = ans * quick_pow(jie[m], totP - 2ll, totP) % totP;
  ans = ans * quick_pow(jie[n - m], totP - 2ll, totP) % totP;
  return ans;
}

long long Lucas(long long n, long long m) {
  if (n < m) {
    return 0;
  }
  if (n == m)
    return 1;
  return C(n % totP, m % totP) * Lucas(n / totP, m / totP) % totP;
}

int main() {
  totT = read();
  while (totT--) {
    totN = read();
    totM = read();
    totP = read();
    init();
    write(Lucas(totM + totN, totN));
    putchar('\n');
  }
  return 0;
} // Thomitics Code