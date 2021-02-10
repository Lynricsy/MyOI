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

const int MOD=1000000090;

int totN,totM,en,dist[100090],in[100090];

bool inque[100090];

struct Edge
{
	int e,d;
	Edge *next;
}edges[500090],*veges[100090];

void add_edge(int s,int e,int d)
{
	en++;
	edges[en].next = veges[s];
	veges[s] = edges + en;
	veges[s]->e = e;
	veges[s]->d = d;
}

void SPFA()
{
	memset(dist, 0x3f, sizeof(dist));
	dist[1] = 0;
	inque[1] = true;
	queue<int> q;
	q.push(1);
	while (q.size())
	{
		int now = q.front();
		q.pop();
		inque[now] = false;
		for (Edge *e = veges[now]; e; e = e->next)
		{
			int d = dist[now] + e->d;
			if (dist[e->e] > d)
			{
				dist[e->e] = d;
				if (!inque[e->e])
				{
					inque[e->e] = true;
					q.push(e->e);
				}
			}
		}
	}
}

int main()
{
	totN=read();
	totM=read();
	for (int a = 1; a <= totM; a++)
	{
		int s, e, d;
		scanf("%d%d%d", &s, &e, &d);
		add_edge(s, e, d);
	}
	SPFA();
	for (int a = 1; a <= totN; a++)
	{
		for (Edge *e = veges[a]; e; e = e->next)
		{
			if (dist[a] + e->d == dist[e->e])
			{
				in[e->e]++;
			}
		}
	}
	int ans = 1;
	for (int a = 2; a <= totN; a++)
	{
		ans = 1ll * ans * in[a] % MOD;
	}

	write(ans);
	putchar('\n');
	return 0;
}
