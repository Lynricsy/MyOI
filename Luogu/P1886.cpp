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
long long totK;
long long nums[maxN];
struct Node
{
    long long TIME;
    long long num;
};

deque<Node> AQ, IQ;

void MAXAMUM()
{
    for (int i = 1; i <= totN; ++i)
    {
        while (!AQ.empty() and AQ.back().num < nums[i])
        {
            AQ.pop_back();
        }
        AQ.push_back({i, nums[i]});
        if (AQ.front().TIME <= i - totK)
        {
            AQ.pop_front();
        }
        if (i >= totK)
            write(AQ.front().num), putchar(' ');
    }
    putchar('\n');
}
void MINIMUM()
{
    for (int i = 1; i <= totN; ++i)
    {
        while (!IQ.empty() and IQ.back().num > nums[i])
        {
            IQ.pop_back();
        }
        IQ.push_back({i, nums[i]});
        if (IQ.front().TIME <= i - totK)
        {
            IQ.pop_front();
        }
        if (i >= totK)
            write(IQ.front().num), putchar(' ');
    }
    putchar('\n');
}

int main()
{
    totN = read();
    totK = read();
    for (int i = 1; i <= totN; ++i)
    {
        nums[i] = read();
    }
    MINIMUM();
    MAXAMUM();
    return 0;
} //Thomitics Code