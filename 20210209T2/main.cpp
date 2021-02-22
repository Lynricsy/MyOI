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

long long totM,totN;
int fa[100090];
long long ssum[100090];
void init()
{
	for (int i = 1; i <= totN; ++i)
	{
		fa[i]=i;
	}
}
long long getfa(long long nowX)
{
	if (fa[nowX]==nowX)
	{
		return nowX;
	} else
	{
		return fa[nowX]=getfa(fa[nowX]);
	}
}
long long getbig()
{
	long long Max=-99999;
	for (int i = 1; i <= totN; ++i)
	{
		long long y=getfa(i);
		++ssum[y];
		Max=max(Max,y);
	}
	return Max;
}

int main()
{
	totN=read();
	totM=read();
	init();
	for (int i = 1; i <= totM; ++i)
	{
		int x,y;
		x=read();
		y=read();
		if ((getfa(x)!=y)&&(getfa(y)!=x))
		{
			fa[x]=y;
		}
	}
	long long bigheap=getbig();
	if (bigheap>totN/2)
	{
		write(((totN-bigheap)*bigheap-totM)>0?((totN-bigheap)*bigheap-totM):0);
	} else
	{
		if (totN%2)
		{
			write(((totN/2+1)*(totN/2)-totM)>0?((totN/2+1)*(totN/2)-totM):0);
		} else
		{
			write(((totN/2)*(totN/2)-totM)>0?((totN/2)*(totN/2)-totM):0);
		}
	}
	return 0;
}//LikiBlaze Code