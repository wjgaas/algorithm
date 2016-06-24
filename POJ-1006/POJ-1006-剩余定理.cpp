#include <iostream>
#include <math.h>

using namespace std;

int gcd(int a, int b)
{
	while (a!=b)
	{
		if(a > b) a -= b;
		else b -= a;
	}

	return a;
}

int inv(int a, int b, int m)
{
	int ret = -1;
	int min = a*b / gcd(a, b);

	for(int i=1; i<1000; i++)
	{
		if( (min*i)%m == 1)
		{
			ret = min*i;
			break;
		}
	}

	return ret;
}

int main()
{
	int p, e, i, d;

	const int m1=23, m2=28, m3=33;
	int a1 = inv(m2, m3, m1);
	int a2 = inv(m1, m3, m2);
	int a3 = inv(m1, m2, m3);

	int cnt = 1;
	while (cin >> p >> e >> i >> d)
	{
		if (p == -1 && e == -1 && i == -1 && d == -1)
			break;
		int n = (a1 * p + a2 * e + a3 * i - d + 21252) % 21252;
		if (n == 0)
			n = 21252;
		cout << "Case " << cnt++ << ": the next triple peak occurs in " \
			 << n << " days." << endl;
	}
}
