/**************************************************************
 * Problem: Luogu P3805
 * Author: 芊枫
 * Date: 2021 July 05
 * Algorithm: Manacher
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

const long long maxN = 1100090;
char chr[maxN];
long long nums[maxN];
long long totANS;
long long LEN;

void READstr()
{
    char ch;
    ch = getchar();
    chr[0] = '#';
    chr[1] = '|';
    LEN = 1;
    while (ch < 'a' || ch > 'z')
    {
        ch = getchar();
    }
    while (ch >= 'a' && ch <= 'z')
    {
        chr[++LEN] = ch;
        chr[++LEN] = '|';
        ch = getchar();
    }
}

int main()
{
    READstr();
    for (long long i = 1, r = 0, mid = 0; i <= LEN; ++i)
    {
        if (i <= r)
        {
            nums[i] = min(nums[(mid << 1) - i], r - i + 1);
        }
        while (chr[i - nums[i]] == chr[i + nums[i]])
        {
            ++nums[i];
        }
        if (nums[i] + i > r)
        {
            r = nums[i] + i - 1;
            mid = i;
        }
        if (nums[i] > totANS)
        {
            totANS = nums[i];
        }
    }
    write(totANS - 1);
    return 0;
} //Thomitics Code