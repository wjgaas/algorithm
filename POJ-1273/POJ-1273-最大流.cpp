#include <iostream>
#include <queue>

#define MAXN 201
using namespace std;

int cap[MAXN][MAXN];
int flow[MAXN][MAXN];
int pre[MAXN];
int a[MAXN];

int Edmonds_Karp(int s, int t)
{
	int sum = 0;
	queue<int> que;

	for( ; ; )
	{
		memset(a, 0, sizeof(a));
		a[s] = INT_MAX;

		que.push(s);
		while(!que.empty())
		{
			int u = que.front(); que.pop();

			for(int v=s; v<=t; v++)
			{
				if(!a[v] && flow[u][v] < cap[u][v])
				{
					que.push(v);
					pre[v] = u;
					a[v] = min(a[u], cap[u][v] - flow[u][v]);
				}
			}
		}

		if(a[t] == 0)
			break;

		sum += a[t];

		for(int i=t; i!=s; i=pre[i])
		{
			flow[pre[i]][i] += a[t];
			flow[i][pre[i]] -= a[t];
		}
	}

	return sum;
}

//int main()
//{
//	int m, n;
//
//	ios_base::sync_with_stdio(false);
//
//	while(cin >> m >> n)
//	{
//		memset(cap, 0, sizeof(cap));
//		memset(flow, 0, sizeof(flow));
//		memset(pre, 0, sizeof(pre));
//
//		int a, b, c;
//		for(int i=0; i<m; i++)
//		{
//			cin >> a >> b >> c;
//			cap[a][b] += c;
//		}
//
//		cout << Edmonds_Karp(1, n) << endl;
//	}
//}


