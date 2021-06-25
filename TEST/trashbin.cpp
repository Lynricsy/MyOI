#include <iostream>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <cstdlib>

#define maxn 500001

using namespace std;
int siz[maxn], ch[maxn][2], fix[maxn], val[maxn];
int T, cnt, n, m, x, y, z, p, a, root, com;

inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (c > '9' || c < '0')
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x * f;
}

inline void update(int x)
{
    siz[x] = 1 + siz[ch[x][0]] + siz[ch[x][1]];
}
inline int new_node(int x)
{
    siz[++cnt] = 1;
    val[cnt] = x;
    fix[cnt] = rand();
    return cnt;
}

int merge(int A, int B)
{
    if (!A || !B)
        return A + B;
    if (fix[A] < fix[B])
    {
        ch[A][1] = merge(ch[A][1], B);
        update(A);
        return A;
    }
    else
    {
        ch[B][0] = merge(A, ch[B][0]);
        update(B);
        return B;
    }
}

void split(int now, int k, int &x, int &y)
{
    if (!now)
        x = y = 0;
    else
    {
        if (val[now] <= k)
            x = now, split(ch[now][1], k, ch[now][1], y);
        else
            y = now, split(ch[now][0], k, x, ch[now][0]);
        update(now);
    }
}

int kth(int now, int k)
{
    while (1)
    {
        if (k <= siz[ch[now][0]])
            now = ch[now][0];
        else if (k == siz[ch[now][0]] + 1)
            return now;
        else
            k -= siz[ch[now][0]] + 1, now = ch[now][1];
    }
}

int main()
{
    srand((unsigned)time(NULL));
    T = read();
    while (T--)
    {
        p = read();
        a = read();
        if (p == 1)
        {
            split(root, a, x, y);
            root = merge(merge(x, new_node(a)), y);
        }
        else if (p == 2)
        {
            split(root, a, x, z);
            split(x, a - 1, x, y);
            y = merge(ch[y][0], ch[y][1]);
            root = merge(merge(x, y), z);
        }
        else if (p == 3)
        {
            split(root, a - 1, x, y);
            printf("%d\n", siz[x] + 1);
            root = merge(x, y);
        }
        else if (p == 4)
            printf("%d\n", val[kth(root, a)]);
        else if (p == 5)
        {
            split(root, a - 1, x, y);
            printf("%d\n", val[kth(x, siz[x])]);
            root = merge(x, y);
        }
        else
        {
            split(root, a, x, y);
            printf("%d\n", val[kth(y, 1)]);
            root = merge(x, y);
        }
    }
    return 0;
}