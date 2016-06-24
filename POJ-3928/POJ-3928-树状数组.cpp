#include <iostream>
#include <algorithm>

#define MAXN 22000

using namespace std;

struct Player
{
	int level, id;
}player[MAXN];

int tree[MAXN];

bool cmp(Player a, Player b)
{
	return a.level < b.level;
}

int lowbit(int x)
{
	return x&(-x);
}

void update(int x, int max)
{
	for(;x<=max; x+=lowbit(x))
		tree[x] += 1;
}

__int64 query(int x)
{
	__int64 sum=0;

	for(;x>=1; x-=lowbit(x))
		sum += tree[x];
	return sum;
}

int main()
{
	int T, N;
	cin >> T;
	while (T--)
	{
		cin >> N;
		for(int i=1; i<=N; i++)
		{
			cin >> player[i].level;
			player[i].id = i;
		}

		sort(player+1, player+1+N, cmp);
		memset(tree,0,sizeof(tree));

		__int64 ans=0;
		__int64 l, r;
		for(int i=1; i<=N; i++)
		{
			l = query(player[i].id);
			r = query(N) - l;
			ans += l*(N-player[i].id-r) + r*(player[i].id-l-1);
			update(player[i].id, N);
		}
		cout << ans << endl;
	}
}

