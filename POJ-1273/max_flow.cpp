#include <iostream>
#include <vector>

#define MAXN 201

using namespace std;

struct edge{ int to, cap, rev; };

vector<edge> G[MAXN];
bool visit[MAXN];

void add_edge(int from, int to, int cap)
{
	edge e1 = {to, cap, G[to].size()};
	G[from].push_back(e1);
	edge e2 = {from, 0, G[from].size()-1};
	G[to].push_back(e2);
}

int dfs(int v, int t, int f)
{
	if(v == t) return f;
	visit[v] = true;

	for(int i=0; i<G[v].size(); i++)
	{
		edge &e = G[v][i];

		if(!visit[e.to] && e.cap>0)
		{
			int d = dfs(e.to, t, min(f, e.cap));
			if(d>0)
			{
				e.cap -= d;
				G[e.to][e.rev].cap += d;
				return d;
			}
		}
	}
	return 0;
}

int max_flow(int s, int t)
{
	int flow=0;

	for(;;)
	{
		memset(visit, false, sizeof(visit));
		int f = dfs(s, t, INT_MAX);
		if(f == 0) return flow;
		flow += f;
	}
}

int main()
{
	int m, n;

	ios_base::sync_with_stdio(false);

	while(cin >> m >> n)
	{
		for(int i=0; i<MAXN; i++)
			G[i].clear();

		int a, b, c;
		for(int i=0; i<m; i++)
		{
			cin >> a >> b >> c;
			add_edge(a, b, c);
		}

		cout << max_flow(1, n) << endl;
	}
}
