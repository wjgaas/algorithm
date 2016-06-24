#include <cstdio>
#include <cstdlib>
#include <cstring>

#define MAXN 1000005

int T;
int n, m, k;
int city[MAXN][2];
int points[MAXN];

int cmp(const void *aa, const void *bb)
{
	int *a=(int*)aa;
	int *b=(int*)bb;

	if(a[0] != b[0]) return a[0] - b[0];
	else return a[1] - b[1];
}

int lowbit(int x)
{
	return x&(-x);
}

void update(int x)
{
	for(;x<=k; x+=lowbit(x))
		points[x]++;
}

__int64 query(int x)
{
	__int64 sum=0;

	for(;x>0; x-=lowbit(x))
		sum += points[x];

	return sum;
}

int main()
{
	scanf("%d", &T);

	for(int i=0; i<T; i++)
	{
		scanf("%d %d %d", &n, &m, &k);

		for(int j=1; j<=k; j++)
		{
			scanf("%d %d", &city[j][0], &city[j][1]);
		}

		qsort(city[1], k, sizeof(city[1]), cmp);

		memset(points,0,sizeof(points));

		__int64 ans=0;
		for(int jj=1; jj<=k; jj++)
		{
			ans += query(m) - query(city[jj][1]);
			update(city[jj][1]);
		}

		printf("Test case %d: %I64d\n", i+1, ans);
	}
}

