#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5000 + 10;

int n, m;
bool dis[MAXN][MAXN];
int in[MAXN], ans[MAXN], cnt;
bool b[MAXN];

inline int read()
{
	int f = 1, x = 0;
	char c = getchar();

	while (c < '0' || c > '9')
	{
		if (c == '-')
			f = -1;
		c = getchar();
	}

	while (c >= '0' && c <= '9')
	{
		x = x * 10 + c - '0';
		c = getchar();
	}

	return f * x;
}

void dfs(int now)
{
	ans[++cnt] = now;
	b[now] = true;
	for (int i = 1; i <= n; i++)
	{
		if (b[i])
			continue;
		if (!dis[now][i])
			continue;
		b[i] = true;
		dfs(i);
	}
}

int main()
{
	n = read(), m = read();
	for (int i = 1; i <= m; i++)
	{
		int x = read(), y = read();
		dis[x][y] = dis[y][x] = true;
	}
	dfs(1);
	for (int i = 1; i <= n; i++)
	{
		cout << ans[i] << " ";
	}
}