---
title: OI模板
date: 2021-06-29
tags:
 - 
categories: 大杂烩
description: 一些OI模板总结。
top_img: https://api.dujin.org/bing/1920.php
cover: https://tvax4.sinaimg.cn/large/0072Vf1pgy1foxkibab1zj31hc0u0dy7.jpg
---

<p><strong>Update:</strong></p>
```
2021.6.29    
新增 KMP 和 LCA
```

<details>
<summary>历史更新记录</summary>
<pre><code>
2021.6.28
新增 std::string
新增 Tarjan
2021.6.15
新增 Treap 和 左偏树<br>
2021.6.14
新增 Kruskal 最小生成树 <br>
2021.5.30
单源最短路径新增 vector 存图的 <br>
2021.5.16
动态规划新增 LCIS （最长公共上升子序列）<br>
2021.5.14
更新了区间dp的模板<br>
2021.4.29
新增了珂朵莉树
快速幂的代码锅了，现已修复
格式化了全部代码！！！<br>
2021.4.28
添加了单调队列，包含 “定长” 和 “不定长”。<br>
2021.4.23
求 gcd 的部分锅了，重新写了下。<br>
2021.4.20
新增线段树的区间加乘，区间修改。
重构了线段树的代码。
更新了部分标题名称。
```

</details>
<h2 id="考试必备">考试必备</h2>
<h3 id="快速读入">快速读入</h3>
```cpp
inline ll read()
{
    int x = 0, f = 0;
    char ch = getchar();
    while (!isdigit(ch))
        f |= (ch == '-'), ch = getchar();
    while (isdigit(ch))
        x = (x &lt;&lt; 1) + (x &lt;&lt; 3) + (ch ^ 48), ch = getchar();
    return f ? -x : x;
}
```

<h3 id="对拍"><a href="https://www.cnblogs.com/EdisonBa/p/13509379.html" target="_blank">对拍</a></h3>
<h3 id="卡常小技巧">卡常小技巧</h3>
<p><strong>① 位运算乘除</strong></p>
<p></p><div class="math display">\[x=x\times2^n ~可以转化成~ x&lt;&lt;n
\]</div><p></p><p></p><div class="math display">\[x=x÷2^n ~可以转化成~ x&gt;&gt;n
\]</div><p></p><p><strong>② for 卡常</strong></p>
```cpp
for (register int i(1); i &lt;= n; ++i)
```

<p><strong>③ 短函数前加</strong> <code>inline</code> <strong>卡常</strong></p>
<p><strong>④ 判断奇偶</strong></p>
```cpp
if(a % 2 == 0)  可以转化成  if((a &amp; 1) == 0)
```

<p><strong>⑤ 取模用</strong> <code>&amp;</code></p>
```cpp
x = 667 % 4;    可以转化成  x = 667 &amp; (4-1);
x = 667 % 32;   可以转化成  x = 667 &amp; (32-1);
```

<p><strong>⑥ 正负转换用位运算</strong></p>
```cpp
i = -1;       可以转换成  i = ~i + 1;   或   i = (i ^ -1) + 1; 
```

<p><strong>⑦ 取绝对值</strong></p>
```cpp
k = abs(x);   可以转换成  k = (x ^ (x &gt;&gt; 31))-(x &gt;&gt; 31);  
```

<h2 id="数据结构">数据结构</h2>
<h3 id="st表">ST表</h3>
<p>静态查询区间最值。</p>
```cpp
ll f[100001][20];
ll n, m, a[100001];

void ST_make()
{
    for (int i = 1; i &lt;= n; ++i)
        f[i][0] = a[i];
    ll t = log(n) / log(2) + 1;
    for (int j = 1; j &lt; t; ++j)
        for (int i = 1; i &lt;= n - (1 &lt;&lt; j) + 1; ++i)
            f[i][j] = max(f[i][j - 1], f[i + (1 &lt;&lt; (j - 1))][j - 1]);
}

ll ST_q(ll l, ll r)
{
    ll k = log(r - l + 1) / log(2);
    return max(f[l][k], f[r - (1 &lt;&lt; k) + 1][k]);
}

int main()
{
    n = read();
    m = read();
    for (int i = 1; i &lt;= n; ++i)
        a[i] = read();
    ST_make();
    for (int i = 1; i &lt;= m; ++i)
    {
        ll l = read(), r = read();
        printf("%lld\n", ST_q(l, r));
    }
    return 0;
}
```

<h3 id="单调队列">单调队列</h3>
<p><a href="https://www.luogu.com.cn/problem/P1886" target="_blank">例题1</a></p>
<p>有一个长为 <span class="math inline">\(n\)</span> 的序列 <span class="math inline">\(a\)</span>，以及一个大小为 <span class="math inline">\(k\)</span> 的窗口。现在这个从左边开始向右滑动，每次滑动一个单位，求出每次滑动后窗口中的最大值和最小值。</p>
```cpp
ll n, k, cnt = 0;
ll ans[2][1000005];

struct node
{
    ll sum, id;
};

deque&lt;node&gt; maxq;
deque&lt;node&gt; minq;

int main()
{
    n = read();
    k = read();
    node t;
    for (int i = 1; i &lt;= n; ++i)
    {
        ll x = read();
        t.id = i;
        t.sum = x;
        while (!minq.empty() &amp;&amp; x &lt;= minq.back().sum)
            minq.pop_back();
        while (!maxq.empty() &amp;&amp; x &gt;= maxq.back().sum)
            maxq.pop_back();
        minq.push_back(t);
        maxq.push_back(t);
        while (i - k &gt;= minq.front().id)
            minq.pop_front();
        while (i - k &gt;= maxq.front().id)
            maxq.pop_front();
        if (i &gt;= k)
        {
            ans[0][++cnt] = minq.front().sum;
            ans[1][cnt] = maxq.front().sum;
        }
    }
    for (int i = 1; i &lt;= n - k + 1; ++i)
        printf("%lld ", ans[0][i]);
    puts("");
    for (int i = 1; i &lt;= n - k + 1; ++i)
        printf("%lld ", ans[1][i]);
}
```

<p><a href="https://www.luogu.com.cn/problem/P1714" target="_blank">例题2</a></p>
<p>最大不定长子段和问题。</p>
<p>在一段长为 <span class="math inline">\(n\)</span> 的数列中，找出一个长度 <span class="math inline">\(≤m\)</span> 的子段，使得它的和是最大的。子段长度不能为0。</p>
```cpp
const ll maxn = 5000005;
#define INF 9223372036854775800

ll sum[maxn], q[maxn];
ll n, m;

int main()
{
    n = read();
    m = read();
    for (int i = 1; i &lt;= n; ++i)
    {
        ll x = read();
        sum[i] = sum[i - 1] + x;
    }

    ll h = 1, t = 1, ans = -INF;
    q[1] = 0;
    for (int i = 1; i &lt;= n; ++i)
    {
        while (h &lt;= t &amp;&amp; q[h] &lt; i - m)
            h++;
        ans = max(ans, sum[i] - sum[q[h]]);
        while (h &lt;= t &amp;&amp; sum[i] &lt;= sum[q[t]])
            t--;
        q[++t] = i;
    }
    printf("%lld\n", ans);
    Edison Ba;
}
```

<h3 id="树状数组">树状数组</h3>
<p>支持单点修改，区间查询。</p>
```cpp
ll lowbit(ll x)
{
    return x &amp; (-x);
}

ll c[500002], n, m;

void add(ll x, ll y) //单点修改
{
    for (; x &lt;= n; x += lowbit(x))
        c[x] += y;
}

ll sum(ll x) //前缀和
{
    ll ans = 0;
    for (; x; x -= lowbit(x))
        ans += c[x];
    return ans;
}

ll ask(ll l, ll r) //区间查询
{
    return sum(r) - sum(l - 1);
}

int main()
{
    n = read();
    m = read();
    for (int i = 1; i &lt;= n; ++i) //初始化
    {
        ll x = read();
        add(i, x);
    }
    for (int i = 1; i &lt;= m; ++i)
    {
        ll opt = read();
        if (opt == 1) //单点修改
        {
            ll x = read(), k = read();
            add(x, k);
        }
        else if (opt == 2) //区间查询
        {
            ll x, y;
            x = read();
            y = read();
            ll ans = ask(x, y);
            printf("%lld\n", ans);
        }
    }
    return 0;
}
```

<h3 id="线段树">线段树</h3>
<p>注：本线段树使用链表形式（指针），每个结点都是左闭右开区间。</p>
<h4 id="单点加">单点加</h4>
<p>作用等同于树状数组，但是线段树时间和空间的开销都非常大。</p>
```cpp
ll n, m;

struct node
{ //树结点
    ll L, R, sum, k;
    node *lc, *rc;
};

void build(node *now, ll l, ll r) //建树
{
    now-&gt;L = l;
    now-&gt;R = r;
    now-&gt;sum = 0;
    if (l + 1 &lt; r) //不是叶子，继续递归
    {
        now-&gt;lc = new node;
        now-&gt;rc = new node;
        ll mid = (l + r) / 2;
        build(now-&gt;lc, l, mid);
        build(now-&gt;rc, mid, r);
    }
    else
        now-&gt;lc = now-&gt;rc = NULL; //是叶子，停下
}

ll check(node *now, ll l, ll r) //查询区间和
{
    if (l &lt;= now-&gt;L &amp;&amp; now-&gt;R &lt;= r + 1) //勿忘 r+1
        return now-&gt;sum;
    else
    {
        ll ans = 0;
        ll mid = (now-&gt;L + now-&gt;R) / 2;
        if (l &lt; mid)
            ans += check(now-&gt;lc, l, r);
        if (r &gt;= mid)
            ans += check(now-&gt;rc, l, r); //右边需要取等
        return ans;
    }
}

void change(node *now, ll x, ll k) //单点修改
{
    if (now-&gt;L + 1 == now-&gt;R)
    {
        now-&gt;sum += k;
    }
    else
    {
        ll mid = (now-&gt;L + now-&gt;R) / 2;
        if (x &lt; mid)
            change(now-&gt;lc, x, k);
        if (x &gt;= mid)
            change(now-&gt;rc, x, k); //右边需要取等
        now-&gt;sum = now-&gt;lc-&gt;sum + now-&gt;rc-&gt;sum;
    }
}

int main()
{
    n = read();
    m = read();
    node *root;
    root = new node; //创建根结点
    build(root, 1, n + 1);

    for (int i = 1; i &lt;= n; ++i) //初始化
    {
        ll x = read();
        change(root, i, x);
    }

    for (int i = 1; i &lt;= m; ++i)
    {
        ll opt = read();
        if (opt == 1) //区间修改
        {
            ll x = read(), k = read();
            change(root, x, k);
        }
        else if (opt == 2) //区间查询
        {
            ll l = read(), r = read();
            ll res = check(root, l, r);
            printf("%lld\n", res);
        }
    }
    return 0;
}
```

<h4 id="区间加">区间加</h4>
<p>需要延迟修改。</p>
<p>对于结点，新加 <span class="math inline">\(k\)</span>，代表延迟修改量。</p>
<p>新增延迟信息下传函数 <code>update()</code></p>
<p>对于修改和查询函数新增延迟操作。</p>
```cpp
ll n, m;

struct node
{                    //树结点
    ll L, R, sum, k; //多出了延迟修改量 k
    node *lc, *rc;
};

void build(node *now, ll l, ll r) //建树

void update(node *now) //更新
{
    now-&gt;lc-&gt;sum += now-&gt;k * (now-&gt;lc-&gt;R - now-&gt;lc-&gt;L);
    now-&gt;rc-&gt;sum += now-&gt;k * (now-&gt;rc-&gt;R - now-&gt;rc-&gt;L);
    now-&gt;lc-&gt;k += now-&gt;k;
    now-&gt;rc-&gt;k += now-&gt;k;
    now-&gt;k = 0;
}

ll check(node *now, ll l, ll r) //查询区间和
{
    if (l &lt;= now-&gt;L &amp;&amp; now-&gt;R &lt;= r + 1) //勿忘 r+1
        return now-&gt;sum;
    else
    {
        update(now); //多了更新这一步
        ll ans = 0;
        ll mid = (now-&gt;L + now-&gt;R) / 2;
        if (l &lt; mid)
            ans += check(now-&gt;lc, l, r);
        if (r &gt;= mid)
            ans += check(now-&gt;rc, l, r); //右边需要取等
        return ans;
    }
}

void change(node *now, ll l, ll r, ll k) //区间修改
{
    if (l &lt;= now-&gt;L &amp;&amp; now-&gt;R &lt;= r + 1)
    {
        now-&gt;sum += k * (now-&gt;R - now-&gt;L);
        now-&gt;k += k;
    }
    else
    {
        update(now); //同样多了更新这一步
        ll mid = (now-&gt;L + now-&gt;R) / 2;
        if (l &lt; mid)
            change(now-&gt;lc, l, r, k);
        if (r &gt;= mid)
            change(now-&gt;rc, l, r, k);
        now-&gt;sum = now-&gt;lc-&gt;sum + now-&gt;rc-&gt;sum;
    }
}

int main()
{
    n = read();
    m = read();
    node *root;
    root = new node; //创建根结点
    build(root, 1, n + 1);

    for (int i = 1; i &lt;= n; ++i) //初始化
    {
        ll x = read();
        change(root, i, i, x); //区间修改单点
    }

    for (int i = 1; i &lt;= m; ++i)
    {
        ll opt = read();
        if (opt == 1) //区间修改（加）
        {
            ll l = read(), r = read(), k = read();
            change(root, l, r, k);
        }
        else if (opt == 2) //区间查询
        {
            ll l = read(), r = read();
            ll res = check(root, l, r);
            printf("%lld\n", res);
        }
    }
    return 0;
}
```

<h4 id="区间加乘">区间加乘</h4>
<p>操作为加或乘，最后答案模 <span class="math inline">\(mod\)</span>。</p>
<p>打两个标记，分别为 <code>add</code> 和 <code>mul</code> 。</p>
```cpp
ll n, m, mod;

struct node
{                           //树结点
    ll L, R, sum, mul, add; //多了 mul 和 add
    node *lc, *rc;
};

void build(node *now, ll l, ll r) //建树
{
    now-&gt;L = l;
    now-&gt;R = r;
    now-&gt;sum = 0;
    now-&gt;mul = 1;
    if (l + 1 &lt; r) //不是叶子，继续递归
    {
        now-&gt;lc = new node;
        now-&gt;rc = new node;
        ll mid = (l + r) / 2;
        build(now-&gt;lc, l, mid);
        build(now-&gt;rc, mid, r);
    }
    else
        now-&gt;lc = now-&gt;rc = NULL; //是叶子，停下
}

void update(node *now) //更新
{
    now-&gt;lc-&gt;sum = ((now-&gt;mul * now-&gt;lc-&gt;sum) % mod + (now-&gt;add * (now-&gt;lc-&gt;R - now-&gt;lc-&gt;L) % mod) % mod) % mod;
    now-&gt;rc-&gt;sum = ((now-&gt;mul * now-&gt;rc-&gt;sum) % mod + (now-&gt;add * (now-&gt;rc-&gt;R - now-&gt;rc-&gt;L) % mod) % mod) % mod;
    now-&gt;lc-&gt;mul = (now-&gt;mul * now-&gt;lc-&gt;mul) % mod;
    now-&gt;rc-&gt;mul = (now-&gt;mul * now-&gt;rc-&gt;mul) % mod;
    now-&gt;lc-&gt;add = ((now-&gt;mul * now-&gt;lc-&gt;add) % mod + now-&gt;add) % mod;
    now-&gt;rc-&gt;add = ((now-&gt;mul * now-&gt;rc-&gt;add) % mod + now-&gt;add) % mod;
    now-&gt;add = 0;
    now-&gt;mul = 1;
}

ll check(node *now, ll l, ll r) //查询区间和
{
    if (l &lt;= now-&gt;L &amp;&amp; now-&gt;R &lt;= r + 1) //勿忘 r+1
        return now-&gt;sum;
    else
    {
        update(now);
        ll ans = 0;
        ll mid = (now-&gt;L + now-&gt;R) / 2;
        if (l &lt; mid)
            ans = (ans + check(now-&gt;lc, l, r)) % mod;
        if (r &gt;= mid)
            ans = (ans + check(now-&gt;rc, l, r)) % mod; //右边需要取等
        return ans % mod;
    }
}

void add(node *now, ll l, ll r, ll k) //区间加
{
    if (l &lt;= now-&gt;L &amp;&amp; now-&gt;R &lt;= r + 1)
    {
        now-&gt;sum = now-&gt;sum + (k * (now-&gt;R - now-&gt;L)) % mod;
        now-&gt;add = (now-&gt;add + k) % mod;
    }
    else
    {
        update(now);
        ll mid = (now-&gt;L + now-&gt;R) / 2;
        if (l &lt; mid)
            add(now-&gt;lc, l, r, k);
        if (r &gt;= mid)
            add(now-&gt;rc, l, r, k);
        now-&gt;sum = (now-&gt;lc-&gt;sum + now-&gt;rc-&gt;sum) % mod;
    }
}

void mul(node *now, ll l, ll r, ll k) //区间乘
{
    if (l &lt;= now-&gt;L &amp;&amp; now-&gt;R &lt;= r + 1)
    {
        now-&gt;mul = (k * now-&gt;mul) % mod;
        now-&gt;add = (k * now-&gt;add) % mod;
        now-&gt;sum = (k * now-&gt;sum) % mod;
    }
    else
    {
        update(now);
        ll mid = (now-&gt;L + now-&gt;R) / 2;
        if (l &lt; mid)
            mul(now-&gt;lc, l, r, k);
        if (r &gt;= mid)
            mul(now-&gt;rc, l, r, k);
        now-&gt;sum = (now-&gt;lc-&gt;sum + now-&gt;rc-&gt;sum) % mod;
    }
}
```

<h3 id="平衡树">平衡树</h3>
<h4 id="treap">Treap</h4>
<p>您需要写一种数据结构，来维护一些数，其中需要提供以下操作：</p>
<ol>
<li>插入 <span class="math inline">\(x\)</span> 数</li>
<li>删除 <span class="math inline">\(x\)</span> 数(若有多个相同的数，因只删除一个)</li>
<li>查询 <span class="math inline">\(x\)</span> 数的排名(排名定义为比当前数小的数的个数 <span class="math inline">\(+1\)</span> )</li>
<li>查询排名为 <span class="math inline">\(x\)</span> 的数</li>
<li>求 <span class="math inline">\(x\)</span> 的前驱(前驱定义为小于 <span class="math inline">\(x\)</span>，且最大的数)</li>
<li>求 <span class="math inline">\(x\)</span>的后继(后继定义为大于 <span class="math inline">\(x\)</span>，且最小的数)</li>
</ol>
<p>第一行为 <span class="math inline">\(n\)</span>，表示操作的个数,下面 <span class="math inline">\(n\)</span> 行每行有两个数 <span class="math inline">\(\text{opt}\)</span> 和 <span class="math inline">\(x\)</span>，<span class="math inline">\(\text{opt}\)</span> 表示操作的序号<span class="math inline">\(( 1≤opt≤6  )\)</span></p>
<p>对于操作 <span class="math inline">\(3,4,5,6\)</span> 每行输出一个数，表示对应答案</p>
```cpp
const ll maxn = 1e5 + 10;
const ll inf = 1e14 + 10;
ll n, tot, root;

struct node
{
    ll l, r;
    ll v, rk;
    ll cnt, siz;
} s[maxn &lt;&lt; 1];

inline ll New(ll w)
{
    s[++tot].v = w;
    s[tot].rk = rand();
    s[tot].cnt = s[tot].siz = 1;
    return tot;
}

inline void upd(ll p)
{
    s[p].siz = s[s[p].l].siz + s[s[p].r].siz + s[p].cnt;
}

inline void build()
{
    New(-inf), New(inf);
    root = 1;
    s[1].r = 2;
    upd(root);
    return;
}

inline void zig(ll &amp;p)
{
    ll q = s[p].l;
    s[p].l = s[q].r, s[q].r = p;
    p = q;
    upd(s[p].r);
    upd(p);
}

inline void zag(ll &amp;p)
{
    ll q = s[p].r;
    s[p].r = s[q].l, s[q].l = p;
    p = q;
    upd(s[p].l);
    upd(p);
}

inline void add(ll &amp;p, ll x)
{
    if (p == 0)
    {
        p = New(x);
        return;
    }
    if (s[p].v == x)
    {
        s[p].cnt++;
        upd(p);
        return;
    }
    if (s[p].v &lt; x)
    {
        add(s[p].r, x);
        if (s[p].rk &lt; s[s[p].r].rk)
            zag(p);
    }
    if (s[p].v &gt; x)
    {
        add(s[p].l, x);
        if (s[p].rk &lt; s[s[p].l].rk)
            zig(p);
    }

    upd(p);
}

inline void delt(ll &amp;p, ll x)
{
    if (p == 0)
        return;
    if (s[p].v == x)
    {
        if (s[p].cnt &gt; 1)
        {
            s[p].cnt--;
            upd(p);
            return;
        }
        if (s[p].l || s[p].r)
        {
            if (s[p].r == 0 || s[s[p].l].rk &gt; s[s[p].r].rk)
            {
                zig(p);
                delt(s[p].r, x);
            }
            else
            {
                zag(p);
                delt(s[p].l, x);
            }
            upd(p);
        }
        else
            p = 0;
        return;
    }
    if (s[p].v &lt; x)
    {
        delt(s[p].r, x);
        upd(p);
        return;
    }
    if (s[p].v &gt; x)
    {
        delt(s[p].l, x);
        upd(p);
        return;
    }
}

inline ll getrank(ll p, ll x)
{
    if (p == 0)
        return 0;
    if (s[p].v == x)
    {
        return s[s[p].l].siz + 1;
    }
    if (s[p].v &gt; x)
    {
        return getrank(s[p].l, x);
    }
    else
    {
        return getrank(s[p].r, x) + s[s[p].l].siz + s[p].cnt;
    }
}

inline ll getval(ll p, ll x)
{
    if (p == 0)
        return inf;
    if (s[s[p].l].siz &gt;= x)
    {
        return getval(s[p].l, x);
    }
    if (s[s[p].l].siz + s[p].cnt &gt;= x)
    {
        return s[p].v;
    }
    else
    {
        return getval(s[p].r, x - s[s[p].l].siz - s[p].cnt);
    }
}

inline ll getpre(ll x)
{
    ll ans = 1;
    ll p = root;
    while (p)
    {
        if (x == s[p].v)
        {
            if (s[p].l)
            {
                p = s[p].l;
                while (s[p].r)
                    p = s[p].r;
                ans = p;
            }
            break;
        }
        if (s[p].v &lt; x &amp;&amp; s[p].v &gt; s[ans].v)
            ans = p;
        if (x &lt; s[p].v)
            p = s[p].l;
        else
            p = s[p].r;
    }
    return s[ans].v;
}

inline ll getnxt(ll x)
{
    ll ans = 2;
    ll p = root;
    while (p)
    {
        if (x == s[p].v)
        {
            if (s[p].r)
            {
                p = s[p].r;
                while (s[p].l)
                    p = s[p].l;
                ans = p;
            }
            break;
        }
        if (s[p].v &gt; x &amp;&amp; s[p].v &lt; s[ans].v)
            ans = p;
        if (x &lt; s[p].v)
            p = s[p].l;
        else
            p = s[p].r;
    }
    return s[ans].v;
}

int main()
{
    build();
    n = read();
    for (int i = 1; i &lt;= n; i++)
    {
        ll op = read(), x = read();
        if (op == 1)
            add(root, x);
        if (op == 2)
            delt(root, x);
        if (op == 3)
            printf("%lld\n", getrank(root, x) - 1);
        if (op == 4)
            printf("%lld\n", getval(root, x + 1));
        if (op == 5)
            printf("%lld\n", getpre(x));
        if (op == 6)
            printf("%lld\n", getnxt(x));
    }
    return 0;
}
```

<h3 id="左偏树">左偏树</h3>
<p>一开始有 <span class="math inline">\(n\)</span> 个小根堆，每个堆包含且仅包含一个数。接下来需要支持两种操作：</p>
<ol>
<li><code>1 x y</code>:将第 <span class="math inline">\(x\)</span> 个数和第 <span class="math inline">\(y\)</span> 个数所在的小根堆合并（若第 <span class="math inline">\(x\)</span> 或第 <span class="math inline">\(y\)</span> 个数已经被删除或第 <span class="math inline">\(x\)</span> 和第 <span class="math inline">\(y\)</span> 个数在用一个堆内，则无视此操作）。</li>
<li><code>2 x</code>：输出第 <span class="math inline">\(x\)</span> 个数所在的堆最小数，并将这个最小数删除（若有多个最小数，优先删除先输入的；若第 <span class="math inline">\(x\)</span> 个数已经被删除，则输出 <span class="math inline">\(-1\)</span> 并无视删除操作）。</li>
</ol>
<p>第一行包含两个正整数 <span class="math inline">\(n,m\)</span>，分别表示一开始小根堆的个数和接下来操作的个数。</p>
<p>第二行包含 <span class="math inline">\(n\)</span> 个正整数，其中第 <span class="math inline">\(i\)</span> 个正整数表示第 <span class="math inline">\(i\)</span> 个小根堆初始时包含且仅包含的数。</p>
<p>接下来 <span class="math inline">\(m\)</span> 行每行 <span class="math inline">\(2\)</span> 个或 <span class="math inline">\(3\)</span> 个正整数，表示一条操作。</p>
<p>输出包含若干行整数，分别依次对应每一个操作 <span class="math inline">\(2\)</span> 所得的结果。</p>
```cpp
#define M 150010
#define swap my_swap
#define ls S[x].Son[0]
#define rs S[x].Son[1]

struct Tree
{
    ll dis, val, Son[2], rt;
} S[M];
ll N, T, A, B, C, i;

inline ll Merge(ll x, ll y);
ll my_swap(ll &amp;x, ll &amp;y) { x ^= y ^= x ^= y; }
inline ll Get(ll x) { return S[x].rt == x ? x : S[x].rt = Get(S[x].rt); }
inline void Pop(ll x) { S[x].val = -1, S[ls].rt = ls, S[rs].rt = rs, S[x].rt = Merge(ls, rs); }
inline ll Merge(ll x, ll y)
{
    if (!x || !y)
        return x + y;
    if (S[x].val &gt; S[y].val || (S[x].val == S[y].val &amp;&amp; x &gt; y))
        swap(x, y);
    rs = Merge(rs, y);
    if (S[ls].dis &lt; S[rs].dis)
        swap(ls, rs);
    S[ls].rt = S[rs].rt = S[x].rt = x, S[x].dis = S[rs].dis + 1;
    return x;
}
int main()
{
    N = read(), T = read();
    S[0].dis = -1;
    for (i = 1; i &lt;= N; ++i)
        S[i].rt = i, S[i].val = read();
    for (i = 1; i &lt;= T; ++i)
    {
        A = read(), B = read();
        if (A == 1)
        {
            C = read();
            if (S[B].val == -1 || S[C].val == -1)
                continue;
            ll f1 = Get(B), f2 = Get(C);
            if (f1 != f2)
                S[f1].rt = S[f2].rt = Merge(f1, f2);
        }
        else
        {
            if (S[B].val == -1)
                puts("-1");
            else
                printf("%lld\n", S[Get(B)].val), Pop(Get(B));
        }
    }
    return 0;
}
```

<h3 id="珂朵莉树"><a href="https://oi-wiki.org/ds/odt/" target="_blank">珂朵莉树</a></h3>
<p>神奇的暴力数据结构</p>
<p><a href="https://www.luogu.com.cn/problem/CF896C" target="_blank">例题</a></p>
<p><span class="math inline">\(n\)</span> 个数，<span class="math inline">\(m\)</span> 次操作 <span class="math inline">\((n,m≤105)\)</span></p>
<p>操作：</p>
<ul>
<li>区间加</li>
<li>区间赋值</li>
<li>区间第k小</li>
<li>求区间幂次和</li>
</ul>
<p>数据随机，时限 <span class="math inline">\(2s\)</span>。</p>
<p>关键操作：推平一段区间，使一整段区间内的东西变得一样。保证数据随机</p>
```cpp
#include &lt;set&gt;
#include &lt;vector&gt;
#define p 1000000007
#define IT set&lt;node&gt;::iterator

/* 初始化 */
struct node
{
    ll l, r;
    mutable ll w; //可变的
    node(ll L, ll R = -1, ll W = 0)
    {
        l = L;
        r = R;
        w = W;
    }
    bool operator&lt;(const node &amp;o) const
    {
        return l &lt; o.l;
    }
};


ll n, m, seed, vmax, a[100005];
set&lt;node&gt; s;

ll rnd() /* 对于本题的数据生成器 */
{
    ll ans = seed;
    seed = (seed * 7 + 13) % p;
    return ans;
}

ll ksm(){}

IT split(ll pos) /* 分裂 */
{
    IT it = s.lower_bound(node(pos));
    if (it != s.end() &amp;&amp; it-&gt;l == pos)
        return it;
    --it;
    ll L = it-&gt;l, R = it-&gt;r;
    ll W = it-&gt;w;
    s.erase(it);
    s.insert(node(L, pos - 1, W));
    return s.insert(node(pos, R, W)).first;
}

void assign(ll l, ll r, ll w = 0) /* 推平 */
{
    IT itl = split(l), itr = split(r + 1);
    s.erase(itl, itr);
    s.insert(node(l, r, w));
}

void add(ll l, ll r, ll w = 1) /* 暴力区间加 */
{
    IT itl = split(l), itr = split(r + 1);
    for (; itl != itr; ++itl)
        itl-&gt;w += w;
}

ll rnk(ll l, ll r, ll k) /* 暴力区间第 k 小 */
{
    vector&lt;pair&lt;ll, int&gt;&gt; vp;
    IT itl = split(l), itr = split(r + 1);
    vp.clear();
    for (; itl != itr; ++itl)
        vp.push_back(pair&lt;ll, int&gt;(itl-&gt;w, itl-&gt;r - itl-&gt;l + 1));
    std::sort(vp.begin(), vp.end());
    for (vector&lt;pair&lt;ll, int&gt;&gt;::iterator it = vp.begin(); it != vp.end(); ++it)
    {
        k -= it-&gt;second;
        if (k &lt;= 0)
            return it-&gt;first;
    }
    return -1LL;
}

ll sum(ll l, ll r, ll ex, ll mod) /* 暴力求和 */
{
    IT itl = split(l), itr = split(r + 1);
    ll res = 0;
    for (; itl != itr; ++itl)
        res = (res + (ll)(itl-&gt;r - itl-&gt;l + 1) * ksm(itl-&gt;w, ex, mod)) % mod;
    return res;
}

int main()
{
    n = read();
    m = read();
    seed = read();
    vmax = read();
    for (int i = 1; i &lt;= n; ++i)
    {
        a[i] = (rnd() % vmax) + 1;
        s.insert(node(i, i, a[i]));
    }
    s.insert(node(n + 1, n + 1, 0));

    for (int i = 1; i &lt;= m; ++i)
    {
        ll op = 1LL * (rnd() % 4) + 1;
        ll l = 1LL * (rnd() % n) + 1;
        ll r = 1LL * (rnd() % n) + 1;
        if (l &gt; r)
            swap(l, r);
        ll x, y;
        if (op == 3)
            x = 1LL * (rnd() % (r - l + 1)) + 1;
        else
            x = 1LL * (rnd() % vmax) + 1;
        if (op == 4)
            y = 1LL * (rnd() % vmax) + 1;
        if (op == 1)
            add(l, r, x);
        else if (op == 2)
            assign(l, r, x);
        else if (op == 3)
            printf("%lld\n", rnk(l, r, x));
        else
            printf("%lld\n", sum(l, r, x, y));
    }
    return 0;
}
```

<h2 id="数学">数学</h2>
<h3 id="线性筛素数">线性筛素数</h3>
<p>给定一个整数 <span class="math inline">\(n\)</span> ，求出 $[2,n] $ 之间的所有素数。</p>
<p>思路：<code>prime</code> 数组存放已经筛出的素数， <span class="math inline">\(m\)</span> 代表素数个数（也就是说遍历时从 <span class="math inline">\(1\)</span> 遍历到 <span class="math inline">\(m\)</span> 即可），<code>v</code> 数组代表有没有被标记，避免重复筛。</p>
```cpp
int v[maxn], prime[maxn], n, k, t, m;
void primes(int n)
{
    memset(v, 0, sizeof(v)); //清空标记数组
    m = 0;                   //质数个数
    for (int i = 2; i &lt;= n; i++)
    {
        if (!v[i])                    //未被标记，i为质数
            v[i] = i, prime[++m] = i; //记录
        for (int j = 1; j &lt;= m; j++)
        {
            if (prime[j] &gt; v[i] || prime[j] &gt; n / i)
                break;                  //i有更小的质因子，或者超出n的范围
            v[i * prime[j]] = prime[j]; //prime[j]为合数 i*prime[j]的最小质因子
        }
    }
}
int main()
{
    scanf("%d", &amp;n);
    primes(n);
    for (int i = 1; i &lt;= m; ++i)
        printf("%d\n", prime[i]);
}
```

<h3 id="最大公约数">最大公约数</h3>
<p><strong>① 标准</strong></p>
```cpp
inline int gcd(int a, int b)
{
    int r;
    while (b &gt; 0)
    {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}
```

<p><strong>② 位运算</strong></p>
```cpp
inline int gcd(int a, int b) //a，b不能为0
{
    while (b ^= a ^= b ^= a %= b)
        ;
    return a;
}
```

<p><strong>③ 辗转相除法</strong></p>
```cpp
inline int gcd(int a, int b)
{
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}
```

<p><strong>④ 三目</strong></p>
```cpp
inline int gcd(int a, int b)
{
    return b &gt; 0 ? gcd(b, a % b) : a;
}
```

<p><strong>⑤ 外挂（考试禁止）</strong></p>
```cpp
#include &lt;algorithm&gt;
inline int gcd(int a, int b)
{
    return __gcd(a, b); //其实可以在主函数里直接用这个
}
```

<h2 id="分治">分治</h2>
<h3 id="快速乘法取余">快速乘法取余</h3>
<p>给定三个整数 <span class="math inline">\(a,n,mod\)</span> ，求 <span class="math inline">\(a \times n ~\%~mod\)</span> 的值。</p>
```cpp
inline int mult_mod(int a, int n, int mod)
{
    int ans = 0;
    while (n &gt; 0)
    {
        if (n &amp; 1)
            ans = (ans + a) % mod;
        a = (a + a) % mod;
        n &gt;&gt;= 1;
    }
    return ans;
}
```

<p>这个东西好像没有必要的样子，貌似只需要 <span class="math inline">\((a~\%~mod)×(n~\%~mod)~\%~mod\)</span> 即可。</p>
<h3 id="快速幂">快速幂</h3>
<p>给定三个整数 <span class="math inline">\(a,n,mod\)</span> ，求 <span class="math inline">\(a^n~\%~mod\)</span> 的值。</p>
```cpp
ll ksm(ll a, ll b, ll mod)
{
    if (mod == 1)
        return 0;
    ll ans = 1;
    ll tmp = a % mod;
    while (b)
    {
        if (b &amp; 1)
            ans = ans * tmp % mod;
        tmp = tmp * tmp % mod;
        b &gt;&gt;= 1;
    }
    return ans;
}
```

<h3 id="lis">LIS</h3>
<p>求一个序列的最长上升子序列个数。<br>
本程序采用边读边处理 + 二分法。</p>
```cpp
ll f[maxn], ans = 1; //注意答案个数初始化为1

int main()
{
    ll n = read();
    for (int i = 1; i &lt;= n; ++i)
    {
        int x = read();
        if (i == 1)
        {
            f[1] = x;
            continue;
        }
        int l = 1, r = ans, mid;
        while (l &lt;= r)
        {
            mid = (l + r) &gt;&gt; 1;
            if (x &lt;= f[mid])
                r = mid - 1;
            else
                l = mid + 1;
        }
        f[l] = x;
        if (l &gt; ans)
            ++ans;
    }
    printf("%lld\n", ans);
    return 0;
}

```

<h3 id="lower_bound">lower_bound</h3>
<p>使用前提：数列为有序数列。</p>
<h4 id="①数组内">①数组内</h4>
```cpp
//查找范围：[ begin , end ) ，左闭右开区间。
*lower_bound(begin, end, num);        //返回第一个 &gt;= num 的数的数值
lower_bound(begin, end, num) - begin; // 返回下标

实际操作：
int a[100] = {0, 1, 3, 5, 7, 9, 10};
//       下标：0  1  2  3  4  5  6
int main()
{
    int x = lower_bound(a + 1, a + 6 + 1, 6) - a; //输出下标
    int y = *lower_bound(a + 1, a + 6 + 1, 6);    //输出值
    printf("%d %d", x, y);
    return 0;
}

输出结果：4 7
```

<h4 id="②结构体内">②结构体内</h4>
<p>结构体内使用 lower_bound 需要重载，下面我们主要对结构体中的 <span class="math inline">\(a\)</span> 进行操作。</p>
```cpp
struct node //开结构体
{
    int a, id; //定义结构体内的两个变量
    node() {}
    node(int x, int y) : a(x), id(y) {}
    bool operator&lt;(const node t) const //重载
    {
        return a &lt; t.a;
    }
} t[1001];

bool cmp(node x, node y) //快排 cmp 比较函数
{
    if (x.a &lt; y.a)
        return 1; //结构体内按 a 由小到大排序。
    return 0;
}

int main()
{
    int n = read(); //数列中数的个数
    for (int i = 1; i &lt;= n; ++i)
    {
        t[i].a = read(); //读入数列
        t[i].id = i;
    }
    sort(t + 1, t + n + 1, cmp); //按小到大排序

    int x, xiabiao, ans;
    x = read();                                              //需要查找的数字
    xiabiao = lower_bound(t + 1, t + n + 1, node(x, 0)) - t; //这样求下标
    ans = (*lower_bound(t + 1, t + n + 1, node(x, 0))).a;    //这样求值
    printf("%d %d\n", xiabiao, ans);
    return 0;
}

输入：
5
20 40 30 10 50
35
输出：
4 40
```

<p>另：upper_bound 的使用与 lower_bound 的使用类似，只不过是严格大于（&gt;）。</p>
<h2 id="动态规划">动态规划</h2>
<h3 id="基础模型">基础模型</h3>
<h4 id="数字金字塔">数字金字塔</h4>
```cpp
f[i][j] = max((f[i][j] + f[i + 1][j]), (f[i][j] + f[i][j + 1]));
```

<h4 id="lcs">LCS</h4>
<p>操作对象：两个长度不一定相等的字符串。</p>
<p><a href="http://ybt.ssoier.cn:8088/problem_show.php?pid=1265" target="_blank">例题</a></p>
```cpp
string s, t;
int f[maxn][maxn];

int main()
{
    cin &gt;&gt; s &gt;&gt; t;
    int ls = s.length(), lt = t.length();
    for (int i = 1; i &lt;= ls; i++)
        for (int j = 1; j &lt;= lt; j++)
        {
            f[i][j] = max(f[i - 1][j], f[i][j - 1]);
            if (s[i - 1] == t[j - 1])
                f[i][j] = max(f[i][j], f[i - 1][j - 1] + 1);
        }
    cout &lt;&lt; f[ls][lt] &lt;&lt; endl;
    return 0;
}
```

<h4 id="lcis">LCIS</h4>
<p>操作对象：两个长度不一定相等的数列。</p>
<p><a href="https://www.luogu.com.cn/problem/CF10D" target="_blank">CF10D</a></p>
```cpp
const int maxn = 1005;
ll n, m, a[maxn], b[maxn], ans;
ll f[maxn][maxn], lcis[maxn][maxn];

int main()
{
    n = read();
    for (int i = 1; i &lt;= n; ++i)
        a[i] = read();
    m = read();
    for (int i = 1; i &lt;= m; ++i)
        b[i] = read();

    for (int i = 1; i &lt;= n; ++i)
    {
        for (int j = 1, k = 0; j &lt;= m; ++j)
        {
            if (a[i] == b[j])
            {
                f[i][j] = f[i - 1][k] + 1;
                for (int p = 1; p &lt;= f[i - 1][k]; ++p)
                    lcis[j][p] = lcis[k][p];
                lcis[j][f[i][j]] = a[i];
            }
            else
                f[i][j] = f[i - 1][j];
            if (b[j] &lt; a[i] &amp;&amp; f[i][j] &gt; f[i][k])
                k = j;
        }
    }

    for (int i = 1; i &lt;= m; ++i)
        if (f[n][i] &gt; f[n][ans])
            ans = i;

    printf("%lld\n", f[n][ans]);
    for (int p = 1; p &lt;= f[n][ans]; ++p)
        printf("%lld ", lcis[ans][p]);
    puts("");
    return 0;
}
```

<h3 id="基础背包">基础背包</h3>
<h4 id="01背包">01背包</h4>
<p>背包数量为 <span class="math inline">\(V\)</span>，有 <span class="math inline">\(n\)</span>件物品，重量为 <span class="math inline">\(w_i\)</span>，价值为 <span class="math inline">\(c_i\)</span>。求能获得最大价值。</p>
```cpp
ll V, n, w[10000], c[10000], f[10000];

int main()
{
    V = read();
    n = read();
    for (int i = 1; i &lt;= n; ++i)
    {
        w[i] = read();
        c[i] = read();
    }
    for (int i = 1; i &lt;= n; ++i)
        for (int v = V; v &gt;= w[i]; --v)
        {
            if (f[v - w[i]] + c[i] &gt; f[v])
                f[v] = f[v - w[i]] + c[i];
        }
    printf("%lld\n", f[V]);
    return 0;
}
```

<h4 id="01-方案数">01-方案数</h4>
<p>一种物品只能选一次，组合出固定价值的方案数问题。</p>
<p>例题：<a href="http://ybt.ssoier.cn:8088/problem_show.php?pid=1291" target="_blank">ybt1291：数字组合</a></p>
```cpp
ll a[21], f[1003], n, t;
int main()
{
    n = read();
    t = read();
    for (int i = 1; i &lt;= n; ++i)
    {
        a[i] = read();
    }
    f[0] = 1;
    for (int i = 1; i &lt;= n; ++i)
    {
        for (int j = t; j &gt;= a[i]; --j)
        {
            f[j] += f[j - a[i]];
        }
    }
    printf("%lld\n", f[t]);
    return 0;
}
```

<h4 id="完全背包">完全背包</h4>
<p>一种物品可以选无限次。<br>
只需要改一下第二层循环的循环顺序就行了。</p>
```cpp
for (int i = 1; i &lt;= n; ++i)
    for (int v = w[i]; v &lt;= V; ++v)
    {
        if (f[v - w[i]] + c[i] &gt; f[v])
            f[v] = f[v - w[i]] + c[i];
    }
```

<h4 id="完全-方案数">完全-方案数</h4>
<p>一种物品可以选无限次，组合出固定价值的方案数问题。<br>
例题：<a href="http://ybt.ssoier.cn:8088/problem_show.php?pid=1293" target="_blank">ybt1293：买书</a></p>
```cpp
ll a[5], f[10002], m;

int main()
{
    m = read();
    a[1] = 10, a[2] = 20, a[3] = 50, a[4] = 100;
    f[0] = 1;
    for (int i = 1; i &lt;= 4; ++i)
    {
        for (int j = a[i]; j &lt;= m; ++j)
        {
            f[j] += f[j - a[i]];
        }
    }
    printf("%lld\n", f[m]);
    return 0;
}
```

<h4 id="混合背包">混合背包</h4>
<p>一种物品可以选 <span class="math inline">\(p\)</span> 次。</p>
```cpp
ll w[31], c[31], p[31];
ll f[201], n, m;

int main()
{
    m = read();
    n = read();
    for (int i = 1; i &lt;= n; ++i)
    {
        w[i] = read();
        c[i] = read();
        p[i] = read();
    }
    for (int i = 1; i &lt;= n; ++i)
    {
        if (p[i] == 0) //完全
        {
            for (int j = w[i]; j &lt;= m; ++j)
                f[j] = max(f[j], f[j - w[i]] + c[i]);
        }
        else //01和多重
        {
            for (int j = 1; j &lt;= p[i]; ++j)
            {
                for (int k = m; k &gt;= w[i]; --k)
                {
                    f[k] = max(f[k], f[k - w[i]] + c[i]);
                }
            }
        }
    }
    printf("%lld\n", f[m]);
    return 0;
}
```

<h4 id="二维费用背包">二维费用背包</h4>
<p>再加一重循环，多开一维数组即可。</p>
<p>例题：<a href="http://ybt.ssoier.cn:8088/problem_show.php?pid=1271" target="_blank">ybt1271：【例9.15】潜水员</a></p>
```cpp
ll v, u, k;
ll a[1091], b[1021], c[1092];
ll f[101][101];

int main()
{
    memset(f, 127, sizeof f);
    f[0][0] = 0;
    v = read();
    u = read();
    k = read();
    for (int i = 1; i &lt;= k; ++i)
    {
        a[i] = read();
        b[i] = read();
        c[i] = read();
    }
    for (int i = 1; i &lt;= k; ++i)
    {
        for (int j = v; j &gt;= 0; --j)
        {
            for (int l = u; l &gt;= 0; --l)
            {
                ll t1 = j + a[i];
                ll t2 = l + b[i];
                t1 = min(t1, v);
                t2 = min(t2, u);
                f[t1][t2] = min(f[t1][t2], f[j][l] + c[i]);
            }
        }
    }
    printf("%lld\n", f[v][u]);
    return 0;
}
```

<h3 id="进阶dp">进阶dp</h3>
<h4 id="区间dp">区间dp</h4>
<p>以 <code>f[i][j]</code> 中的 <span class="math inline">\(i\)</span> 为起点，<span class="math inline">\(j\)</span> 为终点进行 dp。</p>
<p>核心代码：</p>
```cpp

for (int t = 2; t &lt;= n; ++t)
{
    for (int i = 1; i &lt;=  n - t + 1; ++i)
    {
        int j = i + t - 1;
        for (int k = i; k &lt; j; ++k)
        {
            f[i][j] = ();
        }
    }
}

print()

```

<h4 id="斜率优化dp">斜率优化dp</h4>
<p>未完成，待补充。</p>
<p>例题：<a href="https://www.luogu.com.cn/problem/P3195" target="_blank">[HNOI2008]玩具装箱</a></p>
```cpp
ll sum[M], f[M], Q[M];
ll n, L;

ll X(ll j)
{
    return sum[j];
}

ll Y(ll j)
{
    return f[j] + (sum[j] + L) * (sum[j] + L);
}

long double K(ll j, ll k)
{
    return 1.0 * ((Y(j) - Y(k)) / (X(j) - X(k)));
}

int main()
{
    n = read();
    L = read();
    for (int i = 1; i &lt;= n; ++i)
    {
        sum[i] = read();
        sum[i] += sum[i - 1];
        ++sum[i];
    }

    ll l = 1, r = 1, j;
    for (int i = 1; i &lt;= n; ++i)
    {
        while (l &lt; r &amp;&amp; K(Q[l + 1], Q[l]) &lt;= 2 * sum[i])
            ++l;
        j = Q[l];
        f[i] = f[j] + (sum[i] - sum[j] - (L + 1)) * (sum[i] - sum[j] - (L + 1));
        while (l &lt; r &amp;&amp; K(Q[r], Q[r - 1]) &gt;= K(i, Q[r - 1]))
            --r;
        Q[++r] = i;
    }
    printf("%lld\n", f[n]);
}
```

<h2 id="图论">图论</h2>
<h3 id="前置">前置</h3>
<h4 id="链式前向星存图">链式前向星存图</h4>
```cpp
ll head[maxn];

struct node
{
    ll nxt, to, w;
} t[maxn];

void add(const ll u, const ll v, const ll w)
{
    t[++tot].to = v;
    t[tot].w = w;
    t[tot].nxt = head[u];
    head[u] = tot;
}
```

<h4 id="vector-存图">vector 存图</h4>
```cpp
struct node{
    ll to, w;
};

vector&lt;node&gt; t[maxn];

void add(const int u, const int v, const int w)
{
    t[u].push_back((node){v, w});
}
```

<h3 id="dijkstra-最短路">Dijkstra 最短路</h3>
<p>求单源 <span class="math inline">\(s\)</span> 到任意一点的最短路径。最短路径保存在数组 <code>dis</code> 中。</p>
<h4 id="链式前向星">链式前向星</h4>
```cpp
#include &lt;queue&gt;
priority_queue&lt;pair&lt;ll, ll&gt;&gt; q;
void dijkstra(int s)
{
    memset(dis, 0x3f, sizeof(dis)); //初始边无限大
    memset(vis, 0, sizeof(vis));          //结点初始均为访问
    dis[s] = 0;                           //起点到自己距离为0
    q.push(make_pair(0, s));              //起点进队
    while (!q.empty())
    {
        x = q.top().second;
        q.pop();                          //初始结点入队
        if (vis[x])
            continue;                     //如果走过，直接跳过
        vis[x] = 1;                       //标记已访问
        for (ll i = head[x]; i != -1; i = t[i].nxt)
        {
            ll y = t[i].to, z = t[i].w;
            if (dis[y] &gt; dis[x] + z)
            {
                dis[y] = dis[x] + z;           //更新起点到y最短路
                q.push(make_pair(-dis[y], y)); //d[y]相反数入队，转小根堆
            }
        }
    }
}
int main()
{
    for (int i = 1; i &lt;= n; ++i)
        head[i] = -1;
    ...
}
//后面省略
```

<h4 id="vector">vector</h4>
```cpp
void dj(int s)
{
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof vis);
    dis[s] = 0;
    q.push(make_pair(0, s));
    while (!q.empty())
    {
        ll x = q.top().second;
        q.pop();
        if (vis[x])
            continue;
        vis[x] = 1;
        for (int i = 0; i &lt; t[x].size(); ++i)
        {
            ll y = t[x][i].to, z = t[x][i].w;
            if (dis[y] &gt; dis[x] + z)
            {
                dis[y] = dis[x] + z;
                q.push(make_pair(-dis[y], y));
            }
        }
    }
}
```

<h3 id="spfa">SPFA</h3>
<p>SPFA能处理负边权，可以判断负环。也可以求最长路。</p>
<h4 id="最短路">最短路</h4>
```cpp
#include &lt;queue&gt;
queue&lt;int&gt; q;
void SPFA(int s)
{
    fill(dis + 1, dis + 1 + n, 2147483647); //初始边无限大
    memset(vis, 0, sizeof vis);
    dis[s] = 0;
    q.push(s);
    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        vis[x] = 0;
        for (int i = head[x]; i != -1; i = t[i].nxt)
        {
            int y = t[i].to, z = t[i].w;
            if (dis[y] &gt; dis[x] + z)
            {
                dis[y] = dis[x] + z;
                if (vis[y] == 0)
                {
                    q.push(y);
                    vis[y] = 1;
                }
            }
        }
    }
}
```

<h4 id="最长路">最长路</h4>
<p>可依据最短路代码进行修改。</p>
<pre><code>1. `dis` 数组赋初值时，如果没有负边权就赋 $-1$ ，如果有负边权就赋无限小。
```

<ol start="2">
<li>把 <code>dis[y]&gt;dis[x]+z</code> 中的 <code>&gt;</code> 改成 <code>&lt;</code> 。</li>
</ol>
<h4 id="判断负环">判断负环</h4>
<p>可在最短路代码基础上进行修改。需新加入一个数组 <code>cnt</code> ，专门记录负环。</p>
<p>补充代码：</p>
```cpp
ll cnt[maxn]; //专门记录负环
void SPFA().....if (dis[y] &gt; dis[x] + z)
{
    dis[y] = dis[x] + z;
    cnt[y]++;
    if (cnt[y] &gt;= n + 1) //出现超过n次表示就有负环
    {
        ans = 1; //ans=1代表有负环。
        return;
    }
    if (vis[y] == 0)
    {
        q.push(y);
        vis[y] = 1;
    }
}
```

<h3 id="floyd-全源最短路">Floyd 全源最短路</h3>
```cpp
inline void floyd()
{
    for (k = 1; k &lt;= n; k++)
        for (i = 1; i &lt;= n; i++)
            for (j = 1; j &lt;= n; j++)
                if (e[i][j] &gt; e[i][k] + e[k][j])
                    e[i][j] = e[i][k] + e[k][j];
}
```

<h3 id="并查集">并查集</h3>
<p><span class="math inline">\(n\)</span> 代表元素个数，<span class="math inline">\(m\)</span> 为操作数。</p>
<p><span class="math inline">\(opt=1\)</span> 时，合并集合 <span class="math inline">\(a,b\)</span> ；<span class="math inline">\(opt=2\)</span> 时，如果 <span class="math inline">\(a,b\)</span> 在同一集合，输出 <code>Y</code> 否则输出 <code>N</code> 。</p>
```cpp
int find(int k)
{
    if (f[k] == k)
        return k;
    return f[k] = find(f[k]);
}

int main()
{
    n = read();
    m = read();
    for (int i = 1; i &lt;= n; ++i)
        f[i] = i; //初始化自己的老大是自己

    for (int i = 1; i &lt;= m; ++i)
    {
        int opt, a, b;
        opt = read();
        a = read();
        b = read();
        if (opt == 1)
            f[find(a)] = find(b);
        else
        {
            if (find(a) == find(b))
                printf("Y\n");
            else
                printf("N\n");
        }
    }
    return 0;
}
```

<h3 id="lca">LCA</h3>
<p><a href="https://www.luogu.com.cn/problem/P3379" target="_blank">P3379 【模板】最近公共祖先（LCA）</a></p>
<p>邻接表存图。</p>
```cpp
struct node{...};
void add(...){}

ll dep[500010], fa[500010][21], lg[500002];
ll head[500010], tot;
ll n, m, s;

void dfs(ll now, ll fath)
{
    fa[now][0] = fath;
    dep[now] = dep[fath] + 1;
    for (int i = 1; i &lt;= lg[dep[now]]; ++i)
        fa[now][i] = fa[fa[now][i - 1]][i - 1];
    for (int i = head[now]; i; i = t[i].nxt)
        if (t[i].to != fath)
            dfs(t[i].to, now);
}

ll LCA(ll x, ll y)
{
    if (dep[x] &lt; dep[y])
        swap(x, y);
    while (dep[x] &gt; dep[y])
        x = fa[x][lg[dep[x] - dep[y]] - 1];
    if (x == y)
        return x;
    for (int k = lg[dep[x]] - 1; k &gt;= 0; --k)
        if (fa[x][k] != fa[y][k])
            x = fa[x][k], y = fa[y][k];
    return fa[x][0];
}

int main()
{
    n = read();
    m = read();
    s = read();
    for (int i = 1; i &lt;= n; ++i)
        lg[i] = lg[i - 1] + (1 &lt;&lt; lg[i - 1] == i);
        
    for (int i = 1; i &lt; n; ++i)
    {
        ll x = read(), y = read();
        add(x, y);
        add(y, x);
    }
    
    dfs(s, 0);
    for (int i = 1; i &lt;= m; ++i)
    {
        ll x = read(), y = read();
        printf("%lld\n", LCA(x, y));
    }
    return 0;
}
```

<h3 id="最小生成树">最小生成树</h3>
<h4 id="kruskal">Kruskal</h4>
<p>前置：并查集</p>
```cpp
struct node
{
    ll u, v, w;
} t[200005];

ll fa[200005], n, m, ans, eu, ev, cnt;

inline bool cmp(node a, node b)
{
    return a.w &lt; b.w;
}

inline ll find(ll x)
{
    if (fa[x] == x)
        return x;
    return fa[x] = find(fa[x]);
}

inline void K()
{
    sort(t, t + m, cmp);
    for (int i = 1; i &lt;= m; ++i)
    {
        eu = find(t[i].u), ev = find(t[i].v);
        if (eu == ev)
            continue;
        ans += t[i].w;
        fa[ev] = eu;
        if (++cnt == n)
            break;
    }
}

int main()
{
    n = read();
    m = read();
    for (int i = 1; i &lt;= n; ++i)
        fa[i] = i;
    for (int i = 1; i &lt;= m; ++i)
        t[i].u = read(), t[i].v = read(), t[i].w = read();
    K();
    printf("%lld\n", ans);
    Edison Ba;
}
```

<h4 id="prim">Prim</h4>
```cpp
int ans, cnt, now = 1; //Prim
void prim()
{
    for (int i = 2; i &lt;= n; ++i)
        dis[i] = MAXN;

    for (int i = head[1]; i; i = t[i].nxt)
        dis[t[i].to] = min(dis[t[i].to], t[i].w);

    while (++cnt &lt; n)
    {
        int minn = MAXN;
        vis[now] = 1;
        for (int i = 1; i &lt;= n; ++i)
        {
            if (vis[i])
                continue;
            if (minn &gt; dis[i])
            {
                minn = dis[i];
                now = i;
            }
        }

        ans += minn;

        for (int i = head[now]; i; i = t[i].nxt)
        {
            int y = t[i].to, z = t[i].w;
            if (vis[y])
                continue;
            if (dis[y] &gt; z)
            {
                dis[y] = z;
            }
        }
    }
}
```

<h3 id="拓扑排序">拓扑排序</h3>
```cpp
ll ans[100] ，cnt; //拓扑序列及其元素个数
ll deg[100];       //所有点的入度

void topsort()
{
    queue&lt;ll&gt; q;
    for (int i = 1; i &lt;= n; ++i)
        if (deg[i] == 0) //寻找最开始入度就为0的点
            q.push(i);   //入队

    while (!q.empty())
    {
        ll x = q.front();
        q.pop();
        ans[++cnt] = x; //把队首的元素放进拓扑序列
        for (int i = head[x]; i; i = t[i].nxt)
        {
            ll y = t[i].to;    //寻找邻边
            if (--deg[y] == 0) //邻边的入度-1，并且判断减后的入度是否为0
                q.push(y);     //如果为0就入队
        }
    }
}

int main()
{
    n = read();
    m = read(); //点，边
    for (int i = 1; i &lt;= m; ++i)
    {
        ll x = read(), y = read();
        add(x, y);
        deg[v]++; //入度++
    }

    topsort(); //拓扑排序

    if (cnt &lt; n) //拓扑序列的元素个数小于点数，说明有环
        puts("有环");
    else
        puts("无环");

    for (int i = 1; i &lt;= cnt; ++i)
        printf("%lld ", ans[i]); //输出拓扑序列

    return 0;
}
```

<h3 id="tarjan">Tarjan</h3>
```cpp
std::vector&lt;int&gt; t[maxn]; //vector 存图
std::vector&lt;int&gt; SCC[maxn];
std::stack&lt;int&gt; stk;

int n, m, tot, cnt;
int vis[maxn], dfn[maxn], low[maxn], belong[maxn];

void Tarjan(const int x)
{
    dfn[x] = low[x] = ++tot;
    vis[x] = 1;
    stk.push(x);
    for (int i = 0; i &lt; t[x].size(); ++i)
    {
        int y = t[x][i];
        if (!dfn[y])
        {
            Tarjan(y);
            low[x] = std::min(low[x], low[y]);
        }
        else if (vis[y])
            low[x] = std::min(low[x], dfn[y]);
    }
    if (dfn[x] == low[x])
    {
        int Last;
        cnt++;
        do
        {
            Last = stk.top();
            vis[Last] = 0;
            belong[Last] = cnt;
            stk.pop();
        } while (stk.size() &amp;&amp; Last != x);
    }
    return;
}

signed main()
{
    Init();
    for (int i = 1; i &lt;= n; ++i)
        if (!dfn[i])
            Tarjan(i);
    for (int i = 1; i &lt;= n; ++i)
        for (int j = 0; j &lt; t[i].size(); ++j)
            if (belong[i] != belong[t[i][j]])
                SCC[belong[i]].push_back(belong[t[i][j]]);
    ......
    
}
```

<h2 id="字符串">字符串</h2>
<h3 id="快速读入-1">快速读入</h3>
<p>可以根据题目描述自行修改。</p>
```cpp
void Init()
{
    char ch;
    ch = getchar();
    while (ch &lt; 'A' || ch &gt; 'Z')
        ch = getchar();
    while (ch &gt;= 'A' &amp;&amp; ch &lt;= 'Z')
    {
        A[++lena] = ch;
        ch = getchar();
    }

    while (ch &lt; 'A' || ch &gt; 'Z')
        ch = getchar();
    while (ch &gt;= 'A' &amp;&amp; ch &lt;= 'Z')
    {
        B[++lenb] = ch;
        ch = getchar();
    }
}
```

<h3 id="kmp">KMP</h3>
<p><a href="https://www.luogu.com.cn/problem/P3375" target="_blank">模板题</a></p>
<p><span class="math inline">\(A\)</span> 为大串，<span class="math inline">\(B\)</span> 为小串。</p>
<p>求 <span class="math inline">\(next\)</span> 数组</p>
```cpp
void make_nxt()
{
    k = 1;
    for (int i = 2; i &lt;= lenb; ++i)
    {
        while ((B[k] != B[i] &amp;&amp; k &gt; 1) || k &gt; i)
            k = nxt[k - 1] + 1;
        if (B[k] == B[i])
            nxt[i] = k++;
    }
}
```

<p>匹配</p>
```cpp
void check()
{
    k = 1;
    for (int i = 1; i + lenb &lt;= lena + 1;)
    {
        while (A[i + k - 1] == B[k] &amp;&amp; k &lt;= lenb)
            ++k;
        if (k == lenb + 1)
            printf("%d\n", i);
        if (nxt[k - 1] == 0)
        {
            ++i;
            k = 1;
            continue;
        }
        --k;
        i += k - nxt[k];
        k = nxt[k] + 1;
    }
}
```

<h2 id="常用-stl-初步">常用 STL 初步</h2>
<h3 id="string">string</h3>
```cpp
#include&lt;cstring&gt;
string s1,s2;

s1 + s2;   //将两个字符串拼接
[cur];     //访问下标
s1.size(); //返回字符串长度
s1.append(s2);  //将 s2 添加到 s1 末尾
s1.replace(pos,n,s2);   // 删除从 pos 开始的 n 个字符，然后在 pos 处插入串 s
s1.erase(pos, n);   // 删除从 pos 开始的 n 个字符
s1.insert(pos, s2); //在 pos 位置插入字符串 s
s1.substr(start, len);  //从 start 截取一个长度为 len 的字符串
s1.find(char，start=0); //查找并返回从 start 开始的字符 ch 的位置
s1.rfind(ch);   //从末尾开始，查找并返回第一个找到的字符 ch 的位置
//找不到则返回 -1
```

<h3 id="queue">queue</h3>
<p>先进先出</p>
```cpp
#include&lt;queue&gt;
queue&lt;int&gt; q; //priority_queue&lt;int&gt; q（从大到小排序）;
q.empty();  //判断队列是否为空
q.size();   //返回队列长度
q.push(item);   //对于queue，在队尾压入一个新元素
                //对于priority_queue，在基于优先级的适当位置插入新元素
q.pop();    //弹出队首元素

//queue only:
q.front();  //返回队首元素的值，但不删除该元素
q.back();   //返回队尾元素的值，但不删除该元素
     
//priority_queue only:
q.top();    //返回具有最高优先级的元素值，但不删除该元素
```

<h3 id="stack">stack</h3>
<p>先进后出</p>
```cpp
#include&lt;set&gt;
stack&lt;int&gt; s;
stack&lt; int, vector&lt;int&gt; &gt; stk;  //覆盖基础容器类型，使用vector实现stk
s.empty();  //判断stack是否为空，为空返回true，否则返回false
s.size();   //返回stack中元素的个数
s.pop();    //删除栈顶元素，但不返回其值
s.top();    //返回栈顶元素的值，但不删除此元素
s.push(item);   //在栈顶压入新元素item
```

<h3 id="set">set</h3>
<p>自动从小到大排序，自动去重。</p>
```cpp
set&lt;int&gt; s;//multiset&lt;int&gt; s （不去重）
set&lt;int&gt;::const_iterator iter; //迭代器 

s.insert();   //插入
s.erase();    //若参数为元素值，则删除所有该元素值
              //若参数为迭代器，则删除该迭代器指向的值
s.empty();    //判断set是否为空，为空返回 true，否则返回 false
s.count();    //返回某个值元素的个数
s.clear();    //清除所有元素
s.find();     //查找某元素，找到则返回其迭代器，否则返回 s.end()
s.begin();    //返回指向第一个元素的迭代器
--s.end();    //返回指向最后一个元素的迭代器
*s.begin();   //返回指向第一个元素的值
*--s.end();   //返回指向最后一个元素的值
              //区间形式为 [ begin , end ) ，所以 end 要自减
s.size();     //返回集合中元素的个数
*s.lower_bound(k);    //返回第一个大于等于k的元素值
*s.upper_bound(k);    //返回第一个大于k的元素值 （后继）
              //如果没有符合条件的值，则输出 s.size()

/* 遍历 */
for(iter = s.begin() ; iter != s.end() ; ++iter)
{
    cout&lt;&lt;*iter&lt;&lt;" ";//使用迭代器遍历 
}
```

<h3 id="map">map</h3>
```cpp
#include&lt;map&gt;
map&lt;string,int&gt; m;//string 是 key，int 是 value。
m.size();   //输出元素个数
m.empty();  //如果 map 为空则返回 true
m.clear();  //删除所有元素
......

m["AKIOI"] = 10;
cout &lt;&lt; m["AKIOI"];
输出结果：10
```

<h4 id="unordered">unordered</h4>
```cpp
#include&lt;unordered_map&gt;
用法：与 map 差别不大。
优点：因为内部实现了哈希表，因此其查找速度非常的快
缺点：哈希表的建立比较耗费时间
适用处：对于查找问题，unordered_map会更加高效一些，因此遇到查找问题，常会考虑一下用 unordered_map
```