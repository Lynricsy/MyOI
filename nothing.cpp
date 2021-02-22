#include <cstdio>
#include <algorithm>
#define N (1000000 + 10)
using namespace std;
int a[N], nxt[N], head[N], dfn[N], low[N], cnt, k;
bool cut[N], bst[N];
void add(int x, int y)
{
    a[++k] = y;
    nxt[k] = head[x];
    head[x] = k;
}
void tarjan(int u, int mr)
{
    int rc = 0;
    dfn[u] = low[u] = ++cnt;
    for (int p = head[u]; p; p = nxt[p])
    {
        int v = a[p];
        if (!dfn[v])
        {
            tarjan(v, mr);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u] && u != mr)
                cut[u] = true;
            if (u == mr)
                rc++;
        }
        low[u] = min(low[u], dfn[v]);
    }
    if (u == mr && rc >= 2)
        cut[mr] = true;
}
int main()
{
    int n, m, ans = 0;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        add(x, y);
        add(y, x);
    }
    for (int i = 1; i <= n; i++)
    {
        if (!dfn[i])
            tarjan(i, i);
    }
    for (int i = 1; i <= n; i++)
        if (cut[i])
            ans++;
    printf("%d\n", ans);
    for (int i = 1; i <= n; i++)
        if (cut[i])
            printf("%d ", i);
}