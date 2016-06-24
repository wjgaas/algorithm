#include <iostream>
#include <algorithm>

#define MAXN 20002

using namespace std;

pair<int, int> cow[MAXN];
__int64 xtree[MAXN];
__int64 ctree[MAXN];

int lowbit(int x)
{
	return x&(-x);
}

void update(__int64 *tree, int x, int val)
{
	for(; x<=MAXN; x+=lowbit(x))
		tree[x] += val;
}

__int64 query(__int64 *tree, int x)
{
	__int64 sum=0;
	
	for(;x>=1; x-=lowbit(x))
		sum += tree[x];

	return sum;
}

int main()
{
	int T;
	cin >> T;

	for(int i=1; i<=T; i++)
	{
		cin >> cow[i].first 
			>> cow[i].second;
	}

	sort(cow+1, cow+1+T);

	memset(xtree, 0, sizeof(xtree));
	memset(ctree, 0, sizeof(ctree));

	__int64 ans=0;
	for(int i=1; i<=T; i++)
	{
		int v = cow[i].first;
		int x = cow[i].second;

		int cnt = query(ctree, x);
		__int64 dist = query(xtree, x);
		ans += (cnt*x-dist) * v;

		cnt = query(ctree, MAXN) - cnt;
		dist = query(xtree, MAXN)- dist;
		ans += (dist-cnt*x) * v;

		update(ctree, x, 1);
		update(xtree, x, x);
	}

	cout << ans << endl;
}
