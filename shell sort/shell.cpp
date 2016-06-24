#include <iostream>

using namespace std;

void shell(int *a, int len)
{
	int d = len;

	while (d > 1)
	{
		d = (d + 1) / 2;

		for (int i = 0; i < len - d; ++i)
		{
			if (a[i] > a[i + d])
				std::swap(a[i], a[i + d]);
		}
	}
}

int main()
{
	int a[] = { 10, 2, 3, 4, 5, 6, 7, 8, 9, 11 };

	shell(a, sizeof(a) / sizeof(a[0]));

	for (auto &x : a)
		std::cout << x << std::endl;

	return 0;
}
