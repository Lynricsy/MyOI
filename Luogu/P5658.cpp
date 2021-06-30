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

const long long maxN = 190;
long long totN;
char C[maxN];
long long sum[maxN];
long long nowDONATE[maxN];
stack<long long> S;
long long fath[maxN];

struct Edge
{
	long long nxt;
	long long to;
} edges[maxN];
long long head[maxN];
long long cnt_edges;
long long totANS;

void add_edge(long long x, long long y)
{
	++cnt_edges;
	edges[cnt_edges].nxt = head[x];
	edges[cnt_edges].to = y;
	head[x] = cnt_edges;
}

void DFS(long long nowX)
{
	long long POPed = 0;
	if (C[nowX] == ')')
	{
		if (!S.empty())
		{
			POPed = S.top();
			S.pop();
			nowDONATE[nowX] = nowDONATE[fath[POPed]] + 1;
		}
	}
	else if (C[nowX] == '(')
	{
		S.push(nowX);
	}
	sum[nowX] = sum[fath[nowX]] + nowDONATE[nowX];
	for (long long i = head[nowX]; i ; i=edges[i].nxt)
	{
		DFS(edges[i].to);
	}
	if (POPed)
	{
		S.push(POPed);
	}
	else if (!S.empty())
	{
		S.pop();
	}
}

int main()
{
	totN = read();
	scanf("%s", C + 1);
	for (int i = 2, x; i <= totN; ++i)
	{
		x = read();
		fath[i] = x;
		add_edge(x, i);
	}
	DFS(1);
	for (long long i = 1; i <= totN; ++i)
	{
		totANS ^= i*sum[i];
	}
	write(totANS);
	return 0;
} //Thomitics Code