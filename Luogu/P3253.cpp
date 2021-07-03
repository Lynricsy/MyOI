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

const long long maxN = 100090;
long long totN;
long long totM;
long long nums[maxN];
long long Slink;
long long totANS;

inline long long lowbit(long long x)
{
    return (x & -x);
}

void add(long long x, long long y)
{
    while (x <= totN)
    {
        nums[x] += y;
        x += lowbit(x);
    }
}

long long query(long long x)
{
    long long ans = 0;
    while (x >= 1)
    {
        ans += nums[x];
        x -= lowbit(x);
    }
    return ans;
}

struct Node
{
    long long ID;
    long long nums;
} nodes[maxN];
bool operator<(Node a, Node b)
{
    return a.nums > b.nums;
}

int main()
{
    totN = read();
    totM = read();
    for (int i = totN; i >= 1; i--)
    {
        long long x = read();
        nodes[i] = {i, x};
        add(i, 1);
    }
    for (int i = totN + 2; i <= totN + totM + 1; ++i)
    {
        long long x = read();
        nodes[i] = {i, x};
        add(i, 1);
    }
    sort(nodes + 1, nodes + totN + totM + 2);
    Slink = totN + 1;
    for (int i = 1; i <= totN + totM; ++i)
    {
        Node tpnode = nodes[i];
        // totANS += abs(query(Slink) - query(tpnode.ID)) - (tpnode.ID > Slink);
        totANS += abs(query(Slink - 1) - query(tpnode.ID));
        add(tpnode.ID, -1);
        Slink = tpnode.ID;
    }
    write(totANS);
    return 0;
} //Thomitics Code