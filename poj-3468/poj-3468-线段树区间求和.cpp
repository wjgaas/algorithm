/*
poj-3468 lazy优化, 否则超时
The sums may exceed the range of 32-bit integers
*/

#include <cstdio>
#include <cstdlib>

#define MAXN 100000

struct SegTree
{
	int left, right;
	__int64 sum, mark;
};

struct SegTree tree[MAXN*4];

void build_tree(int root, int left, int right)
{
	tree[root].left = left;
	tree[root].right = right;
	tree[root].mark = 0;

	if(left == right)
	{
		scanf("%d", &tree[root].sum);
		return;
	}

	int mid = (left + right) >> 1;

	build_tree(root<<1|1, left, mid);
	build_tree((root<<1)+2, mid+1, right);

	tree[root].sum = tree[root<<1|1].sum + tree[(root<<1)+2].sum;
}

__int64 query(int root, int left, int right, int L, int R)
{
	if(L==left && R==right)
	{
		return tree[root].sum + tree[root].mark*(__int64)(R-L+1);
	}

	if(tree[root].mark != 0)
	{
		tree[root<<1|1].mark += tree[root].mark;
		tree[(root<<1)+2].mark += tree[root].mark;
		tree[root].sum += tree[root].mark*(__int64)(R-L+1);
		tree[root].mark = 0;
	}

	int mid = (left + right) >> 1;

	if(R <= mid)
		return query(root<<1|1, left, mid, L, R);
	else if(L >mid)
		return query((root<<1)+2, mid+1, right, L, R);
	else
	{
		return query(root<<1|1, left, mid, L, mid) + \
			query((root<<1)+2, mid+1, right, mid+1, R);
	}
}

void update(int root, int left, int right, int L, int R, int val)
{
	if(L==left && R==right)
	{
		tree[root].mark += (__int64)val;
		return;
	}

	tree[root].sum += (__int64)val*(__int64)(R-L+1);

	int mid = (left + right) >> 1;

	if(R <= mid)
		update(root<<1|1, left, mid, L, R, val);
	else if(L >mid)
		update((root<<1)+2, mid+1, right, L, R, val);
	else
	{
		update(root<<1|1, left, mid, L, mid, val);
		update((root<<1)+2, mid+1, right, mid+1, R, val);
	}
}

int main(void)
{
	int N, Q;
	char str[10];

	 while(scanf("%d %d",&N,&Q)!=EOF)
	 {
		 build_tree(0,1,N);

		 while (Q--)
		 {
			 scanf("%s", str);
			 if(str[0] == 'Q')
			 {
				 int a,b;
				 scanf("%d %d", &a, &b);
				 printf("%lld\n", query(0,1,N,a,b));
			 }
			 else
			 {
				 int a,b,c;
				 scanf("%d %d %d", &a,&b,&c);
				 update(0,1,N,a,b,c);
			 }
		 }
	 }

	//system("PAUSE");
	return 0;
}
