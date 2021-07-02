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

const long long maxN = 10000090;
struct Node
{
    long long ID;
    long long num;
};

long long totN;
long long totK;
long long nums[maxN];

deque<Node> MI, MA;
long long MAXlen = -1;
long long now;

void WORK()
{
    for (long long i = 1; i <= totN; ++i)
    {
        while (!MI.empty() and MI.back().num > nums[i])
        {
            MI.pop_back();
        }
        MI.push_back({i, nums[i]});
        while (!MA.empty() and MA.back().num < nums[i])
        {
            MA.pop_back();
        }
        MA.push_back({i, nums[i]});
        while (MA.front().num - MI.front().num > totK)
        {
            if (MA.front().ID < MI.front().ID)
            {
                now=MA.front().ID;
                MA.pop_front();
            }
            else
            {
                now=MI.front().ID;
                MI.pop_front();
            }
        }
        MAXlen = max({MAXlen, i-now});
    }
}

int main()
{
    totK = read();
    totN = read();
    for (long long i = 1; i <= totN; ++i)
    {
        nums[i] = read();
    }
    WORK();
    write(MAXlen);
    return 0;
} //Thomitics Code