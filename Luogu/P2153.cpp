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
#ifdef THODEBUG
const long long maxN = 90;
#else
const long long maxN = 100090;
#endif
long long totN;
long long totM;
struct Edge
{
	long long val;
	long long nxt;
	long long to;
	long long flow;
} edges[maxN];
long long cnt_edges = 1;
long long head[maxN];
long long DIS[maxN];
bool vis[maxN];

long long incf[maxN];
long long pre[maxN];
long long maxFLOW;
long long minCOST;
long long totS;
long long totT;
void add_edge(long long x, long long y, long long w, long long flow)
{
	++cnt_edges;
	edges[cnt_edges].nxt = head[x];
	head[x] = cnt_edges;
	edges[cnt_edges].to = y;
	edges[cnt_edges].val = w;
	edges[cnt_edges].flow = flow;

	++cnt_edges;
	edges[cnt_edges].nxt = head[y];
	head[y] = cnt_edges;
	edges[cnt_edges].to = x;
	edges[cnt_edges].val = -w;
	edges[cnt_edges].flow = 0;
}

bool SPFA()
{
	memset(DIS, 0x3f, sizeof DIS);
	memset(vis, 0, sizeof vis);
	queue<long long> Q;
	Q.push(totS);
	DIS[totS] = 0;
	vis[totS] = true;
	incf[totS] = 0x3f3f3f3f3f3f3f3f;
	while (!Q.empty())
	{
		long long nowX = Q.front();
		Q.pop();
		// vis[nowX] = false;
		for (int i = head[nowX]; i; i = edges[i].nxt)
		{
			long long vir = edges[i].to;
			long long w = edges[i].val;
			long long f = edges[i].flow;
			if (!f)
			{
				continue;
			}
			if (DIS[vir] > DIS[nowX] + w)
			{
				DIS[vir] = DIS[nowX] + w;
				incf[vir] = min(incf[nowX], f);
				pre[vir] = i;
				if (!vis[vir])
				{
					// vis[vir] = true;
					Q.push(vir);
				}
			}
		}
	}
	return (DIS[totT] != 0x3f3f3f3f3f3f3f3f);
}

void MCMF()
{
	while (SPFA())
	{
		maxFLOW += incf[totT];
		minCOST += incf[totT] * DIS[totT];
		long long nowX = totT;
		while (nowX != totS)
		{
			long long E = pre[nowX];
			edges[E].flow -= incf[totT];
			edges[E ^ 1].flow += incf[totT];
			nowX = edges[E ^ 1].to;
		}
	}
}

int main()
{
	totN = read();
	totM = read();
	for (int i = 1, x, y, z; i <= totM; ++i)
	{
		x = read();
		y = read();
		z = read();
		add_edge(x + totN, y, z, 1);
	}
	for (int i = 2; i < totN; ++i)
	{
		add_edge(i, i + totN, 0, 1);
	}
	add_edge(1, 1 + totN, 0, 10000000);
	add_edge(totN, totN + totN, 0, 10000000);
	totS = 1 + totN, totT = totN;
	MCMF();
	write(maxFLOW);
	putchar('\n');
	write(minCOST);
	return 0;
} //Thomitics Code