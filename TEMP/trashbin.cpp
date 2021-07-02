#include <bits/stdc++.h>
using namespace std;
string Sa, Sb;
int main()
{
	getline(cin, Sa);
	getline(cin, Sb);
	int len = Sb.size();
	int p = 0;
	while (true)
	{
		p = Sa.find(Sb, max(0, p - len + 1));
		if (p == string::npos)
			break;
		Sa.erase(p, len);
	}
	cout << Sa;
	return 0;
}