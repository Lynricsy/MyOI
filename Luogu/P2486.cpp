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
long long totM;
long long col[maxN];
long long totR;
long long num[maxN];
long long nums[maxN];
long long Sson[maxN];
long long top[maxN];
long long siz[maxN];
long long ID[maxN];
long long fath[maxN];
long long depth[maxN];
long long cntNODE;
long long preL;
long long preR;

struct Edge
{
    long long to;
    long long nxt;
} edges[maxN];
long long cnt_edges;
long long head[maxN];
void add_edge(long long x, long long y)
{
    ++cnt_edges;
    edges[cnt_edges].nxt = head[x];
    head[x] = cnt_edges;
    edges[cnt_edges].to = y;
}

void DFS1(long long x, long long fa, long long dep)
{
    long long max = -1;
    depth[x] = dep;
    fath[x] = fa;
    siz[x] = 1;
    for (int i = head[x]; i; i = edges[i].nxt)
    {
        long long vir = edges[i].to;
        if (vir == fa)
        {
            continue;
        }
        DFS1(vir, x, dep + 1);
        siz[x] += siz[vir];
        if (max < siz[vir])
        {
            max = siz[vir];
            Sson[x] = vir;
        }
    }
}

void DFS2(long long x, long long nowTOP)
{
    ++cntNODE;
    ID[x] = cntNODE;
    top[x] = nowTOP;
    // num[cntNODE] = x;
    if (!Sson[x])
    {
        return;
    }
    DFS2(Sson[x], nowTOP);
    for (int i = head[x]; i; i = edges[i].nxt)
    {
        long long vir = edges[i].to;
        if (vir == Sson[x] || vir == fath[x])
        {
            continue;
        }
        DFS2(vir, vir);
    }
}

struct Node
{
    long long l, r;
    long long val;
    long long rcol, lcol;
    long long tag;
    Node *lch, *rch;
    void pushup()
    {
        val = lch->val + rch->val;
        if (lch->rcol == rch->lcol)
        {
            --val;
        }
        lcol = lch->lcol;
        rcol = rch->rcol;
    }
    Node(long long L, long long R)
    {
        l = L;
        r = R;
        tag = 0;
        if (l == r)
        {
            rcol = lcol = col[ID[l]];
            val = 1;
            lch = rch = NULL;
            return;
        }
        long long Mid = (L + R) >> 1;
        lch = new Node(L, Mid);
        rch = new Node(Mid + 1, R);
        pushup();
    }
    inline void maketag()
    {
        tag = 1;
        val = 1;
    }
    void pushdown()
    {
        if (tag)
        {
            val = 1;
            lch->maketag();
            rch->maketag();
            lch->lcol = lch->rcol = rch->lcol = lch->rcol = lcol;
            tag = 0;
        }
    }
    inline bool INrange(long long L, long long R)
    {
        return (L <= l) && (r <= R);
    }
    inline bool OUTrange(long long L, long long R)
    {
        return (l > R) || (L > r);
    }
    void update(long long L, long long R, long long w)
    {
        if (INrange(L, R))
        {
            maketag();
            lcol = rcol = w;
        }
        else if (!OUTrange(L, R))
        {
            pushdown();
            lch->update(L, R, w);
            rch->update(L, R, w);
            pushup();
        }
    }
    long long query(long long L, long long R)
    {
        if (L == l)
        {
            preL = lcol;
        }
        if (R == r)
        {
            preR = rcol;
        }
        if (INrange(L, R))
        {
            return val;
        }
        else if (OUTrange(L, R))
        {
            return 0;
        }
        pushdown();
        if (R <= lch->r)
        {
            return lch->query(L, R);
        }
        else if (L >= rch->l)
        {
            return rch->query(L, R);
        }
        if (lch->rcol == rch->lcol)
        {
            return lch->query(L, R) + rch->query(L, R) - 1;
        }
        else
        {
            return lch->query(L, R) + rch->query(L, R);
        }
    }
    long long fid(long long w)
    {
        if (l == r)
        {
            return lcol;
        }
        if (tag)
        {
            pushdown();
        }
        if (w <= lch->l)
        {
            return lch->fid(w);
        }
        else
        {
            return rch->fid(w);
        }
    }
};

Node *rot;

long long qRANGE(long long x, long long y)
{
    long long ansL = -1, ansR = -1;
    long long nowANS = 0;
    while (top[x] != top[y])
    {
        if (depth[top[x]] < depth[top[y]])
        {
            swap(x, y);
        }
        nowANS += rot->query(ID[top[x]], ID[x]);

        // if (preR == ansL)
        // {
        //     --nowANS;
        // }
        x = fath[top[x]];
        if (rot->fid(ID[top[x]]) == rot->fid(ID[fath[top[x]]]))
        {
            --nowANS;
        }

        // ansL = preL;
    }
    if (depth[x] < depth[y])
    {
        swap(x, y);
        swap(ansL, ansR);
    }
    nowANS += rot->query(ID[y], ID[x]);
    // if (preL == ansR)
    // {
    //     --nowANS;
    // }
    // if (preR == ansL)
    // {
    //     --nowANS;
    // }
    return nowANS;
}
void updRANGE(long long x, long long y, long long k)
{
    while (top[x] != top[y])
    {
        if (depth[top[x]] < depth[top[y]])
        {
            swap(x, y);
        }
        rot->update(ID[top[x]], ID[x], k);
        x = fath[top[x]];
    }
    if (depth[x] > depth[y])
    {
        swap(x, y);
    }
    rot->update(ID[x], ID[y], k);
}

int main()
{
    totN = read();
    totM = read();
    for (int i = 1; i <= totN; ++i)
    {
        col[i] = read();
    }
    for (int i = 1, x, y; i < totN; ++i)
    {
        x = read();
        y = read();
        add_edge(x, y);
        add_edge(y, x);
    }
    char ch = getchar();
    DFS1(1, 1, 1);
    DFS2(1, 1);
    rot = new Node(1, totN);
    for (int i = 1; i <= totM; ++i)
    {
        long long a, b, c;
        while (ch != 'Q' && ch != 'C')
        {
            ch = getchar();
        }
        if (ch == 'Q')
        {
            a = read();
            b = read();
            write(qRANGE(a, b));
            putchar('\n');
        }
        else
        {
            a = read();
            b = read();
            c = read();
            updRANGE(a, b, c);
        }
        ch = getchar();
    }
    return 0;
} //Thomitics Code