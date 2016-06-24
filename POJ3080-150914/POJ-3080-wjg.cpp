/*
----------------------------------------------------------------------------------
	problem : Blue Jeans
	url : http://poj.org/problem?id=3080
	Author : WJG
	time : 2015.09.15
	comment : use KMP Search algorithm and enum all substring,
			  time complexity : O(N+M)
----------------------------------------------------------------------------------
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

//#define __DEBUG__

class KmpSearch
{
public:
	KmpSearch(std::string &N, std::string &M);

	bool search();

private:
	//create particial match table
	void __particial_match_table();

private:
	std::vector<int> m_pm_table;
	std::string m_N;
	std::string m_M;
};

KmpSearch::KmpSearch(std::string &N, std::string &M)
	: m_N(N), m_M(M)
{
	m_pm_table.resize(M.size(), 0);

	__particial_match_table();
}

void KmpSearch::__particial_match_table()
{
	int m=m_M.size();
	
	int begin=1, marched=0;
	while(begin + marched <= m)
	{
		if(m_M[begin + marched] == m_M[marched])
		{
			begin++;
			m_pm_table[begin + marched -1] = marched;
		}
		else
		{
			if(marched == 0) begin++;
			else
			{
				begin += marched - m_pm_table[marched -1];
				marched = m_pm_table[marched - 1];
			}
		}

	}

#ifdef __DEBUG__
	std::cout << "m_pm_table" << std::endl;

	for(int i=0; i<m_pm_table.size(); i++)
		std::cout << m_pm_table[i] << std::endl;
#endif
}

bool KmpSearch::search()
{
	int n = m_N.size();
	int m = m_M.size();

	int begin=0, marched=0;

	while ( (begin+marched) <= n)
	{
		if( m_N[begin+marched] == m_M[marched] && marched<m)
		{
			marched++;
			if(marched==m) 
			{ 
#ifdef __DEBUG__
				std::cout << "begin at : " << begin << std::endl;
#endif
				return true; 
			}
		}
		else
		{
			if(marched==0) begin++;
			else 
			{
				begin += marched - m_pm_table[marched - 1];
				marched = m_pm_table[marched - 1];
			}
		}
	}

	return false;
}

//compare func for sort
bool cmp(std::string a, std::string b)
{
    return strcmp(a.c_str(), b.c_str()) < 0;
}

//test case for kmp
void kmp_test(void)
{
	std::string test_string =  "GATACCAGATACCAGATACCAGATACCAGATACCAGA";
	std::string march = "GATACCAGATACCAGATACCAGATACC";

	KmpSearch kmp(test_string, march);
	kmp.search();
}

int main(void)
{
	int n, m;

	std::cin >> n;

	while (n--)
	{
		std::cin >> m;

		std::vector<std::string> samples(m);

		for(int i=0; i<m; i++)
		{
			std::cin >> samples[i];
		}

		//to store the max length substring to sort by alphabetical order
		std::vector<std::string> max_marched_str;
		bool break_flag = false;
		//enum sub string whose length is less than 3
		//length from max to 3
		for(int len=samples[0].size(); len>=3; len--)
		{
			break_flag = false;

			//begin position from 0
			for(int begin=0; begin+len<=samples[0].size(); begin++)
			{
				std::string sub_string = samples[0].substr(begin, len);

				//for all rest cases, test if substring is in it
				int result=true;
				for(int k=1; k<m; k++)
				{
					KmpSearch kmp(samples[k], sub_string);

					result = kmp.search();
					if(!result) break;

				}

				if(result)
				{
					//push the max length substring into vector
					//sort it after this length enum over
					max_marched_str.push_back(sub_string);
					break_flag = true;
				}
			}

			if(break_flag)
			{
				std::sort(max_marched_str.begin(), max_marched_str.end(), cmp);
				std::cout << max_marched_str[0] << std::endl;
				break;
			}
		}

		if(!break_flag)
			std::cout << "no significant commonalities" << std::endl;
	}

	return 0;
}
