/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <stack>
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

const long long maxN = 100090;
long long totN;
long long nums[maxN];
long long times[maxN];

struct Node {
  long long id;
  long long num;
} nodes[maxN];

stack<Node> S;

int main() {
  totN = read();
  for (int i = 1; i <= totN; ++i) {
    nodes[i].id = i;
    nodes[i].num = read();
  }
  for (int i = 1; i <= totN; ++i) {
    while (!S.empty() && S.top().num < nodes[i].num) {
      times[S.top().id] = i;
      S.pop();
    }
    S.push(nodes[i]);
  }
  for (int i = 1; i <= totN; ++i) {
    write(times[i]);
    putchar(' ');
  }
  return 0;
} // Thomitics Code