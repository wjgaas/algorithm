/*
Find the top K number
using partition like quick sort
T(N)=T(N/2) + N/2 = T(N/4) + N/2 N/4 = 2N
O(N+KlogK)
*/
#include <iostream>
#include <vector>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost\random.hpp>

using namespace std;

inline void swap(int &a, int &b)
{
	int tmp=a;
	a=b;
	b=tmp;
}

int partition_k(vector<int> &a, int K, int left, int right)
{
	if(right-left+1 == K)
		return left;

	int l=left-1, r=left;
	for(; r<right; r++)
	{
		if(a[r]<=a[right])
			swap(a[++l], a[r]);
	}
	swap(a[l+1], a[right]);
	
	if(right-(l+1) +1 > K)
	{
		return partition_k(a, K, l+1, right);
	}
	else if(right-(l+1) +1 < K)
	{
		int num= K - (right-(l+1) +1);
		return partition_k(a, num, left, l<left?left:l);
	}
}

const int K=100;

int main(void)
{
	vector<int> a(1000000,1);

	boost::random::mt19937 gen;
	boost::random::uniform_int_distribution<> distribute(1,1000000);
	boost::random::variate_generator<boost::random::mt19937 &, boost::random::uniform_int_distribution<> > die(gen, distribute);

	for(vector<int>::iterator iter=a.begin(); \
		iter!=a.end(); iter++)
	{
		*iter = die();
	}
	random_shuffle(a.begin(), a.end());

	boost::posix_time::ptime tic=boost::posix_time::microsec_clock::local_time();
	int pos = partition_k(a, K, 0, a.size()-1);
	sort(a.begin()+pos, a.end());
	boost::posix_time::ptime toc=boost::posix_time::microsec_clock::local_time();
	cout << boost::posix_time::to_iso_string(toc - tic) << endl;

	for(vector<int>::iterator iter=a.begin()+pos; \
		iter!=a.end(); iter++)
	{
		cout << *iter << " ";
	}

	system("PAUSE");
	return 0;
}