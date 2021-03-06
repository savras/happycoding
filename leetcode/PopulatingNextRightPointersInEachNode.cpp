//https://leetcode.com/problems/populating-next-right-pointers-in-each-node/
/*
Given a binary tree

struct TreeLinkNode {
TreeLinkNode *left;
TreeLinkNode *right;
TreeLinkNode *next;
}
Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

Note:

You may only use constant extra space.
You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).
For example,
Given the following perfect binary tree,
1
/  \
2    3
/ \  / \
4  5  6  7
After calling your function, the tree should look like:
1 -> NULL
/  \
2 -> 3 -> NULL
/ \  / \
4->5->6->7 -> NULL

Observation:
Nothing too serious, since it asks for contstant space, recursion approach doesn't apply here.

Simply take advantage of the next pointer built at the higher level, you can traverse the node at
the same level from left to right. Then the next iteration always start from the left most node.
*/
namespace PopulatingNextRightPointersInEachNode
{
	/**
	* Definition for binary tree with next pointer.
	*/
	struct TreeLinkNode {
		int val;
		TreeLinkNode *left, *right, *next;
		TreeLinkNode(int x) : val(x), left(nullptr), right(nullptr), next(nullptr) {}
	};

	class SolutionPopulatingNextRightPointersInEachNode {
	private:
		void aux(TreeLinkNode *node, TreeLinkNode *next)
		{
			if (nullptr == node)
				return;
			node->next = next;
			aux(node->left, node->right);
			aux(node->right, node->next == nullptr ? nullptr : node->next->left);
		}
	public:
		void connect1(TreeLinkNode *root) {
			aux(root, nullptr);
		}
		void connect(TreeLinkNode *root) {
			if (nullptr == root)return;
			TreeLinkNode *tn = nullptr;
			while (root->left)
			{
				root->left->next = root->right;
				root->right->next = nullptr == root->next ? nullptr : root->next->left;
				tn = root;
				while (root->next)
				{
					root = root->next;
					root->left->next = root->right;
					root->right->next = nullptr == root->next ? nullptr : root->next->left;
				}
				root = tn->left;
			}
		}
	};
}
using PNRPENode = PopulatingNextRightPointersInEachNode::TreeLinkNode;
using PNRPESolution = PopulatingNextRightPointersInEachNode::SolutionPopulatingNextRightPointersInEachNode;
void TestPopulatingNextRightPointersInEachNode()
{
	PNRPENode root(1);
	PNRPENode four(4);
	PNRPENode five(5);
	PNRPENode six(6);
	PNRPENode seven(7);
	PNRPENode three(3);
	three.left = &six;
	three.right = &seven;
	PNRPENode two(2);
	two.left = &four;
	two.right = &five;
	root.left = &two;
	root.right = &three;
	PNRPESolution so;
	so.connect(&root);

	PNRPENode root1(1);
	PNRPENode two1(2);
	PNRPENode three1(3);
	root1.left = &two1;
	root1.right = &three1;
	so.connect(&root1);
}