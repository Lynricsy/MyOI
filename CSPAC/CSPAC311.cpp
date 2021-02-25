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
inline double dread()
{
    double r;
    double x = 0, t = 0;
    int s = 0, f = 1;
    char c = getchar();
    for (; !isdigit(c); c = getchar())
    {
        if (c == '-')
        {
            f = -1;
        }
        if (c == '.')
        {
            goto readt;
        }
    }
    for (; isdigit(c) && c != '.'; c = getchar())
    {
        x = x * 10 + c - '0';
    }
readt:
    for (; c == '.'; c = getchar())
        ;
    for (; isdigit(c); c = getchar())
    {
        t = t * 10 + c - '0';
        ++s;
    }
    r = (x + t / pow(10, s)) * f;
    return r;
}

inline void dwrite(long long x)
{
    if (x == 0)
    {
        putchar(48);
        return;
    }
    int bit[20], p = 0, i;
    for (; x; x /= 10)
        bit[++p] = x % 10;
    for (i = p; i > 0; --i)
        putchar(bit[i] + 48);
}
inline void write(double x, int k)
{
    static int n = pow(10, k);
    if (x == 0)
    {
        putchar('0');
        putchar('.');
        for (int i = 1; i <= k; ++i)
            putchar('0');
        return;
    }
    if (x < 0)
        putchar('-'), x = -x;
    long long y = (long long)(x * n) % n;
    x = (long long)x;
    dwrite(x), putchar('.');
    int bit[10], p = 0, i;
    for (; p < k; y /= 10)
        bit[++p] = y % 10;
    for (i = p; i > 0; i--)
        putchar(bit[i] + 48);
}

long long MOD;

long long ultra_quick_pow(long long a,long long b)
{
	long long base=a;
	long long result=1;
	while(b)
	{
		if(b&1)
		{
			result*=base;
			result%=MOD;
		}
		b>>=1;
		base*=base;
		base%=MOD;
	}
	return result;
}

long long A;
long long B;

bool check[100000001]={0};
int prime[1000001];
int cnt=0;

void getprime(long long n)
{
	check[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(!check[i])
		{
			prime[cnt++]=i;
		}
		for(int j=0;j<cnt&&i*prime[j]<100000001;j++)
		{
			check[i*prime[j]]=1;
			if(i%prime[j]==0)
			{
				break;
			}
		}
	}
}

long long phi(long long x){
	long long ans=1;
	for(long long i=2;i*i<=x;i++){
		if(x%i==0)ans*=(i-1),x/=i;
		while(x%i==0)x/=i,ans*=i;
	}
	return ans*max(x-1,1LL);
}

long long getphi(long long num)
{
	long long result;
	int aa=0;
	while(prime[aa]<=num)
	{
		if(!(num%prime[aa]))
		{
			num=num/prime[aa]*(prime[aa]-1);
		}
		aa++;
	}
	return num;
}

int main()
{
	A=read();
	MOD=read();
	write(MOD*phi(MOD)+A);
    return 0;
} //ROSMONTIS Code

