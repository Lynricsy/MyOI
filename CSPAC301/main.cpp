#include <bits/stdc++.h>

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

struct BigInteger
{
    typedef unsigned long long LL;

    static const int BASE = 100000000;
    static const int WIDTH = 8;
    vector<int> s;

    BigInteger &clean()
    {
        while (!s.back() && s.size() > 1)
            s.pop_back();
        return *this;
    }
    BigInteger(LL num = 0) { *this = num; }
    BigInteger(string s) { *this = s; }
    BigInteger &operator=(long long num)
    {
        s.clear();
        do
        {
            s.push_back(num % BASE);
            num /= BASE;
        } while (num > 0);
        return *this;
    }
    BigInteger &operator=(const string &str)
    {
        s.clear();
        int x, len = (str.length() - 1) / WIDTH + 1;
        for (int i = 0; i < len; i++)
        {
            int end = str.length() - i * WIDTH;
            int start = max(0, end - WIDTH);
            sscanf(str.substr(start, end - start).c_str(), "%d", &x);
            s.push_back(x);
        }
        return (*this).clean();
    }

    BigInteger operator+(const BigInteger &b) const
    {
        BigInteger c;
        c.s.clear();
        for (int i = 0, g = 0;; i++)
        {
            if (g == 0 && i >= s.size() && i >= b.s.size())
                break;
            int x = g;
            if (i < s.size())
                x += s[i];
            if (i < b.s.size())
                x += b.s[i];
            c.s.push_back(x % BASE);
            g = x / BASE;
        }
        return c;
    }
    BigInteger operator-(const BigInteger &b) const
    {
        assert(b <= *this);
        BigInteger c;
        c.s.clear();
        for (int i = 0, g = 0;; i++)
        {
            if (g == 0 && i >= s.size() && i >= b.s.size())
                break;
            int x = s[i] + g;
            if (i < b.s.size())
                x -= b.s[i];
            if (x < 0)
            {
                g = -1;
                x += BASE;
            }
            else
                g = 0;
            c.s.push_back(x);
        }
        return c.clean();
    }
    BigInteger operator*(const BigInteger &b) const
    {
        int i, j;
        LL g;
        vector<LL> v(s.size() + b.s.size(), 0);
        BigInteger c;
        c.s.clear();
        for (i = 0; i < s.size(); i++)
            for (j = 0; j < b.s.size(); j++)
                v[i + j] += LL(s[i]) * b.s[j];
        for (i = 0, g = 0;; i++)
        {
            if (g == 0 && i >= v.size())
                break;
            LL x = v[i] + g;
            c.s.push_back(x % BASE);
            g = x / BASE;
        }
        return c.clean();
    }
    BigInteger operator/(const BigInteger &b) const
    {
        assert(b > 0);
        BigInteger c = *this;
        BigInteger m;
        for (int i = s.size() - 1; i >= 0; i--)
        {
            m = m * BASE + s[i];
            c.s[i] = bsearch(b, m);
            m -= b * c.s[i];
        }
        return c.clean();
    }
    BigInteger operator%(const BigInteger &b) const
    {
        BigInteger c = *this;
        BigInteger m;
        for (int i = s.size() - 1; i >= 0; i--)
        {
            m = m * BASE + s[i];
            c.s[i] = bsearch(b, m);
            m -= b * c.s[i];
        }
        return m;
    }
    int bsearch(const BigInteger &b, const BigInteger &m) const
    {
        int L = 0, R = BASE - 1, x;
        while (1)
        {
            x = (L + R) >> 1;
            if (b * x <= m)
            {
                if (b * (x + 1) > m)
                    return x;
                else
                    L = x;
            }
            else
                R = x;
        }
    }
    BigInteger &operator+=(const BigInteger &b)
    {
        *this = *this + b;
        return *this;
    }
    BigInteger &operator-=(const BigInteger &b)
    {
        *this = *this - b;
        return *this;
    }
    BigInteger &operator*=(const BigInteger &b)
    {
        *this = *this * b;
        return *this;
    }
    BigInteger &operator/=(const BigInteger &b)
    {
        *this = *this / b;
        return *this;
    }
    BigInteger &operator%=(const BigInteger &b)
    {
        *this = *this % b;
        return *this;
    }

    bool operator<(const BigInteger &b) const
    {
        if (s.size() != b.s.size())
            return s.size() < b.s.size();
        for (int i = s.size() - 1; i >= 0; i--)
            if (s[i] != b.s[i])
                return s[i] < b.s[i];
        return false;
    }
    bool operator>(const BigInteger &b) const { return b < *this; }
    bool operator<=(const BigInteger &b) const { return !(b < *this); }
    bool operator>=(const BigInteger &b) const { return !(*this < b); }
    bool operator!=(const BigInteger &b) const { return b < *this || *this < b; }
    bool operator==(const BigInteger &b) const { return !(b < *this) && !(b > *this); }
};

ostream &operator<<(ostream &out, const BigInteger &x)
{
    out << x.s.back();
    for (int i = x.s.size() - 2; i >= 0; i--)
    {
        char buf[20];
        sprintf(buf, "%08d", x.s[i]);
        for (int j = 0; j < strlen(buf); j++)
            out << buf[j];
    }
    return out;
}

istream &operator>>(istream &in, BigInteger &x)
{
    string s;
    if (!(in >> s))
        return in;
    x = s;
    return in;
}

string str;
string firststr;
BigInteger tempA,tempB;
BigInteger ANS(0);
BigInteger tempC;

const int  SIZE = 100; // 栈的初始容量
const int  ADDSIZE = 5; // 栈的单位增加容量
using namespace std;// 命名空间
const int INF = -0xfffffff;// 用于空栈时防止尴尬，返回一个不能读取的地址，让读取的人尴尬；
template <class T>
struct Strack
{
	T *top;// 栈顶的指针
	T *base;// 栈底的指针
	int strackSize;//栈容量
	void init()//栈的初始化
	{
		base = (T *)malloc(SIZE * sizeof(T));//分配内存
		top = base;
		strackSize = SIZE;
	}
 
	T Top()
	{// 返回栈顶元素
		if (top == base)
			return INF;// 返回尴尬地址
		return *(top - 1);
	}
 
	bool pop()
	{// 删除栈顶元素
		if (top == base)
			return false;
		top--;
		return true;
	}
 
	void push(T x)
	{//栈顶插入元素
		if (isPull()) {//如果内存不够重新分配内存
			base = (T *)realloc(base, (strackSize + ADDSIZE)*(sizeof(T)));
			top = base + strackSize;
			strackSize += ADDSIZE;
		}
		*top++ = x;
	}
 
	bool isEmpty()
	{//判断栈是否为空
		if (top == base)
			return true;
		return false;
	}
 
	bool isPull()//判满函数
	{
		if (top - base == strackSize)// 一次push一个所以当top - base = strackSize时满
			return true;
		else
			return false;
	}
};
 
int compareNumber(char x)//用来比较符号的优先级
{
	if (x == '+' || x == '-')
		return 0;
	if (x == '*' || x == '/')
		return 1;
	return -1;
}
 
void change(char *mid, char *suxfix)  
{
	int i = 0, len = strlen(mid), mid_index = 0;
	char c;
	Strack<char >intElements;
	intElements.init();
	intElements.push('#');
	while (i < len)
	{
		if (mid[i] == '(')
		{
			intElements.push(mid[i]);
			i++;
		}
		else if (mid[i] == ')')
		{
			while (intElements.Top() != '(')
			{
				suxfix[mid_index++] = intElements.Top();
				suxfix[mid_index++] = ' ';
				intElements.pop();
			}
			intElements.pop();
			i++;
		}
		else if (mid[i] == '+' || mid[i] == '-' || mid[i] == '/' || mid[i] == '*')
		{
			while (compareNumber(intElements.Top()) >= compareNumber(mid[i]))
			{
				suxfix[mid_index++] = intElements.Top();
				suxfix[mid_index++] = ' ';
				intElements.pop();
			}
			intElements.push(mid[i]);
			i++;
		}
		else if (mid[i] >= '0'&&mid[i] <= '9')
		{
			while (mid[i] >= '0'&&mid[i] <= '9')
			{
				suxfix[mid_index++] = mid[i];
				i++;
			}
			suxfix[mid_index++] = ' ';
		}
		else
		{
 
		}
	}
	while (intElements.Top() != '#') {
		suxfix[mid_index++] = intElements.Top();
		suxfix[mid_index++] = ' ';
		intElements.pop();
	}
	suxfix[mid_index] = 0;
}
BigInteger countSuxfix(char *suxfix)
{
	int len = strlen(suxfix);
	BigInteger x;
	Strack <BigInteger >intElements;
	intElements.init();
	int i = 0;
	while (i<len) {
		if (suxfix[i] == ' ')
		{
			i++;
			continue;
		}
		switch (suxfix[i])
		{
			case '+':
				x = intElements.Top();
				intElements.pop();
				x = intElements.Top() + x;
				intElements.pop(); i++;
				break;
			case '-':
				x = intElements.Top();
				intElements.pop();
				x = intElements.Top() - x;
				intElements.pop();
				i++;
				break;
			case '*':
				x = intElements.Top();
				intElements.pop();
				x = intElements.Top()*x;
				intElements.pop();
				i++;
				break;
			case '/':
				x = intElements.Top();
				intElements.pop();
				x = intElements.Top() / x;
				intElements.pop();
				i++;
				break;
			default:
			{
				x = 0;
				while (suxfix[i] >= '0'&&suxfix[i] <= '9')
				{
					BigInteger aaaaaa=10;
					BigInteger bbbbbb=int(suxfix[i] - '0');
					BigInteger cccccc=x * aaaaaa;
					x = cccccc + bbbbbb;
					i++;
				}
			}
		}
		intElements.push(x);
	}
	return intElements.Top();
}

void fuzhi(BigInteger &a,string b)
{
	char laststr[1009];
	char firstr[1009];
	for(int i=0;i<=b.length()-1;i++)
	{
		firstr[i]=b[i];
	}
	change(firstr, laststr);
	cout<<laststr<<endl;
	a=countSuxfix(laststr);
}

int main()
{
    cin>>firststr;
    str=firststr;
    for(int i=1;i<=firststr.length()-2;i++)
    {
        for(int j=0;j<=11;j++)
        {
            if(j==10)
            {
                fuzhi(tempA,str.substr(0,i));
                fuzhi(tempB,str.substr(i+1,str.length()-i-1));
                ANS+=tempA+tempB;
            }
            else if(j==11)
            {
                fuzhi(tempA,str.substr(0,i));
                fuzhi(tempB,str.substr(i+1,str.length()-i-1));
                ANS+=tempA*tempB;
            }
            else
            {
                str[i]=j+'0';
                fuzhi(tempC,str);
                ANS+=tempC;
                str=firststr;
            }
        }
    }
    for(int i=1;i<=9;i++)
    {
        str[0]=i+'0';
        tempC=str;
        ANS+=tempC;
    }
    str=firststr;
    for(int i=0;i<=9;i++)
    {
        str[str.length()-1]=i+'0';
        tempC=str;
        ANS+=tempC;
    }
    cout<<ANS;
    return 0;
} //LikiBlaze Code
