/**************************************************************
 * Problem: Luogu P1368
 * Author: 芊枫
 * Date: 2021 July 05
 * Algorithm: 最小表示法
**************************************************************/
#pragma once
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
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

const long long maxN = 100090;
long long nums[maxN];
long long totN;

int main()
{
    totN = read();
    for (int i = 1; i <= totN; ++i)
    {
        nums[i] = read();
    }
    long long i;
    long long j;
    long long k;
    while (i < totN && j < totN && k < totN)
    {
    }

    return 0;
} //Thomitics Code