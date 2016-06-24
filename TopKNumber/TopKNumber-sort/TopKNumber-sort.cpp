/*
Find the top K number
using quick sort
O(NlogN)
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost\random.hpp>

using namespace std;

const int K=100;

int main(void)
{
	vector<int> a(1000000,1);

	boost::random::mt19937 gen;
	boost::random::uniform_int_distribution<> dist(1,1000000);
	boost::random::variate_generator<boost::random::mt19937 &, boost::random::uniform_int_distribution<> > die(gen,dist);

	for(vector<int>::iterator iter=a.begin(); \
		iter!=a.end(); iter++)
	{
		*iter = die();
	}
	random_shuffle(a.begin(), a.end());

	boost::posix_time::ptime tic=boost::posix_time::microsec_clock::local_time();
	sort(a.begin(), a.end());
	boost::posix_time::ptime toc=boost::posix_time::microsec_clock::local_time();
	cout << boost::posix_time::to_iso_string(toc - tic) << endl;
	
	for(vector<int>::iterator iter=a.end()-K; \
		iter!=a.end(); iter++)
	{
		cout << *iter << " ";
	}

	system("PAUSE");
	return 0;
}