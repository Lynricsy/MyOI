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
inline void write(const long long &x)
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

const int MAXN=1000090;
char A[MAXN], B[MAXN];
long long KMP[MAXN];
long long LA, LB;

void prefix()
{
    int j = 0;
    for (int i = 2; i <= LB; ++i)
    {
        while (j && (B[i] != B[j + 1]))
        {
            j = KMP[j];
        }
        if (B[i] == B[j + 1])
        {
            ++j;
        }
        KMP[i] = j;
    }
}

void check()
{
    int j=0;
    for (int i = 1; i <= LA; ++i)
    {
        while (j&&(A[i] != B[j + 1]))
        {
            j=KMP[j];
        }
        if (B[j+1]==A[i])
        {
            ++j;
        }
        if (j==LB)
        {
            write(i-LB+1);
            putchar('\n');
            j=KMP[j];
        }
    }
}

int main()
{
    scanf("%s",A+1);
    scanf("%s",B+1);
    LA = strlen(A+1);
    LB = strlen(B+1);
    prefix();
    check();
    for (int i = 1; i <= LB; i++)
    {
        write(KMP[i]);
        putchar(' ');
    }
    return 0;
} //Thomitics Code