#include <iostream>

struct TreeNode
{
	int val;
	TreeNode *lch;
	TreeNode *rch;

	TreeNode(int x) : val(x), lch(NULL), rch(NULL) {}
};

void inorderMirrosTraversal(TreeNode *root)
{
	TreeNode *cur = root, *prev = NULL;

	while (cur != NULL)
	{
		if(cur->lch == NULL)
		{
			std::cout << cur->val << std::endl;
			cur = cur->rch;
		}
		else
		{
			prev = cur->lch;

			while (prev->rch != NULL || prev->rch != cur)
				prev = prev->rch;

			if(prev->rch == NULL)
			{
				prev->rch = cur;
				cur = cur->lch;
			}
			else if(prev->rch == cur)
			{
				prev->rch = NULL;
				std::cout << cur->val << std::endl;
				cur = cur->rch;
			}
		}
	}
}

int main()
{

}