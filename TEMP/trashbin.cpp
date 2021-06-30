// 下面代码摘自笔者 NOIP2005 等价表达式
std::string convert(const std::string &s)
{ // 把中缀表达式转换为后缀表达式
	std::stack<char> oper;
	std::stringstream ss;
	ss << s;
	std::string t, tmp;
	while (ss >> tmp)
	{
		if (isdigit(tmp[0]))
			t += tmp + " "; // 1. 如果遇到一个数，输出该数
		else if (tmp[0] == '(')
			oper.push(tmp[0]); // 2. 如果遇到左括号，把左括号入栈
		else if (tmp[0] == ')')
		{ // 3. 如果遇到右括号，
			while (!oper.empty() && oper.top() != '(')
				t += std::string(1, oper.top()) + " ",
					oper.pop(); // 不断取出栈顶并输出，直到栈顶为左括号，
			oper.pop();			// 然后把左括号出栈
		}
		else
		{ // 4. 如果遇到运算符
			while (!oper.empty() && level[oper.top()] >= level[tmp[0]])
				t += std::string(1, oper.top()) + " ",
					oper.pop(); // 只要栈顶符号的优先级不低于新符号，就不断取出栈顶并输出
			oper.push(tmp[0]);	// 最后把新符号进栈
		}
	}
	while (!oper.empty())
		t += std::string(1, oper.top()) + " ", oper.pop();
	return t;
}
int calc(const std::string &s)
{ // 计算转换好的后缀表达式
	std::stack<int> num;
	std::stringstream ss;
	ss << s;
	std::string t, tmp;
	while (ss >> tmp)
	{
		if (isdigit(tmp[0]))
			num.push(stoi(tmp));
		else
		{
			int b, a; // 取出栈顶元素，注意顺序
			if (!num.empty())
				b = num.top();
			num.pop();
			if (!num.empty())
				a = num.top();
			num.pop();
			if (tmp[0] == '+')
				num.push(a + b);
			if (tmp[0] == '-')
				num.push(a - b);
			if (tmp[0] == '*')
				num.push(a * b);
			if (tmp[0] == '^')
				num.push(qpow(a, b));
		}
	}
	return num.top();
}