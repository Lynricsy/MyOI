#include <bits/stdc++.h>

using namespace std;

inline long long read()
{
	long long x = 0;
	int f = 1;
	char ch = getchar();
	while (ch < '0' || ch>'9')
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
void write(const long long& x)
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
	double x=0,t=0;
	int s=0,f=1;
	char c=getchar();
	for (;!isdigit(c);c=getchar())
	{
		if (c=='-')
		{
			f=-1;
		}
		if (c=='.')
		{
			goto readt;
		}
	}
	for (;isdigit(c)&&c!='.';c=getchar())
	{
		x=x*10+c-'0';
	}
	readt:
	for (;c=='.';c=getchar());
	for (;isdigit(c);c=getchar())
	{
		t=t*10+c-'0';
		++s;
	}
	r=(x+t/pow(10,s))*f;
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
inline void write(double x,int k)
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
	if (x < 0) putchar('-'), x = -x;
	long long y = (long long) (x * n) % n;
	x = (long long) x;
	dwrite(x), putchar('.');
	int bit[10], p = 0, i;
	for (; p < k; y /= 10)
		bit[++p] = y % 10;
	for (i = p; i > 0; i--)
		putchar(bit[i] + 48);
}

int totN,totM;
int que[650000];
int a[650000];
int sum[650000];
int DP[650000];

int A(int j,int k)
{
	return (DP[j] + sum[j] * sum[j]) - (DP[k] + sum[k] * sum[k]);
}
int B(int j,int k)
{
	return 2*(sum[j]-sum[k]);
}
int Val(int i,int j)
{
	return DP[j] + (sum[i] - sum[j]) * (sum[i] - sum[j]) + totM;
}

int main()
{
	while(~scanf("%d%d", &totN, &totM))
	{
		sum[0]=0;
		memset(DP, 0, sizeof(DP));
		memset(que,0,sizeof(que));
		for(int i=1; i <= totN; i++)scanf("%d", &a[i]);
		for(int i=1; i <= totN; i++)sum[i]= sum[i - 1] + a[i];
		int head=0,tot=0;
		que[tot++]=0;
		for(int i=1; i <= totN; i++)
		{
			while(head+1<tot&&A(que[head+1],que[head])<=sum[i]*B(que[head+1],que[head]))head++;
			DP[i]=Val(i, que[head]);
			while(head+1<tot&&A(i,que[tot-1])*B(que[tot-1],que[tot-2])<=A(que[tot-1],que[tot-2])*B(i,que[tot-1]))tot--;
			que[tot++]=i;
		}
		write(DP[totN]);
	}
}