#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>

#define MAXN 10010

using namespace std;

struct SegTree
{
	int left, right, color;
	bool mark;
	int lchild, rchild;
};

SegTree tree[MAXN<<2];

int poster[MAXN][2];
pair<int, int> lines[2*MAXN];

void build_tree(int rt, int left, int right)
{
	tree[rt].left = left;
	tree[rt].right = right;
	tree[rt].color = -1;
	tree[rt].mark = false;
	tree[rt].lchild = rt<<1;
	tree[rt].rchild = rt<<1|1;

	if(left == right)
	{
		tree[rt].lchild = -1;
		tree[rt].rchild = -1;
		return;
	}

	int mid = (left+right) >> 1;

	build_tree(tree[rt].lchild, left, mid);
	build_tree(tree[rt].rchild, mid+1, right);
}

void update(int rt, int L, int R, int color)
{
	if(L<=tree[rt].left && R>=tree[rt].right)
	{
		tree[rt].mark = true;
		tree[rt].color = color;
		return;
	}
	
	if(tree[rt].mark == true)
	{
		tree[tree[rt].lchild].color = tree[rt].color;
		tree[tree[rt].rchild].color = tree[rt].color;
		tree[rt].mark = false;
	}

	int mid = (tree[rt].left + tree[rt].right) >> 1;

	if(L <= mid) update(tree[rt].lchild, L, R, color);
	if(R > mid) update(tree[rt].rchild, L, R, color);
}

bool hash_table[2*MAXN];

int query(int rt)
{
	memset(hash_table, false, sizeof(hash_table));

	if( (tree[rt].color == -1) && (tree[rt].lchild != tree[rt].rchild) )
	{
		return query(tree[rt].lchild) + query(tree[rt].rchild);
	}
	else
	{
		if(hash_table[tree[rt].color] == false)
		{
			hash_table[tree[rt].color] = true;
			return 1;
		}
		else
			return 0;
	}
}

int main(void)
{
	int T, n;

	scanf("%d", &T);

	while (T--)
	{
		scanf("%d", &n);

		for(int i=0; i<n; i++)
		{
			scanf("%d %d", &poster[i][0], &poster[i][1]);
			lines[i<<1].first = poster[i][0];
			lines[i<<1].second = -i-1;
			lines[i<<1|1].first = poster[i][1];
			lines[i<<1|1].second = i+1;
		}

		sort(lines, lines+(n<<1));

		int cnt=1;
		int tmp = lines[0].first;
		for(int i=1; i<(n<<1); i++)
		{
			if(tmp != lines[i].first)
			{
				cnt++;
				tmp = lines[i].first;
			}

			if(lines[i].second < 0)
				poster[-(lines[i].second+1)][0] = cnt;
			else
				poster[lines[i].second-1][1] = cnt;
		}

		build_tree(1, 1, cnt);

		for(int i=0; i<n; i++)
			update(1, poster[i][0], poster[i][1], i+1);

		printf("%d\n", query(1));

	}
	system("PAUSE");
	return 0;
}
