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

const long long maxN=59;
const long long bigN=1000090;
long long totN;
long long totM;
long long totK;
long long H[maxN];
long long R[maxN];
long long Rs[maxN][maxN];
long long maxFLOW;
long long nowT = 0;
long long head[bigN];
long long cnt_edges=1;
long long DIS[bigN];
long long mainT;
long long mainS;
struct Edge
{
	long long nxt;
	long long to;
	long long flow;
}edges[bigN];
void add_edge(long long x,long long y,long long f)
{
	++cnt_edges;
	edges[cnt_edges].nxt=head[x];
	head[x]=cnt_edges;
	edges[cnt_edges].to=y;
	edges[cnt_edges].flow=f;

	++cnt_edges;
	edges[cnt_edges].nxt=head[y];
	head[y]=cnt_edges;
	edges[cnt_edges].to=x;
	edges[cnt_edges].flow=0;
}

bool BFS()
{
	queue<long long > Q;
	Q.push(0);
	DIS[0]=0;
	while (!Q.empty())
	{
		int nowX=Q.front();
		Q.pop();
		for (int i = head[nowX]; i ; i=edges[i].nxt)
		{
			int vir=edges[i].to;
			if (!DIS[vir])
			{
				Q.push(vir);
			}
			DIS[vir]=DIS[nowX]+1;
			if (vir==mainT)
			{
				return true;
			}
		}
	}
	return false;
}
long long DFS()
{

}

void changePOS()
{
	++nowT;
	for (int i = 1; i <= totN; ++i)
	{

	}
}

int main()
{
	totN=read();
	totM=read();
	totK=read();
	for (int i = 1; i <= totN; ++i)
	{
		H[i]=read();
		R[i]=read();
		for (int j = 1; j <= R[i]; ++j)
		{
			Rs[i][j]=read();
		}
	}
	while (maxFLOW<totK)
	{

	}
	return 0;
} //Thomitics Code