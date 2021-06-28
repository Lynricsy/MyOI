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

const long long maxN = 100090;
long long totN;
long long totM;
vector<long long> edges[100090];
long long firstcm[maxN];
bool flag[maxN];
int ans[maxN];
long long cntANS;
void DFS(long long nowX)
{
	++cntANS;
	ans[cntANS] = nowX;
	flag[nowX] = true;
	for (auto &&i : edges[nowX])
	{
		if (flag[i])
		{
			continue;
		}
		flag[i] = true;
		DFS(i);
	}
}
int main()
{
	totN = read();
	totM = read();
	for (int i = 1, x, y; i <= totM; i++)
	{
		x = read();
		y = read();
		edges[x].push_back(y);
		edges[y].push_back(x);
	}
	// for (int i = 1; i <= totN; i++)
	// {
	// 	sort(edges[i].begin(), edges[i].end());
	// }
	DFS(1);
	for (int i = 1; i <= totN; i++)
	{
		write(ans[i]);
		putchar(' ');
	}
	return 0;
} //Thomitics Code