#include<stdio.h>
#include<stdlib.h>
/*
���� �� ��, a�� ��Ȳ�� ���� Power, Stamina, ��Ÿ ����� �Ǵ� ��
*/
class Status {
	int iX, iY;
	int Power, Stamina, Intel, Luck, Dex, Wealth, Beauty;

	void limit(int a) {
		if (a <= 0) {
			a = 0;
		}
		if (0<a<100)
		{
			a = a;
		}
		else {
			a = 100;
		};
	}

};