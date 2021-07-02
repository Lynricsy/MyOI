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

#ifdef THODEBUG
const long long maxN = 90;
#else
const long long maxN = 100090;
#endif

long long totN;
long long nums[maxN];
struct Node
{
    long long ID;
    long long num;
};

stack<Node> S;
long long sum[maxN];
long long DP[maxN];
long long totANS;

int main()
{
    totN = read();
    for (int i = 1; i <= totN; ++i)
    {
        nums[i] = read();
        sum[i] = nums[i] + sum[i - 1];
    }
    for (int i = 1; i <= totN; ++i)
    {
        while (!S.empty() and S.top().num > nums[i])
        {
            DP[S.top().ID] += (sum[i - 1] - sum[S.top().ID]);
            S.pop();
        }
        if (!S.empty())
        {
            DP[i] = sum[i] - sum[S.top().ID];
        }
        else
        {
            DP[i] = sum[i];
        }
        S.push({i, nums[i]});
    }
    for (int i = 1; i <= totN; ++i)
    {
        totANS = max(totANS, DP[i] * nums[i]);
    }
    write(totANS);
    return 0;
} //Thomitics Code