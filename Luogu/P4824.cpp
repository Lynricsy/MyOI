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

const long long maxN = 1000090;
char Sa[maxN];
char Sb[maxN];
long long KMP[maxN];
long long LENa, LENb;
long long DP[maxN];
long long Stacking[maxN];
long long Stop;

void prefix()
{
    long long j = 0;
    for (int i = 2; i <= LENa; ++i)
    {
        while (j && Sa[i] != Sa[j + 1])
        {
            j = KMP[j];
        }
        if (Sa[i] == Sa[j + 1])
        {
            ++j;
        }
        KMP[i] = j;
    }
}

void suffix()
{
    long long j = 0;
    for (int i = 1; i <= LENb; ++i)
    {
        while (j && Sb[i] != Sa[j + 1])
        {
            j = KMP[j];
        }
        if (Sb[i] == Sa[j + 1])
        {
            ++j;
        }
        DP[i] = j;
        Stacking[++Stop] = i;
        if (j == LENa)
        {
            Stop -= LENa;
            j = DP[Stacking[Stop]];
        }
    }
}

int main()
{
    scanf("%s", Sb + 1);
    scanf("%s", Sa + 1);
    Sa[0]=34;
    Sb[0]=34;
    LENa = strlen(Sa)-1;
    LENb = strlen(Sb)-1;
    prefix();
    suffix();
    for (int i = 1; i <= Stop; ++i)
    {
        putchar(Sb[Stacking[i]]);
    }
    return 0;
} //Thomitics Code