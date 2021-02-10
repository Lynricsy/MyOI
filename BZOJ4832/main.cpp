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
template <class T> inline void read(T &x) {
	x = 0; int c = getchar(), f = 1;
	for (; !isdigit(c); c = getchar()) if (c == 45) f = -1;
	for (; isdigit(c); c = getchar()) (x *= 10) += f*(c-'0');
}
double f[50][10][10][10];
void init()
{
	for (int i = 0; i < 49; i++)
		for (int a = 0; a <= 7; a++)
			for (int b = 0; b <= 7 - a; b++)
				for (int c = 0; c <= 7 - a - b; c++)
				{
					double p = 1.0 / (a + b + c + 1.0);
					f[i + 1][a][b][c] += (f[i][a][b][c] + 1.0) * p;
					if (a) f[i + 1][a][b][c] += f[i][a - 1][b][c] * a * p;
					if (b && a + b + c < 7) 
						f[i + 1][a][b][c] += f[i][a + 1][b - 1][c + 1] * b * p;
					if (b && a + b + c >= 7) 
						f[i + 1][a][b][c] += f[i][a + 1][b - 1][c] * b * p;
					if (c && a + b + c < 7) 
						f[i + 1][a][b][c] += f[i][a][b + 1][c] * c * p;
					if (c && a + b + c >= 7) 
						f[i + 1][a][b][c] += f[i][a][b + 1][c - 1] * c * p;
				}
}
int main()
{
	int T;
	read(T), init();
	while (T--)
	{
		int n, a, b, c;
		read(n), read(a), read(b), read(c);
		printf("%.2lf\n", f[n][a][b][c]);
	}
	return 0;
}