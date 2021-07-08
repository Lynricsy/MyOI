/**************************************************************
 * Problem: Luogu P3384
 * Author: 芊枫
 * Date: 2021 July 07
 * Algorithm: 轻重链剖分
**************************************************************/
#include <bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f
#define IINF 0x3f3f3f3f

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

const long long maxN = 1000090;
long long totN;
long long totM;
long long totR;
long long totP;
long long nums[maxN];
long long depth[maxN];
long long Sson[maxN];
long long siz[maxN];
long long fath[maxN];
long long ID[maxN];
long long num[maxN];
long long top[maxN];
long long cntNODE;

struct Edge
{
	long long nxt;
	long long to;
} edges[maxN];
long long cnt_edges;
long long head[maxN];
void add_edge(long long x, long long y)
{
	++cnt_edges;
	edges[cnt_edges].nxt = head[x];
	head[x] = cnt_edges;
	edges[cnt_edges].to = y;
}
struct Node
{
	long long l, r;
	Node *lch, *rch;
	long long val, tag;
	inline void pushup()
	{
		val = lch->val + rch->val;
	}
	Node(long long L, long long R)
	{
		l = L;
		r = R;
		tag = 0;
		if (l == r)
		{
			lch = rch = NULL;
			val = 1ll * num[l];
			return;
		}
		long long Mid = (L + R) >> 1;
		lch = new Node(L, Mid);
		rch = new Node(Mid + 1, R);
		pushup();
	}
	void maketag(long long w)
	{
		tag += 1ll * w;
		val += 1ll * (r - l + 1) * w;
	}
	void pushdown()
	{
		if (!tag)
		{
			return;
		}
		lch->maketag(1ll * tag);
		rch->maketag(1ll * tag);
		tag = 0;
	}
	inline bool INrange(long long L, long long R)
	{
		return (L <= l) && (r <= R);
	}
	inline bool OUTrange(long long L, long long R)
	{
		return (l > R) || (L > r);
	}
	void update(long long L, long long R, long long w)
	{
		if (INrange(L, R))
		{
			maketag(w);
		}
		else if (!OUTrange(L, R))
		{
			pushdown();
			lch->update(L, R, w);
			rch->update(L, R, w);
			pushup();
		}
	}
	long long query(long long L, long long R)
	{
		if (INrange(L, R))
		{
			return val;
		}
		else if (OUTrange(L, R))
		{
			return 0;
		}
		pushdown();
		return (1ll * lch->query(L, R) + 1ll * rch->query(L, R)) % totP;
	}
};

Node *rot;

void DFS1(long long x, long long fa, long long dept)
{
	depth[x] = dept;
	fath[x] = fa;
	siz[x] = 1;
	long long max = -1;
	for (int i = head[x]; i; i = edges[i].nxt)
	{
		long long vir = edges[i].to;
		if (vir == fa)
		{
			continue;
		}
		DFS1(vir, x, dept + 1);
		siz[x] += siz[vir];
		if (siz[vir] > max)
		{
			max = siz[vir];
			Sson[x] = vir;
		}
	}
}

void DFS2(long long x, long long nowTOP)
{
	++cntNODE;
	ID[x] = cntNODE;
	num[cntNODE] = nums[x];
	top[x] = nowTOP;
	if (!Sson[x])
	{
		return;
	}
	DFS2(Sson[x], nowTOP);
	for (int i = head[x]; i; i = edges[i].nxt)
	{
		long long vir = edges[i].to;
		if (vir == Sson[x] || vir == fath[x])
		{
			continue;
		}
		DFS2(vir, vir);
	}
}

long long qRANGE(long long x, long long y)
{
	long long nowANS = 1ll * 0;
	while (top[x] != top[y])
	{
		if (depth[top[x]] < depth[top[y]])
		{
			swap(x, y);
		}
		nowANS += 1ll * rot->query(ID[top[x]], ID[x]);
		nowANS %= totP;
		x = fath[top[x]];
	}
	if (depth[x] > depth[y])
	{
		swap(x, y);
	}
	nowANS += 1ll * rot->query(ID[x], ID[y]);
	return nowANS % totP;
}

long long qTREE(long long x)
{
	return rot->query(ID[x], ID[x] + siz[x] - 1) % totP;
}

void updRANGE(long long x, long long y, long long k)
{
	k %= totP;
	long long nowANS = 1ll * 0;
	while (top[x] != top[y])
	{
		if (depth[top[x]] < depth[top[y]])
		{
			swap(x, y);
		}
		rot->update(ID[top[x]], ID[x], k);
		x = fath[top[x]];
	}
	if (depth[x] > depth[y])
	{
		swap(x, y);
	}
	rot->update(ID[x], ID[y], k);
}

void updTREE(long long x, long long k)
{
	rot->update(ID[x], ID[x] + siz[x] - 1, k);
}

int main()
{
	totN = read();
	totM = read();
	totR = read();
	totP = read();
	for (int i = 1; i <= totN; ++i)
	{
		nums[i] = read() % totP;
	}
	for (int i = 1, x, y; i < totN; ++i)
	{
		x = read();
		y = read();
		add_edge(x, y);
		add_edge(y, x);
	}
	DFS1(totR, 0, 1);
	DFS2(totR, totR);
	rot = new Node(1, totN);
	for (int i = 1; i <= totM; ++i)
	{
		short tmp = read();
		long long x, y, z;
		if (tmp == 1)
		{
			x = read();
			y = read();
			z = read() % totP;
			updRANGE(x, y, z);
		}
		else if (tmp == 2)
		{
			x = read();
			y = read();
			write(qRANGE(x, y));
			putchar('\n');
		}
		else if (tmp == 3)
		{
			x = read();
			z = read() % totP;
			updTREE(x, z);
		}
		else
		{
			x = read();
			write(qTREE(x));
			putchar('\n');
		}
	}
	return 0;
} //Thomitics Code