#include <iostream>
#include <algorithm>

using namespace std;

#define MAXN 51
#define MAXM 101

using namespace std;

char dna[MAXM][MAXN];
pair<int, int> unsorted[MAXM];

int unsortedness(char *dna, int len)
{
	int sum=0;

	for(int i=0; i<len; i++)
	{
		for(int j=i+1; j<len; j++)
		{
			if(dna[i] > dna[j])
				sum += 1;
		}
	}

	return sum;
}


int main()
{
	int n, m;

	cin >> n >> m;

	for(int i=0; i<m; i++)
	{
		cin >> dna[i];
		unsorted[i].first = unsortedness(dna[i], n);
		unsorted[i].second = i;
	}

	stable_sort(unsorted, unsorted+m);

	for(int i=0; i<m; i++)
	{
		cout << dna[unsorted[i].second] << endl;
	}
}