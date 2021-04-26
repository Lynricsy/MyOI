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

long long sum[100090];
long long totL;
long long DP[100090];
long long totN;
//deque<int> Q;
int Q[100090];
int head=1;
int tail=1;
double a(int nowI)
{
	return (double)sum[nowI]+nowI;
}
double b(int nowI)
{
	return sum[nowI] + nowI + totL + 1;
}
double X(int nowI)
{
	return b(nowI);
}
double Y(int nowI)
{
	return DP[nowI] + b(nowI) * b(nowI);
}
double flare(int nowI,int nowJ)
{
	return (Y(nowI) - Y(nowJ)) / (X(nowI) - X(nowJ));
}

int main()
{
	totN = read();
	totL = read();
	for (int i = 1; i <= totN; ++i)
	{
		sum[i] = read();
		sum[i] += sum[i - 1];
	}
	for (int i = 1; i <= totN; ++i)
	{
		while ((head < tail) && flare(Q[head], Q[head + 1]) < 2 * a(i))
		{
			++head;
		}
		DP[i] = DP[Q[head]] + (a(i) - b(Q[head])) * (a(i) - b(Q[head]));
		while ((head < tail) && flare(i, Q[tail - 1]) < flare(Q[tail - 1], Q[tail]))
		{
			--tail;
		}
		Q[++tail] = i;
	}
	write(DP[totN]);
	return 0;
} //Thomitics Code