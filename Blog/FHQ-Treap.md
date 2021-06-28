---
title: FHQ-Treap
date: 2021-06-28
tags:
 - 数据结构
categories: 数据结构
description: 关于一种非旋随机化平衡树——FHQ-Treap。
top_img: https://api.dujin.org/bing/1920.php
cover: https://tvax4.sinaimg.cn/large/0072Vf1pgy1foxkft70qtj31hc0u0tqy.jpg
---

## 前言
这篇博客我自认为写的非常清楚，不需要$\text任何基础$，只要会`C++`语言基础即可学懂。

任何一个地方我都没有默认已经学过了，完全从`0`开始的$\text FHQ-Treap$教学！

好耶！我们开始吧！ヽ(✿ﾟ▽ﾟ)ノ

哒哒哒哒哒！


## FHQ-Treap

FHQ-Treap是一种平衡树。名字里带有`Treap`，他的确与`Treap`有一些相同的性质。比如，他与`Treap`一样，通过随机权值来保证平衡。

可是，众所周知，`Treap`是一种通过旋转来维护平衡的平衡树。

范浩强(FHQ)说过这样一句话：

$\text{Think functional.}$

$\text{-----FHQ}$

这句话是什么意思呢？

如果不明白，可以看<a href="https://wenku.baidu.com/view/a5f6fefe0066f5335a8121fa.html">这篇文章</a>以获得一些启发。

既然要$\text{Think functional}$，自然就不能使用旋转操作了。

于是，通过拆开与合并来维护平衡的`FHQ-Treap`就诞生了。

## 主要操作

### 结构体

```c++
struct Node
{
    long long lch, rch; //左孩子，右孩子
    long long siz;//子树大小
    long long val;//这个点的权值
    long long rnd;//随机权值
}
```

### 生成随机权值

想不到吧，这个都会讲！就是这么细！

首先为了让权值随机，我们需要初始化种子。

```c++
srand(time(NULL));
```

但是这里要注意的是，初始化种子只需要初始化一次，生成的数就是随机的了，多次初始化反而会导致总是生成同一个数。

Linux下生成的随机数比较大，我们不需要那么大的，可以取个模。
```c++
rnd = rand() % 114514;
```


### 拆分
拆分操作，就是把一棵树拆成两棵，以在两棵树中间进行一些操作。

设定一个$K$，然后把比$K$小或者等于$K$的放在左侧，其余在右侧。

如图：

<img src="https://t10.baidu.com/it/u=2972804439,2749805413&fm=173&app=25&f=JPEG?w=381&h=229&s=6DA2147283964DC00A7905CF000050B2">

代码：
```c++
void split(long long nowX, long long K, long long &Xtree, long long &Ytree)
//nowX是目前正在分裂的节点，K就是K，Xtree和Ytree分别是分裂后的两棵树。
{
	if (!nowX)
	{
		Xtree = Ytree = 0; //第一次分裂，先初始化
	}
	else
	{
		if (nodes[nowX].val <= K)
		{
			Xtree = nowX; //将nowX归至X树
			split(nodes[nowX].rch, K, nodes[nowX].rch, Ytree); //向nowX右子树分裂
		}
		else
		{
			Ytree = nowX; //将nowX归至Y树
			split(nodes[nowX].lch, K, Xtree, nodes[nowX].lch); //向nowX左子树分裂
		}
		update(nowX);
	}
}
```

### 合并

合并，就是拆分完操作完后再将树合并回去。

<img src="https://t10.baidu.com/it/u=2886283773,1160930284&fm=173&app=25&f=JPEG?w=477&h=246&s=69A034728FD768C01CDD48CF0000A0A2">

```c++

long long merge(long long Xtree,long long Ytree)
{
	if(!Xtree||!Ytree)
	{
		return Xtree+Ytree; //边界条件，返回有值的那一个
	}
	else if(nodes[Xtree].rnd<=nodes[Ytree].rnd)
	{
		nodes[Xtree].rch=merge(nodes[Xtree].rch,Ytree);
		update(Xtree);
		retrun Xtree;
	}
	else
	{
		nodes[Ytree].lch=merge(Ytree,nodes[Xtree].lch);
		update(Ytree);
		retrun Ytree;
	}
}
```

### 删除

很显然，将要删除的数分裂出来之后不合并回去即可。

```c++
long long del(long long nowX)
{
	split(rot,nowX,X,Z); //先让nowX作为X树最大的，放在最后
	split(X,nowX-1,X,Y); //X树中的所有nowX分到Y树中
	Y=merge(nodes[nowX].lch,nodes[nowX].rch);//Y树中全都是nowX，删除Y树根上那个nowX，其他nowX作为Y树
	rot=merge(merge(X,Y),Z);//三部分恢复为一棵树

}
```

### 排名第K的数

常规做法。

```c++
long long Kth(long long nowX, long long K) //nowX为目前寻找的树根，K为要找的名次
{
	while (1)
	{
		if (K == nodes[nodes[nowX].lch].siz + 1)
		{
			return nowX; //好耶ヽ(✿ﾟ▽ﾟ)ノ！找到啦！（全~都可以炸完~）
		}
		else if (K > nodes[nodes[nowX].lch].siz + 1)
		{
			nowX = nodes[nowX].rch;				 //emm……这个数太小了，应该找他的右边！走喽！（飞，比跑快吧！）
			K -= nodes[nodes[nowX].lch].siz + 1; //前面已经有这么多数了，应该减去！
		}
		else
		{
			nowX = nodes[nowX].lch; //看来这个数有点大！那就去左面！（我可是蒙德城的飞行冠军！）
		}
	}
}
```

### 前驱

很显然，让要找的数成为Y树的第一个，然后X树最后一个即为前驱。

```cpp
long long pre(long long nowX)
{
	split(rot, nowX-1, X, Y);
	return Kth(X, nodes[X].siz);
}
```

### 后缀
同样思路，让要找的数成为X树的最后一个，然后Y树第一个即为前驱。

```cpp
long long nxt(long long nowX)
{
	split(rot, nowX, X, Y);
	return Kth(Y, 1);
}
```

### 注意！

我们的前驱，后缀操作，都把树拆开了，调用后需要把X树和Y树复原回去。

```c++
#define mrg() merge(X,Y)
```

还有，我们找点的操作，返回的都是节点编号，输出时需要翻译成节点权值。

## 完整代码
好了，这就讲完了！是不是很轻松！

你可别说不轻松哦（鍾城 曉）

```c++
#include <bits/stdc++.h>
#define INF 999999999
#define arand() rand() % 114514
#define mrg() rot = merge(X, Y)

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

struct Node
{
	long long lch, rch;
	long long val, siz;
	long long rnd;
} nodes[maxN];

long long X, Y, Z;
long long rot;
long long cnt;
long long totN;

void update(long long nowX)
{
	nodes[nowX].siz = nodes[nodes[nowX].lch].siz + nodes[nodes[nowX].rch].siz + 1;
}

long long merge(long long Atree, long long Btree)
{
	if ((!Atree) || (!Btree))
	{
		return Atree + Btree;
	}
	else if (nodes[Atree].rnd < nodes[Btree].rnd)
	{
		nodes[Atree].rch = merge(nodes[Atree].rch, Btree);
		update(Atree);
		return Atree;
	}
	else
	{
		nodes[Btree].lch = merge(Atree, nodes[Btree].lch);
		update(Btree);
		return Btree;
	}
}

void split(long long splitX, long long K, long long &Xtree, long long &Ytree)
{
	if (!splitX)
	{
		Xtree = Ytree = 0;
		return ;
	}
	else
	{
		if (nodes[splitX].val <= K)
		{
			Xtree = splitX;
			split(nodes[splitX].rch, K, nodes[splitX].rch, Ytree);
		}
		else
		{
			Ytree = splitX;
			split(nodes[splitX].lch, K, Xtree, nodes[splitX].lch);
		}
		update(splitX);
	}
}
long long Kth(long long KX, long long K)
{
	while (1)
	{
		if (K <= nodes[nodes[KX].lch].siz)
		{
			KX = nodes[KX].lch;
		}
		else if (K == nodes[nodes[KX].lch].siz + 1)
		{
			return KX;
		}
		else
		{
			K -= nodes[nodes[KX].lch].siz + 1;
			KX = nodes[KX].rch;
		}
	}
}

void del(long long delX)
{
	split(rot, delX, X, Z);
	split(X, delX - 1, X, Y);
	Y = merge(nodes[Y].lch, nodes[Y].rch);
	rot = merge(merge(X, Y), Z);
}

void insert(long long nowX)
{
	split(rot, nowX, X, Y);
	++cnt;
	nodes[cnt].lch = nodes[cnt].rch = 0;
	nodes[cnt].val = nowX;
	nodes[cnt].siz = 1;
	nodes[cnt].rnd = arand();
	rot = merge(merge(X, cnt), Y);
}

long long pre(long long nowX)
{
	split(rot, nowX - 1, X, Y);
	return Kth(X, nodes[X].siz);
}
long long nxt(long long nowX)
{
	split(rot, nowX, X, Y);
	return Kth(Y, 1);
}
long long thK(long long nowX)
{
	split(rot, nowX - 1, X, Y);
	return nodes[X].siz + 1;
}

int main()
{
	totN = read();
	int readX, readY;
	while (totN--)
	{
		readX = read();
		readY = read();
		if (readX == 1)
		{
			insert(readY);
		}
		else if (readX == 2)
		{
			del(readY);
		}
		else if (readX == 3)
		{
			write(thK(readY));
			putchar('\n');
			mrg();
		}
		else if (readX == 4)
		{
			write(nodes[Kth(rot, readY)].val);
			putchar('\n');
		}
		else if (readX == 5)
		{
			write(nodes[pre(readY)].val);
			putchar('\n');
			mrg();
		}
		else if (readX == 6)
		{
			write(nodes[nxt(readY)].val);
			putchar('\n');
			mrg();
		}
	}
	return 0;
}
```
## 练习
  - [普通平衡树](https://www.luogu.org/problemnew/show/P3369)
  - [文艺平衡树](https://www.luogu.org/problemnew/show/P3391)
  - [书架](https://www.luogu.org/problemnew/show/P2596)
  - [我永远喜欢珂朵莉~](https://www.luogu.com.cn/problem/P3987)

顺便热烈庆祝停课！

好耶！ヽ(✿ﾟ▽ﾟ)ノ

还有

祝贺微软推出新一代操作系统$\text{Windows 11}$。

从此，`x86`与`ARM`对峙正式形成！