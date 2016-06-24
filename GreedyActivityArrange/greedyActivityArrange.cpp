/*

--------------------------------------------------------------------------------
	copy(istream_iterator<int>(cin),istream_iterator<int>(),back_inserter(ivec));

	vector<int> ivec(istream_iterator<int>(cin),istream_iterator<int>());

	copy(ivec.begin(),ivec.end(),ostream_iterator<int>(cout,"\t"));
--------------------------------------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

struct ActivityTime
{
public:
    ActivityTime(int ts, int te):m_ts(ts),m_te(te){}
    ActivityTime():m_ts(0), m_te(0){}

    int get_ts() { return m_ts; }
    int get_te() { return m_te; }

    friend bool operator < (const ActivityTime &lhs, const ActivityTime &rhs)
    {
        return lhs.m_te < rhs.m_te;
    }

private:
    int m_ts;
    int m_te;
};

class GreedyActivityArrange
{
public:
    GreedyActivityArrange(const vector<ActivityTime> &timelist):
        m_timelist(timelist)
    {
        m_cnt = timelist.size();
        m_flags.resize(m_cnt, false);
    }

    void arrange()
    {
        activity_time_sort();

		int current = 0;
		m_flags[0] = true;
		for(int i=1; i<m_cnt; i++)
		{
			if(m_timelist[i].get_ts() > m_timelist[current].get_te())
			{
				m_flags[i] = true;
				current = i;
			}
		}

		copy(m_flags.begin(), m_flags.end(), ostream_iterator<bool>(cout, "\t"));
		cout << endl;
    }

private:
    void activity_time_sort()
    {
        sort(m_timelist.begin(), m_timelist.end());
        for(vector<ActivityTime>::iterator iter=m_timelist.begin();
            iter!=m_timelist.end(); iter++)
        {
            cout << iter->get_ts() << " " << iter->get_te() << endl;
        }
    }

private:
    vector<ActivityTime> m_timelist;
    vector<bool> m_flags;
    int m_cnt;
};

int main(void)
{
    vector<ActivityTime> time_list;

    time_list.push_back(ActivityTime(1, 4));
    time_list.push_back(ActivityTime(3, 5));
    time_list.push_back(ActivityTime(0, 6));
    time_list.push_back(ActivityTime(5, 7));
    time_list.push_back(ActivityTime(3, 8));
    time_list.push_back(ActivityTime(5, 9));
    time_list.push_back(ActivityTime(6, 10));
    time_list.push_back(ActivityTime(8, 11));

    GreedyActivityArrange gaa(time_list);
    gaa.arrange();

    system("PAUSE");

    return 0;
}

