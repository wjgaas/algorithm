#include <cstdio>

#define MAXN 15010
#define MAXM 32010

int tree[MAXM];
int y;
int max_x=0;

int stars[MAXN];
int level[MAXN];

int lowbit(int x)
{
	return x&(-x);
}

void update(int x)
{
	for(; x <= max_x+1; x+=lowbit(x))
		tree[x]++;
}

int query(int x)
{
	int sum = 0;

	for(;x>0; x-=lowbit(x))
		sum += tree[x];

	return sum;
}

int main()
{
	int T;

	scanf("%d", &T);

	for(int i=1; i<=T; i++)
	{
		scanf("%d %d", &stars[i], &y);
		stars[i]++;
		if(max_x < stars[i]) max_x = stars[i];
	}

	for(int i=1; i<=T; i++)
	{
		level[query(stars[i])]++;
		update(stars[i]);
	}

	for(int i=0; i<T; i++)
    {
        printf("%d\n", level[i]);
    }
}