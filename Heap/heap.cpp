#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class MinHeap
{
public:

	#define ERROR_EMPTY INT_MIN

	MinHeap(vector<int> &vec);
	~MinHeap();

	void make_heap();

	void move_up(int idx);

	void move_down(int parent);

	void push(int elem);

	int pop();

	bool empty();

private:
	void __swap(int &a, int &b);

private:
	vector<int> __heap;
};

MinHeap::MinHeap(vector<int> &vec)
	: __heap(vec)
{
}

MinHeap::~MinHeap()
{
}

void MinHeap::__swap(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

bool MinHeap::empty()
{
	return __heap.size() > 0 ? false : true;
}


void MinHeap::make_heap()
{
	int idx = __heap.size()/2 - 1;

	for(int i=idx; i>=0; i--)
	{
		move_down(i);
	}
}

void MinHeap::move_down(int parent)
{
	int lchild = 2*parent + 1;
	int rchild = lchild + 1;
	int min_child;

	if(lchild >= __heap.size()) return;
	else if(rchild >= __heap.size())
		min_child = lchild;
	else
		min_child = __heap[lchild] < __heap[rchild] ? lchild : rchild;

	if(__heap[min_child] < __heap[parent])
	{
		__swap(__heap[min_child], __heap[parent]);
		move_down(min_child);
	}
}

void MinHeap::move_up(int child)
{
	int parent = child/2;

	if(__heap[child] < __heap[parent])
	{
		__swap(__heap[child], __heap[parent]);

		if(parent != 0)
			move_up(parent);
	}
}

void MinHeap::push(int elem)
{
	__heap.push_back(elem);
	move_up(__heap.size() - 1);
}

int MinHeap::pop()
{
	int ret = ERROR_EMPTY;

	if(!empty())
	{
		ret = __heap[0];

		__heap[0] = __heap[__heap.size()-1];

		move_down(0);
	}

	return ret;
}
