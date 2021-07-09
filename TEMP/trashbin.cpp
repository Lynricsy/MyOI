#include <set>
#include <map>
#include <queue>
#include <cmath>
#include <ctime>
#include <stack>
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <functional>
#define inf 0x3fffffff
#define ls p * 2
#define rs p * 2 + 1
#define fi first
#define se second
#define pb push_back
#define mp make_pair
using namespace std;

typedef long long ll;
typedef pair<long long, long long> pi;
typedef vector<long long> vi;
typedef unsigned long long ui;

long long rd()
{
    long long res = 0, fl = 1;
    char c = getchar();
    while (!isdigit(c))
    {
        if (c == '-')
            fl = -1;
        c = getchar();
    }
    while (isdigit(c))
    {
        res = (res << 3) + (res << 1) + c - '0';
        c = getchar();
    }
    return res * fl;
}

const long long maxn = 1000090;
long long  trie[maxn * 25][2], root[maxn], cnt, lst[maxn * 25];
string op;
long long n, m, x, s[maxn], l, r;
void insert(long long timepost, long long val, long long k, long long nownode, long long lstnode)
{
    if (k < 0)
    {
        lst[nownode] = timepost;
        return;
    }
    long long c = (val >> k) & 1;
    trie[nownode][c] = ++cnt;
    if (trie[lstnode][c ^ 1])
    {
        trie[nownode][c ^ 1] = trie[lstnode][c ^ 1];
    }
    insert(timepost, val, k - 1, trie[nownode][c], trie[lstnode][c]);
    lst[nownode] = max(lst[trie[nownode][0]], lst[trie[nownode][1]]);
    return;
}

long long query(long long timepost, long long val, long long k, long long nownode)
{
    if (k < 0)
    {
        return lst[nownode];
        //        return s[lst[nownode]];
    }
    long long c = val >> k & 1;
    if (lst[trie[nownode][c ^ 1]] >= timepost)
    {
        return query(timepost, val, k - 1, trie[nownode][c ^ 1]);
    }
    else
        return query(timepost, val, k - 1, trie[nownode][c]);
}

int main()
{
    memset(lst, -1, sizeof(lst));
    n = rd();
    m = rd();
    root[0] = ++cnt;
    for (long long i = 1; i <= n; ++i)
    {
        x = rd();
        s[i] = s[i - 1] ^ x;
        root[i] = ++cnt;
        insert(i, s[i], 24, root[i], root[i - 1]);
    }
    for (long long i = 1; i <= m; ++i)
    {
        cin >> op;
        if (op[0] == 'A')
        {
            x = rd();
            s[++n] = s[n - 1] ^ x;
            root[n] = ++cnt;
            insert(n, s[n], 24, root[n], root[n - 1]); //cout << "\n";
        }
        else if (op[0] == 'Q')
        {
            l = rd();
            r = rd();
            x = rd();
            ll ans = 0ll ^ s[n] ^ x ^ s[query(l - 1, x ^ s[n], 24, root[r - 1])];
            printf("%lld\n", ans);
        }
    }
    return 0;
}