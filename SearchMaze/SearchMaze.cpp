#include <iostream>
#include <vector>
#include <string>

using namespace std;

//to store the position in the maze
//reload operator +, =, ==, !=
struct point_t
{
	int x;
	int y;

	point_t() {}

	point_t(int x, int y)
	{
		this->x = x; this->y = y;
	}

	point_t& operator + (point_t &rhs)
	{
		point_t ret;
		ret.x = this->x + rhs.x;
		ret.y = this->y + rhs.y;

		return ret;
	}

	point_t& operator = (point_t &rhs)
	{
		this->x = rhs.x;
		this->y = rhs.y;

		return *this;
	}

	bool operator != (point_t &rhs)
	{
		if(this->x != rhs.x || this->y != rhs.y)
			return true;
		return false;
	}

	bool operator == (point_t &rhs)
	{
		if(this->x == rhs.x && this->y == rhs.y)
			return true;
		return false;
	}
};

//to store the search direction for dfs and bfs
struct direct_t
{
	point_t d[4];

	direct_t() {}

	direct_t(int p[4][2])
	{
		for(int i=0; i<4; i++)
		{
			d[i].x = p[i][0];
			d[i].y = p[i][1];
		}
	}

	point_t& operator = (point_t &rhs)
	{
		return rhs;
	}
};

class DFS
{
public:
	DFS(vector<string> &maze, string first_dir)
		:_maze(maze)
	{
		_h = _maze.size();
		_w = _maze[0].size();

		for(int i=0; i<_h; i++)
		{
			int j = maze[i].find('S');
			if(j != string::npos)
				_s = point_t(j, i);

			j = maze[i].find('E');
			if(j != string::npos)
				_e = point_t(j, i);
		}

		int r[4][2] = {{0,-1}, {-1,0}, {0,1}, {1,0}};
		_d = direct_t(r);

		if(_s.x == 0) _sdir = 2;
		else if(_s.x == _w-1) _sdir = 0;
		else if(_s.y == 0) _sdir = 3;
		else if(_s.y == _h-1) _sdir = 1;

		if(first_dir == "left") _lr=-1;
		else if(first_dir == "right") _lr=1;
	}

	int dfs() { return _search(_s, _sdir, 1); }

private:
	int _search(point_t p, int dir, int step)
	{
		for(int i=0; i<4; i++)
		{
			int idx = _lr==1? ((dir+3)%4+i)%4 : ((dir+1)%4-i+4)%4;

			point_t np = p + _d.d[idx];

			if(np == _e) return step+1;

			if(np.x>=0 && np.x<_w && np.y>=0 && np.y<_h \
				&& _maze[np.y][np.x]=='.')
				return _search(np, idx, step+1);
		}
	}

private:
	vector<string> _maze;
	int _w, _h;
	point_t _s, _e;
	direct_t _d;
	int _sdir;
	int _lr;
};

#include <queue>
class BFS
{
public:
	BFS(vector<string> &maze):_maze(maze)
	{
		_h = _maze.size();
		_w = _maze[0].size();

		for(int i=0; i<_h; i++)
		{
			int j = maze[i].find('S');
			if(j != string::npos)
				_s = point_t(j, i);

			j = maze[i].find('E');
			if(j != string::npos)
				_e = point_t(j, i);
		}

		int l[4][2] = {{0,-1}, {-1,0}, {0,1}, {1,0}};
		_d = direct_t(l);
	}

	int bfs()
	{
		vector<vector<int> > dist(vector<vector<int> >(_h,vector<int>(_w,1000)));

		queue<point_t> que;
		que.push(_s);
		dist[_s.y][_s.x] = 1;

		while(!que.empty())
		{
			point_t p = que.front(); que.pop();

			if(p == _e) break;

			for(int i=0; i<4; i++)
			{
				point_t np = p + _d.d[i];

				if(np.x>=0 && np.x<_w && np.y>=0 && np.y<_h \
					&& _maze[np.y][np.x]!='#' && dist[np.y][np.x]==1000)
				{
					dist[np.y][np.x] = dist[p.y][p.x] + 1;
					que.push(np);
				}
			}
		}

		return dist[_e.y][_e.x];
	}

private:
	vector<string> _maze;
	int _w, _h;
	point_t _s, _e;
	direct_t _d;
};


int main(void)
{
	int n;

	cin >> n;

	while(n--)
	{
		int w, h;

		cin >> w >> h;

		vector<string> maze;

		while(h--)
		{
			string line;
			cin >> line;
			maze.push_back(line);
		}

		DFS ldfs(maze, "left");
		cout << ldfs.dfs() << " ";

		DFS rdfs(maze, "right");
		cout << rdfs.dfs() << " ";

		BFS bfs(maze);
		cout << bfs.bfs() << endl;
	}

	return 0;
}

