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

long long totN;
long long x[1000090];
long long p[1000090];
long long c[1000090];
long long a[1000090];
long long b[1000090];
long long DP[1000090];
long long Q[1000090];
long long head=1;
long long tail=1;
double flare(int nowI,int nowJ)
{
	return 1.0*(((double) DP[nowI] + b[nowI]) - ((double) DP[nowJ] + b[nowJ])) / ((double) a[nowI] - a[nowJ]);
}

int main()
{
	totN = read();
	for (int i = 1; i <= totN; ++i)
	{
		x[i] = read();
		p[i] = read();
		c[i] = read();
		a[i] = a[i - 1] + p[i];
		b[i] = b[i - 1] + p[i] * x[i];
	}
	for (int i = 1; i <= totN; ++i)
	{
		while (head < tail && flare(Q[head + 1], Q[head]) < x[i])
		{
			++head;
		}
		DP[i] = DP[Q[head]] + 1ll*x[i] * (a[i] - a[Q[head]]) - (b[i] - b[Q[head]]) + c[i];
		while (head < tail && flare(Q[tail], Q[tail - 1]) > flare(i, Q[tail]))
		{
			--tail;
		}
		Q[++tail] = i;
	}
	write(DP[totN]);
	return 0;
} //Thomitics Code