#include <windows.h>

#include <bits/stdc++.h>
#define l1 262
#define l2 294
#define l3 330
#define l4 349
#define l5 392
#define l6 440
#define l7 493

#define n1 532
#define n2 588
#define n3 660
#define n4 698
#define n5 784
#define n6 880
#define n7 988

#define h1 1046
#define h2 1175
#define h3 1319
#define h4 1397
#define h5 1568
#define h6 1760
#define h7 1976

#define A 1600 * 1.25 //四拍
#define B 800 * 1.25  //两拍
#define C 400 * 1.25  //一拍
#define D 200 * 1.25  //半拍
#define E 100 * 1.25  //1/4拍
#define F 50 * 1.25	  //1/8拍
int main()
{
	while (true)
	{
		Beep(l3, D);
		Beep(l5, D);
		Beep(l6, C);
		Beep(n1, D);
		Beep(n2, D);
		Beep(n1, D);
		Beep(l5, D);
		Beep(l4, D);
		Beep(l3, D);
		Beep(l5, D);
		Beep(n1, C);
		Sleep(C);
		Beep(n1, D);
		Beep(l7, D);
		Beep(l6, C);
		Beep(n1, C);
		Beep(l7, D);
		Beep(l5, C);
		Beep(l5, D);
		Beep(h5, C);
		Sleep(B);
		Beep(l3, D);
		Beep(l5, D);
		// Beep(h7, D);
	}
}