/**************************************************************
 * Problem: Luogu P1903
 * Author: 芊枫
 * Date: 2021 July 06
 * Algorithm: 带修莫队
**************************************************************/
// #include <iostream>
// #include <cstdio>
// #include <cmath>
// #include <algorithm>
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

long long SIZE;
inline long long inB(long long nowX)
{
	return (long long)(nowX / SIZE);
}
const long long maxN = 10000090;
struct Quest
{
	long long l, r;
	long long time;
	long long ID;
} query[maxN];
bool operator<(const Quest &a, const Quest &b)
{
	if (inB(a.l) == inB(b.l))
	{
		if (inB(a.r) == inB(b.r))
		{
			return a.time < b.time;
		}
		else
		{
			return a.r < b.r;
		}
	}
	else
	{
		return a.l < b.l;
	}
}
struct Tain
{
	long long time;
	long long val;
	long long pos;
} tains[maxN];
long long cntT;
long long cntQ;
long long nums[maxN];
long long totN;
long long totM;
long long ANS[maxN];
long long nowANS;
long long cnt[maxN];

inline void add(long long nowX)
{
	if (!cnt[nowX])
	{
		++nowANS;
	}
	++cnt[nowX];
}
inline void del(long long nowX)
{
	--cnt[nowX];
	if (!cnt[nowX])
	{
		--nowANS;
	}
}
inline void upd(long long nowX, long long time)
{
	if (query[nowX].l <= tains[time].pos && tains[time].pos <= query[nowX].r)
	{
		del(nums[tains[time].pos]);
		add(tains[time].val);
	}
	swap(nums[tains[time].pos], tains[time].val);
}

int main()
{
	totN = read();
	totM = read();
	SIZE = ceil(pow(totN, 3 / 5.0));
	for (int i = 1; i <= totN; ++i)
	{
		nums[i] = read();
	}
	for (int i = 1; i <= totM; ++i)
	{
		char ch = getchar();
		if (ch == 'Q')
		{
			++cntQ;
			query[cntQ].l = read();
			query[cntQ].r = read();
			query[cntQ].ID = cntQ;
			query[cntQ].time = cntT;
		}
		else
		{
			++cntT;
			tains[cntT].pos = read();
			tains[cntT].val = read();
		}
	}
	sort(query + 1, query + cntQ + 1);
	for (long long i = 1, l = 1, r = 0, t = 0; i <= cntQ; ++i)
	{
		while (l > query[i].l)
		{
			add(nums[--l]);
		}
		while (r < query[i].r)
		{
			add(nums[++r]);
		}
		while (l < query[i].l)
		{
			del(nums[l++]);
		}
		while (r > query[i].r)
		{
			del(nums[r--]);
		}
		while (t < query[i].time)
		{
			upd(i, ++t);
		}
		while (t > query[i].time)
		{
			upd(i, t--);
		}
		ANS[query[i].ID] = nowANS;
	}
	for (int i = 1; i <= cntQ; ++i)
	{
		write(ANS[i]);
		putchar('\n');
	}
	return 0;
} //Thomitics Code