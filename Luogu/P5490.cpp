#include <bits/stdc++.h>
#define INF 999999999

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

const long long maxN = 100090;
long long totN;
long long X[maxN << 1];
long long totT;
long long totANS;
struct Line
{
    long long l, r, h;
    long long mark;
} lines[maxN << 1];
bool operator<(Line a, Line b)
{
    return a.l < b.l;
}
struct Node
{
    Node *lch, *rch;
    long long l, r, sum;
    long long len;
    Node(long long L, long long R)
    {
        l = L;
        r = R;
        len = 0;
        sum = 0;
        long long Mid = (l + r) >> 1;
        lch = new Node(L, Mid);
        rch = new Node(Mid + 1, R);
    }
    void push_up()
    {
        if (sum)
        {
            len = X[r + 1] - X[l];
        }
        else
        {
            len=lch->len + rch->len;
        }
    }
    void update(long long L, long long R, long long c)
    {
        if (l >= R || r <= L)
        {
            return;
        }
        if (l >= L && r <= R)
        {
            sum += c;
            push_up();
            return;
        }
        lch->update(L, R, c);
        rch->update(L, R, c);
        push_up();
    }
};

int main()
{
    totN = read();
    for (int i = 1, Xa, Ya, Xb, Yb; i <= totN; i++)
    {
        Xa = read();
        Ya = read();
        Xb = read();
        Yb = read();
        X[2 * i - 1] = Xa;
        X[2 * i] = Xb;
        lines[2 * i - 1] = {Xa, Xb, Ya, 1};
        lines[2 * i - 1] = {Xa, Xb, Yb, -1};
    }
    totN <<= 1;
    sort(lines + 1, lines + totN + 1);
    sort(X + 1, X + totN + 1);
    totT = unique(X + 1, X + totN + 1) - (X + 1);
    Node *rot = new Node(1, totT - 1);
    for (int i = 1; i < totN; i++)
    {
        rot->update(lines[i].l, lines[i].r, lines[i].mark);
        totANS += rot->len * (lines[i + 1].h - lines[i].h);
    }
    delete rot;
    write(totANS);
    return 0;
} //Thomitics Code