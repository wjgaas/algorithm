/*
hdu-1166 µÐ±ø²¼Õó
*/
#include <cstdio>
#include <cstdlib>

#define MAXN 50000
struct SegTree
{
	int left;
	int right;
	int sum;
};

struct SegTree tree[MAXN*4];

void build_tree(int root, int left, int right)
{
	tree[root].left = left;
	tree[root].right = right;

	if(left == right)
	{
		scanf("%d", &tree[root].sum);
		return;
	}

	int mid = (left + right) >> 1;
	
	build_tree(root<<1 | 1, left, mid);
	build_tree((root<<1)+2, mid+1, right);

	tree[root].sum = tree[root<<1|1].sum + tree[(root<<1)+2].sum;
}

void update(int root, int left, int right, int pos, int val)
{
	if(left ==right)
	{
		tree[root].sum += val;
		return;
	}

	int mid = (left + right) >> 1;

	if(pos <= mid)
		update(root<<1|1, left, mid, pos, val);
	else
		update((root<<1)+2, mid+1, right, pos, val);

	tree[root].sum = tree[root<<1|1].sum + tree[(root<<1)+2].sum;
}

int query(int root, int left, int right, int L, int R)
{
	if(L==left && R==right)
	{
		return tree[root].sum;
	}

	int mid = (left + right) >> 1;

	if(R <= mid)
		return query(root<<1|1, left, mid, L, R);
	else if(L > mid)
		return query((root<<1)+2, mid+1, right, L, R);
	else
	{
		return query(root<<1|1, left, mid, L, mid) + \
			query((root<<1)+2, mid+1, right, mid+1, R);
	}
}

int main(void)
{
	char str[10];
	int cnt=1;
	int T, n;
	int a, b;

	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		build_tree(0, 1, n);
		printf("Case %d:\n", cnt++);

		while(scanf("%s", str))
		{
			if(str[0]=='E')
				break;
			scanf("%d%d", &a, &b);

			if(str[0]=='Q')
			{
				printf("%d\n", query(0,1,n,a,b));
			}
			else if(str[0]=='A')
			{
				update(0,1,n,a,b);
			}
			else
			{
				update(0,1,n,a,-b);
			}
		}
	}

	system("PAUSE");
	return 0;
}
