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

const long long maxN = 100090;
long long totN;
long long totM;
long long totT;
long long totS;
long long head[maxN];
long long cnt_edges = 1;
long long DIS[maxN];
bool vis[maxN];
long long incf[maxN];
long long pre[maxN];
long long maxFLOW;
long long minCOST;

struct Edge
{
	long long nxt;
	long long to;
	long long flow;
	long long val;
}edges[maxN*3];

inline void add_edge(long long x,long long y,long long f,long long w)
{
	++cnt_edges;
	edges[cnt_edges].nxt = head[x];
	head[x] = cnt_edges;
	edges[cnt_edges].to = y;
	edges[cnt_edges].val = w;
	edges[cnt_edges].flow = f;

	++cnt_edges;
	edges[cnt_edges].nxt = head[y];
	head[y] = cnt_edges;
	edges[cnt_edges].to = x;
	edges[cnt_edges].val = -w;
	edges[cnt_edges].flow = 0;
}

inline bool SPFA()
{
	memset(vis, 0, sizeof vis);
	memset(DIS, 0x3f, sizeof DIS);
	queue<long long> Q;
	vis[totS] = true;
	DIS[totS]=0;
	Q.push(totS);
	while (!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		for (int i = head[x]; i; i = edges[i].nxt)
		{
			if (!edges[i].flow)
			{
				continue;
			}
			long long ver=edges[i].to;
			if (DIS[ver]>edges[i].val+DIS[x])
			{
				pre[ver]=i;
				incf[ver]=min(incf[x],edges[i].flow);
				if (!vis[ver])
				{
					Q.push(ver);
				}
			}
		}
	}
	if (DIS[totT]==0x3f3f3f3f3f3f3f3f)
	{
		return false;
	}
	return true;
}

void MCMF()
{
	while (SPFA())
	{
		long long ti=totT;
		maxFLOW+=incf[totT];
		minCOST+=incf[totT]*DIS[totT];
		while (ti!=totS)
		{
			int nowEDGE=pre[ti];
			edges[nowEDGE].flow-=totT;
			edges[nowEDGE^1].flow+=totT;
			ti=edges[nowEDGE^1].to;
		}
	}
}

int main()
{
	totN = read();
	totM = read();
	totS = read();
	totT = read();
	for (int i = 1, x, y, w, f; i <= totM; ++i)
	{
		x = read();
		y = read();
		f = read();
		w = read();
		add_edge(x, y, f, w);
	}
	MCMF();
	write(maxFLOW);
	putchar('\n');
	write(minCOST);
	return 0;
} //Thomitics Code