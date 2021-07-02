#include <bits/stdc++.h>
#define INF 999999999
#define arand() rand() % 114514
#define mrg() rot = merge(X, Y)

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

const long long maxN = 90;
long long totN;
long long totK;
long long nums[maxN];
long long sum[maxN];
priority_queue<long long> Q;

struct Node
{
    long long lch, rch;
    long long val, siz;
    long long rnd;
} nodes[maxN];

long long X, Y, Z;
long long rot;
long long cnt;
long long totANS;

void update(long long nowX)
{
    nodes[nowX].siz = nodes[nodes[nowX].lch].siz + nodes[nodes[nowX].rch].siz + 1;
}

long long merge(long long Atree, long long Btree)
{
    if ((!Atree) || (!Btree))
    {
        return Atree + Btree;
    }
    else if (nodes[Atree].rnd < nodes[Btree].rnd)
    {
        nodes[Atree].rch = merge(nodes[Atree].rch, Btree);
        update(Atree);
        return Atree;
    }
    else
    {
        nodes[Btree].lch = merge(Atree, nodes[Btree].lch);
        update(Btree);
        return Btree;
    }
}

void split(long long splitX, long long K, long long &Xtree, long long &Ytree)
{
    if (!splitX)
    {
        Xtree = Ytree = 0;
        return;
    }
    else
    {
        if (nodes[splitX].val <= K)
        {
            Xtree = splitX;
            split(nodes[splitX].rch, K, nodes[splitX].rch, Ytree);
        }
        else
        {
            Ytree = splitX;
            split(nodes[splitX].lch, K, Xtree, nodes[splitX].lch);
        }
        update(splitX);
    }
}
long long Kth(long long KX, long long K)
{
    while (1)
    {
        if (K <= nodes[nodes[KX].lch].siz)
        {
            KX = nodes[KX].lch;
        }
        else if (K == nodes[nodes[KX].lch].siz + 1)
        {
            return KX;
        }
        else
        {
            K -= nodes[nodes[KX].lch].siz + 1;
            KX = nodes[KX].rch;
        }
    }
}

void del(long long delX)
{
    split(rot, delX, X, Z);
    split(X, delX - 1, X, Y);
    Y = merge(nodes[Y].lch, nodes[Y].rch);
    rot = merge(merge(X, Y), Z);
}

void insert(long long nowX)
{
    split(rot, nowX, X, Y);
    ++cnt;
    nodes[cnt].lch = nodes[cnt].rch = 0;
    nodes[cnt].val = nowX;
    nodes[cnt].siz = 1;
    nodes[cnt].rnd = arand();
    rot = merge(merge(X, cnt), Y);
}

long long pre(long long nowX)
{
    split(rot, nowX - 1, X, Y);
    return Kth(X, nodes[X].siz);
}
long long nxt(long long nowX)
{
    split(rot, nowX, X, Y);
    return Kth(Y, 1);
}
long long thK(long long nowX)
{
    split(rot, nowX , X, Y);
    return nodes[X].siz - 1;
}

int main()
{
    totN = read();
    totK = read();
    for (long long i = 1; i <= totN; ++i)
    {
        nums[i] = read() - totK;
        sum[i] = nums[i] + sum[i - 1];
    }
    for (int i = 1; i <= totN; ++i)
    {
        insert(sum[i]);
        totANS += thK(sum[i]) ;
        if (sum[i] >= 0)
        {
            ++totANS;
        }
    }
    write(totANS);
    return 0;
} //Thomitics Code