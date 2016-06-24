#include <iostream>

using namespace std;

void bubble(int *a, int len)
{
	bool exchange = false;

	for (int i = 1; i < len; ++i)
	{
		exchange = false;

		for (int j = len - 1; j >= i; --j)
		{
			if (a[j] < a[j - 1])
			{
				std::swap(a[j], a[j - 1]);

				exchange = true;
			}
		}

		if (!exchange) break;
	}
}


int main()
{
	int a[] = {10,2,3,4,5,6,7,8,9,11};

	bubble(a, sizeof(a)/sizeof(a[0]));

	for (auto &x : a)
		std::cout << x << std::endl;

	return 0;
}