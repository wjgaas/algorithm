#include <iostream>
#include <cmath>
#include <queue>
#include <utility>

#define MAXN 100001

using namespace std;

#include <functional>

typedef priority_queue<pair<double, int>,
					vector<pair<double, int> >,
					greater<pair<double, int> > > MinHeap;

int a[MAXN];
int pre[MAXN];
MinHeap heap;

void solve(int n, int k)
{
	heap.push(make_pair(log(a[0]), 0));

	for(int i=1; i<=n; i++)
	{
		pair<double, int> pp = heap.top();
		
		if(heap.size() >= k) heap.pop();

		heap.push(make_pair(pp.first + log(a[i]), i));

		pre[i] = pp.second;

		cout << pp.second << endl;
	}
}

int main()
{
	ios_base::sync_with_stdio(false);

	int n, k;

	cin >> n >> k;

	for(int i=0; i<n; i++)
		cin >> a[i];

	pre[0] = -1;

	solve(n-1, k);

	long long prod=1;
	for(int i=n-1; i>=0; i=pre[i])
	{
		prod *= a[i];
		prod %= 1000000007;
	}

	cout << prod << endl;
}


