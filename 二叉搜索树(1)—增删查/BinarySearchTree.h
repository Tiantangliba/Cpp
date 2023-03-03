#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<iostream>
using namespace std;

template<class K>
struct BinarySearchTreeNode
{
	BinarySearchTreeNode<K>* _left;
	BinarySearchTreeNode<K>* _right;
	K _key;
	BinarySearchTreeNode(const K& key)
		:_left(nullptr)
		, _right(nullptr)
		, _key(key)
	{}
};


template<class K>
class BinarySearchTree
{
	typedef BinarySearchTreeNode<K> Node;
public:
	bool Insert(const K& key)
	{
		if (_root == nullptr)
		{
			_root = new Node(key);
			return true;
		}
		Node* parent = nullptr;//记录保存cur，为了链接
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)//插入的值大，往右走
			{
				parent = cur;//cur走之前保存cur
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;//cur走之前保存cur
				cur = cur->_left;
			}
			else//相等，插入失效
			{
				return false;
			}
		}
		cur = new Node(key);
		if (parent->_key < key)
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}
		return true;	
	}
	bool Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;//cur走之前保存cur
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;//cur走之前保存cur
				cur = cur->_left;
			}
			else//相等，插入失效
			{
				return true;
			}
		}
		return false;
	}
	bool Erase(const K& key)
	{
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else//开始删除
			{
				if (cur->_left == nullptr)//左为空，让父指向它的右
				{
					if (cur == _root)
					{
						_root = cur->_right;
					}
					else
					{
						if (cur == parent->_left)
						{
							parent->_left = cur->_right;
						}
						else//cur==parent->right
						{
							parent->_right = cur->_right;
						}
					}
					delete cur;
					cur = nullptr;
				}
				else if (cur->_right == nullptr)//右为空，让父指向它的左
				{
					if (cur == _root)
					{
						_root = cur->_left;
					}
					else
					{
						if (cur == parent->_left)
						{
							parent->_left = cur->_left;
						}
						else//cur==parent->right
						{
							parent->_right = cur->_left;
						}
					}
					delete cur;
					cur = nullptr;
				}
				else//左右都不为空，即有两个孩子,替换法删除
				{
					//找到右子树的最小节点进行替换
					Node* minParent = cur;//记录rightMin的上一个,且只能给cur，不能给nullptr
					Node* rightMin = cur->_right;
					while (rightMin->_left)
					{
						minParent = rightMin;
						rightMin = rightMin->_left;
					}
					swap(cur->_key, rightMin->_key);
					//此时，rightMin就是将要被删除的节点
					if (minParent->_left == rightMin)
					{
						minParent->_left = rightMin->_right;
					}
					else
					{
						minParent->_right = rightMin->_right;

					}
					delete rightMin;
				}
				return true;
			}
		}
		return false;
	}

	void InOrder()//直接调用_InOrder调用不了
		//法一：写个无参的,调用有参的；法二：getroot
	{
		_InOrder(_root);
	}

private:
	void _InOrder(Node* root)//中序遍历
	{
		if (root == nullptr)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}
private:
	Node* _root=nullptr;
};





