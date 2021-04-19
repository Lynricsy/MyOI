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

long long totA;
long long totB;
long long DPset[10][11];

void DP()
{
    for (int i = 0; i <= 9; i++)
    {
        DPset[1][i] = 1;
    }
    for (int i = 2; i <= 9; i++)
    {
        for (int j = 0; j <= 9; ++j)
        {
            for (int k = 0; k <= 9; ++k)
            {
                if (abs(j - k) >= 2)
                {
                    DPset[i][j] += DPset[i - 1][k];
                }
            }
        }
    }
}
long long GetSum(int x)
{
    int totANS = 0;
    int length = 1;
    short partedNUM[19] = {0};
    while (x)
    {
        partedNUM[length++] = x % 10;
        x = x / 10;
    }
    length -= 1;
    for (int i = 1; i <= length - 1; ++i)
    {
        for (int j = 1; j <= 9; ++j)
        {
            totANS += DPset[i][j];
        }
    }
    /*
    int Fstn;
    if (x < 10)
    {
        Fstn = x;
    }
    else
    {
        Fstn = x / (10 * (length - 1));
    }
    */
    for (int i = 1; i < partedNUM[length]; ++i)
    {
        totANS += DPset[length][i];
    }
    for (int i = length - 1; i >= 1; --i)
    {
        for (int j = 0; j <= partedNUM[i] - 1; ++j)
        {
            if (abs(partedNUM[i + 1] - j) >= 2)
            {
                totANS += DPset[i][j];
            }
        }
        /*
        if (abs(partedNUM[i + 1] - partedNUM[i]) < 2)
        {
            break;
        }
        */
    }
    return totANS;
}

int main()
{
    totA = read();
    totB = read();
    DP();
    write(GetSum(totB + 1) - GetSum(totA));
    return 0;
} //Thomitics Code