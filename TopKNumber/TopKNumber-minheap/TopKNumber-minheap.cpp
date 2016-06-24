/*
Find the top K number
using minheap
T(N)=T(N/2) + N/2 = T(N/4) + N/2 N/4 = 2N
O(NlogK)
*/
#include <iostream>
#include <queue>
#include <boost\date_time\posix_time\posix_time.hpp>
#include <boost\random.hpp>

using namespace std;
typedef priority_queue<int, vector<int>, greater<int> > MinHeap;

vector<int> sys_heap(vector<int> &a, int K);
vector<int> my_heap(vector<int> &a, int K);

const int K=100;

int main(void)
{
	vector<int> a(1000000,1);

	boost::random::mt19937 gen;
	boost::random::uniform_int_distribution<> dist(1,1000000);
	boost::random::variate_generator<boost::random::mt19937 &, boost::random::uniform_int_distribution<> > die(gen, dist);

	for(vector<int>::iterator iter=a.begin(); \
		iter!=a.end(); iter++)
	{
		*iter = die();
	}

	boost::posix_time::ptime tic=boost::posix_time::microsec_clock::local_time();

	vector<int> aa = my_heap(a, K);

	boost::posix_time::ptime toc=boost::posix_time::microsec_clock::local_time();
	cout << boost::posix_time::to_iso_string(toc - tic) << endl;

	//for(vector<int>::iterator iter=aa.begin(); \
	//	iter!=aa.end(); iter++)
	//{
	//	cout << *iter << " ";
	//}

	system("PAUSE");
	return 0;
}

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void adjust_heap(vector<int> &a, int parent)
{
	int lchild = 2*parent + 1;
	int rchild = 2*parent + 2;
	int min_child;

	if(lchild > a.size()-1) return;
	else if(rchild > a.size()-1) min_child = lchild;
	else min_child = a[lchild] < a[rchild] ? lchild : rchild;

	if(a[min_child] < a[parent])
	{
		swap(a[min_child], a[parent]);
		adjust_heap(a, min_child);
	}
}

void make_heap(vector<int> &a)
{
	int none_leaf=(a.size()-2)/2;
	for(int i=none_leaf; i>=0; i--)
	{
		adjust_heap(a, none_leaf);
	}
}

vector<int> my_heap(vector<int> &a, int K)
{
	vector<int> hp;
	for(vector<int>::iterator iter=a.begin(); \
		iter!=a.begin()+K; iter++)
	{
		hp.push_back(*iter);
	}

	make_heap(hp);

	for(vector<int>::iterator iter=a.begin()+K; \
		iter!=a.end(); iter++)
	{
		if(*iter>hp[0])
		{
			hp[0] = *iter;
			adjust_heap(hp, 0);
		}
	}

	sort(hp.begin(), hp.end());

	return hp;
}

vector<int> sys_heap(vector<int> &a, int K)
{
	MinHeap hp;
	for(vector<int>::iterator iter=a.begin(); \
		iter!=a.begin()+K; iter++)
	{
		hp.push(*iter);
	}

	for(vector<int>::iterator iter=a.begin()+K; \
		iter!=a.end(); iter++)
	{
		if(*iter>hp.top())
		{
			hp.pop();
			hp.push(*iter);
		}
	}

	vector<int> aa(K,1);
	for(vector<int>::iterator iter=aa.begin(); \
		iter!=aa.end(); iter++)
	{
		*iter = hp.top();
		hp.pop();
	}

	sort(aa.begin(), aa.end());

	return aa;
}