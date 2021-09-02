/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <algorithm>
#include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <queue>
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

const long long maxN = 509;
long long totN;
long long totM;
long long h[maxN][maxN];
bool cbd[maxN][maxN];
bool vis[maxN][maxN];
long long delt[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
long long totNCBD;
long long L[maxN][maxN];
long long R[maxN][maxN];
long long Last = 1;
long long totANS;
bool visi[maxN][maxN];

void BFS() {
  queue<pair<long long, long long>> Q;
  for (int i = 1; i <= totM; ++i) {
    Q.push(make_pair(1, i));
    cbd[1][i] = true;
    vis[1][i] = true;
  }
  while (!Q.empty()) {
    long long xx = Q.front().first;
    long long yy = Q.front().second;
    Q.pop();
    for (int i = 0; i <= 3; ++i) {
      long long nx = xx + delt[i][1];
      long long ny = yy + delt[i][0];
      if (nx >= 1 && nx <= totN && ny >= 1 && ny <= totM &&
          h[nx][ny] < h[xx][yy] && !vis[nx][ny]) {
        vis[nx][ny] = true;
        Q.push(make_pair(nx, ny));
        cbd[nx][ny] = true;
      }
    }
  }
}

// void DFS1(long long x, long long y) {
//   if (x == totN && (h[x][y - 1] >= h[x][y] || y == 1)) {
//     L[x][y] = y;
//     return;
//   }
//   for (int i = 0; i <= 3; ++i) {
//     long long nx = x + delt[i][1];
//     long long ny = y + delt[i][0];
//     if (!L[nx][ny] && nx >= 1 && nx <= totN && ny >= 1 && ny <= totM) {
//       DFS1(nx, ny);
//     }
//     L[x][y] = min(L[x][y], L[nx][ny]);
//   }
// }

// void DFS2(long long x, long long y) {
//   if (x == totN && (h[x][y - 1] <= h[x][y] || y == totM)) {
//     R[x][y] = y;
//     return;
//   }
//   for (int i = 0; i <= 3; ++i) {
//     long long nx = x + delt[i][1];
//     long long ny = y + delt[i][0];
//     if (!R[nx][ny] && nx >= 1 && nx <= totN && ny >= 1 && ny <= totM) {
//       DFS2(nx, ny);
//     }
//     R[x][y] = max(R[x][y], R[nx][ny]);
//   }
// }

void DFS(long long x, long long y) {
  visi[x][y] = true;
  for (int i = 0; i <= 3; ++i) {
    long long nx = x + delt[i][1];
    long long ny = y + delt[i][0];
    if (nx < 1 || ny < 1 || nx > totN || ny > totM) {
      continue;
    }
    if (h[nx][ny] >= h[x][y]) {
      continue;
    }
    if (!visi[nx][ny]) {
      DFS(nx, ny);
    }
    L[x][y] = min(L[x][y], L[nx][ny]);
    R[x][y] = max(R[x][y], R[nx][ny]);
  }
}

int main() {
  totN = read();
  totM = read();
  memset(L, 0x3f, sizeof(L));
  for (int i = 1; i <= totM; ++i) {
    L[totN][i] = R[totN][i] = i;
  }
  for (int i = 1; i <= totN; ++i) {
    for (int j = 1; j <= totM; ++j) {
      h[i][j] = read();
    }
  }
  for (int i = 1; i <= totM; ++i) {
    if (!visi[1][i]) {
      DFS(1, i);
    }
  }
  BFS();
  for (int i = 1; i <= totM; ++i) {
    if (!cbd[totN][i]) {
      ++totNCBD;
    }
  }
  if (totNCBD) {
    puts("0");
    write(totNCBD);
    return 0;
  }
  while (Last <= totM) {
    long long maxR = 0;
    for (int i = 1; i <= totM; ++i) {
      if (L[1][i] <= Last) {
        maxR = max(maxR, R[1][i]);
      }
    }
    ++totANS;
    Last = maxR + 1;
  }
  puts("1");
  write(totANS);
  return 0;
} // Thomitics Code