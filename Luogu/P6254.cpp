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
int tip[1000090];
int flag[1000090];
int cnfs[1000090];
int maxF;
vector<int> Vs[1000090];
int totMIN;
int SUMs[1000090];
int conquers[1000090];
int SUMc[1000090];
int ansW;

int main()
{
	totN = read();
	for (int i = 1; i <= totN; i++)
	{
		char ch = getchar();
		if (ch == 'e')
		{
			tip[i] = -1;
		}
		if (ch == 's')
		{
			tip[i] = 1;
		}
		int x = read();
		flag[i] = x;
		maxF = max(maxF, flag[i]);
		Vs[flag[i]].push_back(i);
	}
	for (int i = 1; i <= maxF; i++)
	{
		if (!Vs[i].size())
		{
			continue;
		}
		int nowTOT = 0;
		int minFLOW = INF;
		for (int j = 0; j < Vs[i].size(); j++)
		{
			nowTOT += tip[Vs[i][j]];
			SUMs[j] = nowTOT;
			minFLOW = min(minFLOW, nowTOT);
		}
		if (nowTOT)
		{
			continue;
		}
		for (int j = 0; j < Vs[i].size(); j++)
		{
			if (SUMs[j] != minFLOW)
			{
				continue;
			}
			if (j < Vs[i].size() - 1)
			{
				++conquers[Vs[i][j] + 1];
				--conquers[Vs[i][j + 1] + 1];
			}
			else
			{
				++conquers[Vs[i][j] + 1];
				--conquers[Vs[i][0] + 1];
				++conquers[1];
			}
		}
	}
	for (int i = 1; i <= totN; i++)
	{
		SUMc[i] = SUMs[i] + conquers[i];
	}
	for (int i = 2; i <= totN; i++)
	{
		if (i>ansW)
		{
			ansW=i;
		}
	}
	write(ansW);
	putchar(' ');
	write(SUMc[ansW]);
	putchar('\n');
	return 0;
} //Thomitics Code
