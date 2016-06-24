#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class CyclicNumber
{
public:
	CyclicNumber(const string &str);
	~CyclicNumber();

	bool is_cyclic();

private:
	void __str2int(const string &str);
	bool __multiply(vector<int> &num, int mul);
	bool __is_circulate();

private:
	vector<int> m_num;
	vector<int> m_mul;
	int m_len;
};

CyclicNumber::CyclicNumber(const string &str)
	:m_num(str.size(),0), m_mul(str.size(),0), 
	 m_len(str.size())
{
	__str2int(str);
}

CyclicNumber::~CyclicNumber()
{
}

void CyclicNumber::__str2int(const string &str)
{
	for(int i=0; i<str.size(); i++)
		m_num[i] = str[i] - '0';
}

bool CyclicNumber::__multiply(vector<int> &num, int mul)
{
	int carry=0;
	for(int i=m_len-1; i>=0; i--)
	{
		int res = num[i]*mul;
		m_mul[i] = (res + carry)%10;
		carry = (res + carry) / 10;
	}

	//if the bits of the result of multiply is more than m_len
	//then the number is not cyclic
	if(carry)
		return true;
	else 
		return false;
}

bool CyclicNumber::__is_circulate()
{
	//find all possible start position that 
	//the result can be cyclic
	vector<int> start_pos;
	for(int i=0; i<m_len; i++)
	{
		if(m_num[i] == m_mul[0])
			start_pos.push_back(i);
	}

	for(int i=0; i<start_pos.size(); i++)
	{
		bool flag=0;
		for(int j=1; j<m_len; j++)
		{
			if(m_num[(start_pos[i]+j)%m_len] != m_mul[j])
			{
				flag = 1;
				break;
			}
		}
		if(flag == 0)
			return true;
	}

	return false;
}

bool CyclicNumber::is_cyclic()
{
	//test 1...m_len cases
	for(int i=2; i<=m_len; i++)
	{
		if(__multiply(m_num, i))
			return false;
		else
		{
			if(!__is_circulate())
				return false;
		}
	}

	return true;
}


int main(void)
{
	string input;

	while(cin >> input)
	{
		CyclicNumber cyclic(input);

		if(cyclic.is_cyclic())
			cout << input << " is cyclic" << endl;
		else
			cout << input << " is not cyclic" << endl;
	}

	return 0;
}
