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
		Node* parent = nullptr;//��¼����cur��Ϊ������
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)//�����ֵ��������
			{
				parent = cur;//cur��֮ǰ����cur
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;//cur��֮ǰ����cur
				cur = cur->_left;
			}
			else//��ȣ�����ʧЧ
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
				parent = cur;//cur��֮ǰ����cur
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;//cur��֮ǰ����cur
				cur = cur->_left;
			}
			else//��ȣ�����ʧЧ
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
			else//��ʼɾ��
			{
				if (cur->_left == nullptr)//��Ϊ�գ��ø�ָ��������
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
				else if (cur->_right == nullptr)//��Ϊ�գ��ø�ָ��������
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
				else//���Ҷ���Ϊ�գ�������������,�滻��ɾ��
				{
					//�ҵ�����������С�ڵ�����滻
					Node* minParent = cur;//��¼rightMin����һ��,��ֻ�ܸ�cur�����ܸ�nullptr
					Node* rightMin = cur->_right;
					while (rightMin->_left)
					{
						minParent = rightMin;
						rightMin = rightMin->_left;
					}
					swap(cur->_key, rightMin->_key);
					//��ʱ��rightMin���ǽ�Ҫ��ɾ���Ľڵ�
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

	void InOrder()//ֱ�ӵ���_InOrder���ò���
		//��һ��д���޲ε�,�����вεģ�������getroot
	{
		_InOrder(_root);
	}

private:
	void _InOrder(Node* root)//�������
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





