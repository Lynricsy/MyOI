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

const int MOD = 998244353;
int totN;
int totK;
long long matix[509][509];
long long treat[100090];
long long ematix[509][509];
long long jmatix[509][509];

long long ksm(long long a, long long b)
{
    long long base = a%MOD;
    long long result = 1;
    while (b)
    {
        if (b& 1)
        {
            result*=base;
        }
        base*=base;
        b>>=1;
    }
    return result;
}

void eignmatix()
{
    for (int i = 1; i <= totN; i++)
    {
        ematix[i][i]=1;
        for (int j = i - 1; j >= 0; j--)
        {
            int s(0);
            int m=ksm(treat[i]-matix[j][j]+MOD,MOD-2);
            for (int k = 0; k < i; k++)
            {
                s=(s + matix[j][k]*matix[k][i])
            }
            
        }
        
        
    }
    
    
}

int main()
{
    totN = read();
    totK = read();
    for (int i = 1; i <= totN; ++i)
    {
        for (int j = 1; j <= totN; ++j)
        {
            matix[i][j] = read();
        }
        treat[i] = matix[i][i];
    }
}