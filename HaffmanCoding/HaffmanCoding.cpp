/*
----------------------------------------------------------------------------------
	problem : Haffman Coding
	Author : W.J.G
	time : 2015.09.20
	comment : use min heap to get the minist two nodes
			  and push the sum of them into heap again
			  until the heap size is 1.
----------------------------------------------------------------------------------
*/

#include <iostream>
#include <vector>

using namespace std;

//haffman node to store a char and weight
struct haffman_node_t
{
	char _val;
	int _w;
	haffman_node_t *lchild;
	haffman_node_t *rchild;

	haffman_node_t(char val, int weight, \
		haffman_node_t *left=NULL, haffman_node_t *right=NULL)
		: _val(val), _w(weight), lchild(left), rchild(right)
	{}

	bool operator < (haffman_node_t rhs)
	{
		return this->_w < rhs._w;
	}
};

//min heap for haffman coding
class MinHeap
{
public:

	MinHeap(vector<haffman_node_t*> &vec);
	MinHeap(){}
	~MinHeap();

	void make_heap();

	void move_up(int idx);

	void move_down(int parent);

	void push(haffman_node_t* elem);

	void pop();

	haffman_node_t* top();

	bool empty();

	int size() { return __heap.size(); }

private:
	void __swap(haffman_node_t* &a, haffman_node_t* &b);

private:
	vector<haffman_node_t*> __heap;
};

MinHeap::MinHeap(vector<haffman_node_t*> &vec)
	: __heap(vec)
{
	make_heap();
}

MinHeap::~MinHeap()
{
}

void MinHeap::__swap(haffman_node_t* &a, haffman_node_t* &b)
{
	haffman_node_t* tmp = a;
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
		min_child = *__heap[lchild] < *__heap[rchild] ? lchild : rchild;

	if(__heap[min_child] < __heap[parent])
	{
		__swap(__heap[min_child], __heap[parent]);
		move_down(min_child);
	}
}

void MinHeap::move_up(int child)
{
	int parent = child/2;

	if(*__heap[child] < *__heap[parent])
	{
		__swap(__heap[child], __heap[parent]);

		if(parent != 0)
			move_up(parent);
	}
}

void MinHeap::push(haffman_node_t* elem)
{
	__heap.push_back(elem);
	move_up(__heap.size() - 1);
}

haffman_node_t* MinHeap::top()
{
	if(!empty()) 
		return __heap[0];
	else  
		return 0;
}


void MinHeap::pop()
{
	if(!empty())
	{
		__heap[0] = __heap[__heap.size()-1];
		__heap.pop_back();

		move_down(0);
	}
}

//haffman coding argorithm
class HaffmanCoding
{
public:

	HaffmanCoding(vector<char> &val, vector<int> &w);

	~HaffmanCoding() { __destroy(_root); }

	void coding();

	void decoding();

private:
	void __destroy(haffman_node_t *node);

	void __traverse(haffman_node_t *node, int layer, vector<int> &code);

private:
	haffman_node_t *_root;
	MinHeap _heap;
	int _size;
};

//push all nodes into min heap
HaffmanCoding::HaffmanCoding(vector<char> &val, vector<int> &w)
{
	_size = val.size();
	for(int i=0; i<_size; i++)
	{
		_heap.push(new haffman_node_t(val[i], w[i]));
	}
}

//pop 2 nodes out and push the sum of them in
void HaffmanCoding::coding()
{
	while(_heap.size() > 1)
	{
		haffman_node_t *left = _heap.top();		_heap.pop();
		haffman_node_t *right = _heap.top();	_heap.pop();

		_heap.push(new haffman_node_t('$', left->_w + right->_w, left, right));
	}

	_root = _heap.top();
}

//delete nodes from root
void HaffmanCoding::__destroy(haffman_node_t *node)
{
	if(node->lchild != NULL)	 __destroy(node->lchild);
	if(node->rchild != NULL)	 __destroy(node->rchild);

	if(node->lchild == NULL && node->rchild == NULL)
		delete node;
}

//traverse all the nodes from left to right
void HaffmanCoding::__traverse(haffman_node_t *node, int layer, vector<int> &code)
{
	if(node->lchild != NULL)
	{
		code[layer] = 1;
		__traverse(node->lchild, layer+1, code);
	}

	if(node->rchild != NULL)
	{
		code[layer] = 0;
		__traverse(node->rchild, layer+1, code);
	}

	if(node->lchild == NULL && node->rchild == NULL)
	{
		cout << node->_val << " ";

		for(int i=0; i<layer; i++)
			cout << code[i] << " ";
		cout << endl;
	}
}

//left node is coding to 1, and right to 0
void HaffmanCoding::decoding()
{
	vector<int> code(_size, 0);
	__traverse(_root, 0, code);
}

#include <string>
int main(void)
{
	char val[100];
	int weight[100];

	int m;
	cin >> m;

	while (m--)
	{
		int n;
		cin >> n;

		for(int i=0; i<n; i++)
			cin >> val[i];

		for(int i=0; i<n; i++)
			cin >> weight[i];

		vector<char> nval(val,val+n);
		vector<int> nweight(weight, weight+n);

		HaffmanCoding *hf = new HaffmanCoding(nval, nweight);
		hf->coding();
		hf->decoding();

		delete hf;
	}

	system("PAUSE");

	return 0;
}
