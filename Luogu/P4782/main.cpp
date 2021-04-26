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
long long totM;
struct Edge
{
	int nxt;
	int to;
}edges[4000090];
int head[4000090];
int cnt_edges;
int dfn[4000090];
int low[4000090];
int cntSCC=1;
int DFScnt;
int inSCC[4000090];
stack<int> Stacking;
bool inQ[4000090];
void add_edges(int x,int y)
{
	++cnt_edges;
	edges[cnt_edges].nxt=head[x];
	head[x]=cnt_edges;
	edges[cnt_edges].to=y;
}

void Tarjan(int nowX)
{
	++DFScnt;
	dfn[nowX] = low[nowX] = DFScnt;
	inQ[nowX] = true;
	Stacking.push(nowX);
	for (int i = head[nowX]; i; i = edges[i].nxt)
	{
		if (!dfn[edges[i].to])
		{
			Tarjan(edges[i].to);
			low[nowX] = min(low[edges[i].to], low[nowX]);
		} else if (inQ[edges[i].to])
		{
			low[nowX] = min(dfn[edges[i].to], low[nowX]);
		}
	}
	if (dfn[nowX] == low[nowX])
	{
		++cntSCC;
		int y;
		do
		{
			if(!Stacking.empty())
			{
				y=Stacking.top();
				inQ[y] = false;
				inSCC[y] = cntSCC;
				Stacking.pop();
			}
		} while (!Stacking.empty() && y != nowX );
//		inSCC[Stacking.top()] = cntSCC;
//		inQ[Stacking.top()] = false;
//		if (!Stacking.empty())
//		{
//			Stacking.pop();
//		}
	}
}

int main()
{
	totN = read();
	totM = read();
	for (int i = 1, x, y, s, t; i <= totM; ++i)
	{
		x = read();
		s = read();
		y = read();
		t = read();
		if ((!s) && (!t))
		{
			add_edges(x + totN, y);
			add_edges(y + totN, x);
		} else if (s && t)
		{
			add_edges(y, x + totN);
			add_edges(x, y + totN);
		} else if ((!s) && t)
		{
			add_edges(y, x);
			add_edges(x + totN, y + totN);
		} else if (s && (!t))
		{
			add_edges(y + totN, x + totN);
			add_edges(x, y);
		}
	}
	for (int i = 1; i <= totN * 2; ++i)
	{
		if ((!dfn[i]))
		{
			Tarjan(i);
		}
	}
	for (int i = 1; i <= totN; ++i)
	{
		if (inSCC[i] == inSCC[i + totN])
		{
			puts("IMPOSSIBLE");
			exit(0);
		}
	}
	puts("POSSIBLE\n");
	for (int i = 1; i <= totN; ++i)
	{
		if (inSCC[i] > inSCC[i + totN])
		{
			putchar('1');
			putchar(' ');
		} else
		{
			putchar('0');
			putchar(' ');
		}
	}
	return 0;
} //Thomitics Code