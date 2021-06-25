#include <bits/stdc++.h>
#define INF 999999999
#define arand() rand() % 114514

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
struct Node
{
    Node *lch, *rch;
    long long val;
    long long siz;
    long long rnd;
    void update()
    {
        siz = lch->siz + rch->siz + 1;
    }
    void spilt(long long k, Node *&lc, Node *&rc)
    {
        if (val <= k)
        {
            lc = this;
            rch->spilt(k, rch, rc);
        }
        else
        {
            rc = this;
            lch->spilt(k, lc, lch);
        }
        update();
    }
    Node(long long w)
    {
        val = w;
        rnd = arand();
        siz = 1;
        lch = rch = NULL;
    }
};

Node *x, *y, *z;

auto merge(Node *xa, Node *ya)
{
    if ((xa == NULL) || (ya == NULL))
    {
        if (xa == NULL)
        {
            return ya;
        }
        if (ya == NULL)
        {
            return ya;
        }
    }
    if (xa->rnd < ya->rnd)
    {
        merge(xa->rch, ya);
        xa->update();
        return xa;
    }
    else
    {
        merge(xa->lch, ya);
        xa->update();
        return xa;
    }
}
long long Kth(Node *nowx, long long k)
{
    if (!nowx)
    {
        return 0;
    }
    if (nowx->siz > k)
    {
        return Kth(nowx->lch, k);
    }
    else if (k == nowx->siz)
    {
        return nowx->val;
    }
    else
    {
        return Kth(nowx->rch, k - nowx->siz);
    }
}

int main()
{
    totN = read();
    Node *rot = new Node(INF);
    srand(time(NULL));
    for (int i = 1,readx,readY; i <= totN; i++)
    {
        readx=read();
        if (readx==1)
        {
            readY=read();
            Node *tmpnew= new Node(readY);
            rot->spilt(readY,x,y);
            merge(merge(x,tmpnew),y);
        }
        else if (readx==2)
        {
            readY=read();
            rot->spilt(readY,x,z);
            x->spilt(readY-1, x, y);
            y=merge(x->lch,x->rch);
            rot=merge(merge(x,y),z);
        }
        else if(readx==3)
        {
            readY=read();
            rot->spilt(readY,x,y);
            write(x->siz+1);
            rot=merge(x,y);
        }
        else if (readx==4)
        {
            readY=read();
            write(Kth(rot,readY));
        }
        else if(readx==5)
        {
            readY=read();
            rot->spilt(readY-1,x,y);
            write(Kth(x,x->siz));
            rot=merge(x,y);
        }
        else if(readx==6)
        {
            readY=read();
            rot->spilt(readY-1,x,y);
            write(Kth(y,1));
            rot=merge(x,y);
        }
    }

    return 0;
} //Thomitics Code