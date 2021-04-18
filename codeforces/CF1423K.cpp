#include <bits/stdc++.h>

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

int totT;
long long nowX;
int n;
bool check[1000100] = {0};
int prime[1000090], cnt = 0;
int ANS[1000090];
void Shai()
{
    check[1] = 1;
    for (int i = 2; i <= 1000010; i++)
    {
        if (!check[i])
            prime[++cnt] = i;
        for (int j = 1; j <= cnt && i * prime[j] <= 1010; j++)
        {
            check[i * prime[j]] = 1;
            if (i % prime[j] == 0)
                break;
        }
    }
}
void sumans()
{
    for (int i = 1; i <= cnt; i++)
    {
        if (prime[i] <= 1000)
            ANS[prime[i] * prime[i]]--;
        ANS[prime[i]]++;
    }
    ANS[1] = 1;
    for (int i = 2; i <= 1000080; i++)
    {
        ANS[i] += ANS[i - 1];
    }
}
/*
void SUMans()
{
    int nowP = 0;
    for (int j = 1; j <= 1000090; j++)
    {
        if (prime[nowP] * prime[nowP] > j)
        {
            ANS1[j] = ANS1[j - 1];
        }
        else
        {
            ANS1[j] = ANS1[j - 1];
            ++nowP;
        }
    }
    nowP = 0;
    for (int j = 1; j <= 1000090; j++)
    {
        if (prime[nowP] > j)
        {
            ANS2[j] = ANS2[j - 1];
        }
        else
        {
            ANS2[j] = ANS2[j - 1] + 1;
            ++nowP;
        }
    }
}
*/

int main()
{
    totT = read();
    Shai();
    sumans();
    for (int i = 1; i <= totT; i++)
    {
        nowX = read();
        printf("%d\n", ANS[nowX]);
    }
    return 0;
}