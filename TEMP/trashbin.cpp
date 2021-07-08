#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <math.h>
#include <vector>
#include <queue>
#define ll long long

const ll maxn = 1e5 + 10;
ll n, m, tim;
ll w[maxn], dfn[maxn], rk[maxn], fa[maxn], dis[maxn], son[maxn], top[maxn], siz[maxn];
std::vector<ll> e[maxn];
char s[10];

struct node
{
    ll l, r, v, lv, rv, tag;
    node *ls, *rs;

    inline void pushup()
    {
        v = ls->v + rs->v;
        if (ls->rv == rs->lv)
        {
            v -= 1;
        }
        lv = ls->lv;
        rv = rs->rv;
    }
    inline void maketag(ll w)
    {
        v = 1;
        lv = rv = tag = w;
    }
    inline void pushdown()
    {
        if (!tag)
            return;
        else
        {
            ls->maketag(tag);
            rs->maketag(tag);
            tag = 0;
        }
        return;
    }
    inline bool inrange(const ll L, const ll R)
    {
        return (L <= l) && (r <= R);
    }
    inline bool outofrange(const ll L, const ll R)
    {
        return (l > R) || (L > r);
    }
    inline void upd(const ll L, const ll R, const ll w)
    {
        if (inrange(L, R))
        {
            maketag(w);
            return;
        }
        else if (!outofrange(L, R))
        {
            pushdown();
            ls->upd(L, R, w);
            rs->upd(L, R, w);
            pushup();
        }
        return;
    }
    inline ll qry(const ll L, const ll R)
    {
        if (inrange(L, R))
        {
            return v;
        }
        else if (outofrange(L, R))
            return 0;

        pushdown();

        ll mid = (l + r) >> 1;
        if (R <= mid)
            return ls->qry(L, R);
        if (L > mid)
            return rs->qry(L, R);
        ll ret = ls->qry(L, R) + rs->qry(L, R);

        if (ls->rv == rs->lv)
            ret--;

        return ret;
    }
    inline ll fid(const ll w)
    {
        if (l == r)
            return lv;
        if (tag)
            pushdown();
        ll m = (l + r) >> 1;
        if (w <= m)
            return ls->fid(w);
        else
            return rs->fid(w);
    }
};

node mem[maxn << 1];
node *pool = mem;
node *rot;

inline node *New(const ll L, const ll R)
{
    node *u = pool++;
    u->l = L, u->r = R;
    if (L == R)
    {
        u->lv = u->rv = w[rk[L]];
        u->v = 1;
        u->tag = 0;
        u->ls = u->rs = NULL;
    }
    else
    {
        ll M = (L + R) >> 1;
        u->ls = New(L, M);
        u->rs = New(M + 1, R);
        u->pushup();
    }
    return u;
}

inline void dfs1(ll x, ll f)
{
    dis[x] = dis[f] + 1;
    fa[x] = f;
    siz[x] = 1;

    for (int i = 0; i < e[x].size(); i++)
    {
        ll y = e[x][i];

        if (y == f)
            continue;

        dfs1(y, x);

        siz[x] += siz[y];

        if (!son[x] || siz[son[x]] < siz[y])
        {
            son[x] = y;
        }
    }
}

inline void dfs2(ll x, ll f)
{
    dfn[x] = ++tim;
    rk[tim] = x;
    top[x] = f;

    if (son[x])
    {
        dfs2(son[x], f);
    }
    else
        return;

    for (int i = 0; i < e[x].size(); i++)
    {
        ll y = e[x][i];

        if (y == son[x] || y == fa[x])
            continue;

        dfs2(y, y);
    }
}

inline void update(ll x, ll y, ll w)
{
    while (top[x] != top[y])
    {
        if (dis[top[x]] <= dis[top[y]])
            std::swap(x, y);
        rot->upd(dfn[top[x]], dfn[x], w);
        x = fa[top[x]];
    }
    if (dfn[x] > dfn[y])
        std::swap(x, y);
    rot->upd(dfn[x], dfn[y], w);
}

inline ll query(ll x, ll y)
{
    ll ret = 0;
    while (top[x] != top[y])
    {
        //		puts("1");

        if (dis[top[x]] < dis[top[y]])
            std::swap(x, y);
        //	printf("p%lld %lld %lld\n",x,top[x],fa[top[x]]);
        ret += rot->qry(dfn[top[x]], dfn[x]);
        ll z1 = rot->fid(dfn[top[x]]);
        ll z2 = rot->fid(dfn[fa[top[x]]]);
        x = fa[top[x]];

        if (z1 == z2)
            ret--;
    }
    if (dfn[x] > dfn[y])
        std::swap(x, y);
    ret += rot->qry(dfn[x], dfn[y]);

    return ret;
}

int main(void)
{
    scanf("%lld %lld", &n, &m);

    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", w + i);
    }

    for (int i = 1; i < n; i++)
    {
        ll x, y;
        scanf("%lld %lld", &x, &y);

        e[x].push_back(y);
        e[y].push_back(x);
    }

    dfs1(1, 0);
    dfs2(1, 1);

    rot = New(1, n);

    for (int i = 1; i <= m; i++)
    {
        ll x, y, z;
        scanf("%s", s);
        scanf("%lld%lld", &x, &y);

        if (s[0] == 'Q')
        {
            printf("%lld\n", query(x, y));
        }
        else
        {
            scanf("%lld", &z);
            update(x, y, z);
        }
    }

    return 0;
}