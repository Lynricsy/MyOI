#include <bits/stdc++.h>

using namespace std;

inline long long read()
{
    long long x = 0;
    int f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
void write(const long long &x)
{
    if (!x)
    {
        putchar('0');
        return;
    }
    char f[100];
    long long tmp = x;
    if (tmp < 0)
    {
        tmp = -tmp;
        putchar('-');
    }
    long long s = 0;
    while (tmp > 0)
    {
        f[s++] = tmp % 10 + '0';
        tmp /= 10;
    }
    while (s > 0)
    {
        putchar(f[--s]);
    }
}
inline double dread()
{
    double r;
    double x = 0, t = 0;
    int s = 0, f = 1;
    char c = getchar();
    for (; !isdigit(c); c = getchar())
    {
        if (c == '-')
        {
            f = -1;
        }
        if (c == '.')
        {
            goto readt;
        }
    }
    for (; isdigit(c) && c != '.'; c = getchar())
    {
        x = x * 10 + c - '0';
    }
    readt:
    for (; c == '.'; c = getchar())
        ;
    for (; isdigit(c); c = getchar())
    {
        t = t * 10 + c - '0';
        ++s;
    }
    r = (x + t / pow(10, s)) * f;
    return r;
}

inline void dwrite(long long x)
{
    if (x == 0)
    {
        putchar(48);
        return;
    }
    int bit[20], p = 0, i;
    for (; x; x /= 10)
        bit[++p] = x % 10;
    for (i = p; i > 0; --i)
        putchar(bit[i] + 48);
}
inline void write(double x, int k)
{
    static int n = pow(10, k);
    if (x == 0)
    {
        putchar('0');
        putchar('.');
        for (int i = 1; i <= k; ++i)
            putchar('0');
        return;
    }
    if (x < 0)
        putchar('-'), x = -x;
    long long y = (long long)(x * n) % n;
    x = (long long)x;
    dwrite(x), putchar('.');
    int bit[10], p = 0, i;
    for (; p < k; y /= 10)
        bit[++p] = y % 10;
    for (i = p; i > 0; i--)
        putchar(bit[i] + 48);
}

long long totN;
struct Node
{
    double x;
    double y;
} nodes[100090];
Node pt[100090];
Node pts[100090];
stack<Node> S;
long double totANS;
double dist(Node x, Node y)
{
    return sqrt((x.x - y.x) * (x.x - y.x) + (x.y - y.y) * (x.y - y.y));
}
double cp(Node pa1, Node pa2, Node pb1, Node pb2)
{
    return (pa2.x - pa1.x) * (pb2.y - pb1.y) - (pb2.x - pb1.x) * (pa2.y - pa1.y);
}
bool cmp(Node x, Node y)
{
    double cmpN = cp(pt[1], x, pt[1], y);
    if (cmpN > 0)
    {
        return true;
    }
    else if (cmpN == 0 && dist(pt[0], x) < dist(pt[0], y))
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    totN = read();
    for (int i = 1; i <= totN; i++)
    {
        scanf("%lf", &pt[i].x);
        scanf("%lf", &pt[i].y);
        if (i != 1 && pt[i].y < pt[1].y)
        {
            swap(pt[i].y, pt[1].y);
            swap(pt[i].x, pt[1].x);
        }
    }
    sort(pt + 2, pt + totN + 1, cmp);
    int ht = 1;
    pts[1]=pt[1];
    for (int i = 2; i <= totN; i++)
    {
        while (ht>1 && cp(pts[ht - 1], pts[ht], pts[ht], pt[i]) <= 0)
        {
            --ht;
        }
        ++ht;
        pts[ht] = pt[i];
    }
    pts[ht+1]=pt[1];
    for (int i = 1; i <= ht; ++i)
    {
        totANS+=dist(pts[i],pts[i+1]);
    }
    //write(totANS,2);
    printf("%.2lf",totANS);
    return 0;
} //LikiBlaze Code