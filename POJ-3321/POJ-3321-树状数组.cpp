#include <iostream>
#include <vector>

#define MAXM 100001

using namespace std;

struct range_t
{
	int left;
	int right;
};

typedef vector<vector<int> > edge_t;

edge_t edge(MAXM);
range_t range[MAXM];
int a_tree[MAXM];
bool forks[MAXM];
int N, M;

void dfs_tree(int node, int &key, edge_t &e, range_t *r)
{
	r[node].left = key;

	for(int i=0; i<e[node].size(); i++)
	{
		key++;
		dfs_tree(e[node][i], key, e, r);
	}
	r[node].right = key;
}

int lowbit(int x)
{
	return x&(-x);
}

int query(int *tree, range_t *r, int x)
{
	int pos = r[x].right;
	int rsum=0;
	for(; pos>=1; pos-=lowbit(pos))
		rsum += tree[pos];

	pos = r[x].left - 1;
	int lsum=0;
	for(; pos>=1; pos-=lowbit(pos))
		lsum += tree[pos];

	return rsum - lsum;
}

void update(int *tree, range_t *r, int x)
{
	int val = forks[x] ? -1 : 1;
	forks[x] = !forks[x];

	int pos = r[x].left;
	for(;pos<=N; pos+=lowbit(pos))
		tree[pos] += val;
}

int main()
{
	int a, b;
	char ch;

	memset(forks, false, sizeof(forks));
	memset(a_tree, 0, sizeof(a_tree));

	scanf("%d", &N);

	for(int i=0; i<N-1; i++)
	{
		scanf("%d %d", &a, &b);
		edge[a].push_back(b);
	}

	int key=1;
	dfs_tree(1, key, edge, range);

	for(int i=1;i<=N;i++)
		update(a_tree, range, i);

	scanf("%d", &M);
	getchar();

	while(M--)
	{
		scanf("%c %d", &ch, &a);
		getchar();

		if(ch == 'Q')
			printf("%d\n", query(a_tree, range, a));
		else
			update(a_tree, range, a);
	}
}
