#include <cstdio>

#define MAXN 15010
#define MAXM 32010

int stars[MAXN];
int y;
int max_x=0;

struct SegTree
{
	int left, right;
	int cnt;
}tree[MAXM<<2];

int level[MAXN];

void build_tree(int rt, int left, int right)
{
	tree[rt].left = left;
	tree[rt].right = right;
	tree[rt].cnt = 0;

	if(left == right)
		return;

	int mid = (left + right) >> 1;

	build_tree(rt<<1, left, mid);
	build_tree(rt<<1|1, mid+1, right);
}

void update(int rt, int x)
{
	tree[rt].cnt++;

	if(tree[rt].left == tree[rt].right
		&& tree[rt].left == x)
		return;

	int mid = (tree[rt].left + tree[rt].right) >> 1;

	if(x <= mid)
		update(rt<<1, x);
	else
		update(rt<<1|1, x);
}

int query(int rt, int L, int R)
{
	if(tree[rt].left == L && tree[rt].right == R)
		return tree[rt].cnt;

	int mid = (tree[rt].left + tree[rt].right) >> 1;

	if(R <= mid)
		return query(rt<<1, L, R);
	else if(L > mid)
		return query(rt<<1|1, L, R);
	else
		return query(rt<<1, L, mid) +
		query(rt<<1|1, mid+1, R);
}

int main(void)
{
	int T;
	scanf("%d", &T);

	for(int i=0; i<T; i++)
	{
		scanf("%d %d", &stars[i], &y);

		if(max_x < stars[i])
			max_x = stars[i];
	}

	build_tree(1, 0, max_x);

	for(int i=0; i<T; i++)
	{
		level[query(1,0,stars[i])]++;
		update(1, stars[i]);
	}

	for(int i=0; i<T; i++)
    {
        printf("%d\n", level[i]);
    }

	return 0;
}