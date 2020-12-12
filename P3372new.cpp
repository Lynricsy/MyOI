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
long long totQ;
long long nums[100090];
struct Node
{
    Node *lch, *rch;
    long long tag;
    long long val;
    long long l, r;
    Node(long long _l, long long _r)
    {
        l = _l;
        r = _r;
        tag = 0;
        if (_l == _r)
        {
            val = nums[_l];
            lch = rch = NULL;
        }
        else
        {
            int Mid = (l + r) >> 1;
            lch = new Node(l, Mid);
            rch = new Node(Mid+1, r);
            push_up();
        }
    }
    void push_up()
    {
        val = lch->val + rch->val;
    }
    void maketag(long long w)
    {
        val += (r - l + 1) * w;
        tag += w;
    }
    void push_down()
    {
        if (!tag)
        {
            return;
        }
        lch->maketag(tag);
        rch->maketag(tag);
        tag = 0;
    }
    bool in_range(long long _l, long long _r)
    {
        return (_l <= l) && (r <= _r);
    }
    bool out_of_range(long long _l, long long _r)
    {
        return (_r < l) || (_l > r);
    }
    void update(long long _l, long long _r, long long w)
    {
        if (in_range(_l, _r))
        {
            maketag(w);
        }
        else if (!out_of_range(_l, _r))
        {
            push_down();
            lch->update(_l, _r, w);
            rch->update(_l, _r, w);
            push_up();
        }
    }
    long long query(long long _l, long long _r)
    {
        if (in_range(_l, _r))
        {
            return val;
        }
        if (out_of_range(_l, _r))
        {
            return 0;
        }
        push_down();
        return lch->query(_l, _r) + rch->query(_l, _r);
    }
};

int main()
{
    totN = read();
    totQ = read();
    for (int i = 1; i <= totN; i++)
    {
        nums[i] = read();
    }
    Node *rot = new Node(1, totN);
    for (int i = 1; i <= totQ; i++)
    {
        int tmp = read() - 1;
        if (!tmp)
        {
            int x = read();
            int y = read();
            int z = read();
            rot->update(x, y, z);
        }
        else
        {
            int x = read();
            int y = read();
            write(rot->query(x, y));
            putchar('\n');
        }
    }

    return 0;
} //LikiBlaze Code