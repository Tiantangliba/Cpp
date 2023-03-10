#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<set>
#include<map>
#include<string>
#include<functional>
using namespace std;

template<class K,class V>
struct AVLTreeNode
{
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;

	pair<K, V> _kv;
	int _bf;//ƽ������ balance facto
	AVLTreeNode(const pair<K, V>& kv)
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _kv(kv)
		, _bf(0)
	{}
};

template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	bool Insert(const pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			return true;
		}
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_kv.first>kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}
		
		cur = new Node(kv);
		if (parent->_kv.first < kv.first)
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}
		cur->_parent = parent;

		//��ʼ����ƽ��
		while (parent)
		{
			if (cur == parent->_left)
			{
				parent->_bf++;
			}
			else
			{
				parent->_bf--;
			}

			if (parent->_bf == 1 || parent->_bf == -1)//ԭ�����������߶���ȣ����ڲ��ȣ����ϸ���
			{
				parent = parent->_parent;
				cur = cur->_parent;
			}
			else if (parent->_bf == 0)//ԭ��һ�߸�һ�ߵͣ�����һ���ߣ������˵͵��Ǳߣ����ø�����
			{
				break;
			}
			else if (parent->_bf==2||parent->_bf==-2)//parent���������Ѿ���ƽ���ˣ���Ҫ��ת��ʹ֮ƽ��
			{
				if (parent->_bf == 2 && cur->_bf == 1)//����
				{
					RotateLeft(parent)��
				}
				else if (parent->_bf == -2 && cur->_bf == -1)//�ҵ���
				{
					RotateRight(parent)��
				}
				else if (parent->_bf == -2 && cur->_bf == 1)//����+����
				{
					RotateLR(parent);
				}
				else if (parent->_bf == 2 && cur->_bf == -1)
				{
					RotateRL(parent);
				}
				else
				{
					perror("�����㷨�д��������");
					exit(-1);
				}
				break;
			}
			else
			{
				perror("�����㷨�д��������");
				exit(-1);
			}
		}
		return true;
	}
	bool IsBalance()
	{
		return _IsBalance(_root);
	}

private:
	bool _IsBalance(Node* root)
	{
		if (root == nullptr)
			return true;
		int LeftHeight = Height(root->_left);
		int RightHeight = Height(root->_right);
		int diff = LeftHeight - RightHeight;

		if (diff != root->_bf)
		{
			cout << root->_kv.first << "ƽ�������д�" << endl;
			return fasle;
		}
		return abs(diff) < 2
			&& _IsBalance(root->_left)
			&& _IsBalance(root->_right);//�߶Ȳ�С��2��������������ƽ��

	}
	int Height(Node* root)
	{
		if (root == nullptr)
			return 0;
		int HeightLeft = Height(root->_left);
		int HeightRight = Height(root->_right);
		return max(HeightLeft, HeightRight) + 1;
	}
	void RotateLeft(Node* parent)
	{
		Node* subR = parent->_parent;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		subR->_left = parent;
		if (subRL)
		{
			subRL->_parent = parent;
		}
		if (parent == _root)
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		else//˵��parent���Ǹ������滹�нڵ�
		{
			Node* parentparent = parent->_parent;
			if (parentparent->_left == parent)
			{
				parentparent->_left = subR;
			}
			else
			{
				parentparent->_right = subR;
			}
			subR->_parent = parentparent;
		}
		parent->_parent = subR;
		subR->_bf = parent->_bf = 0;
	}
	void RotateRight(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		Node* pparent = parent->_parent;
		subL->_right = parent;
		parent->_left = subLR;
		if (subLR)
		{
			subLR->_parent = parent;
		}
		parent->_parent = subL;
		if (parent == _root)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			if (pparent->_left == parent)
			{
				pparent->_left = subL;
			}
			else
			{
				pparent->_right = subL;
			}
			subL->_parent = pparent
		}
		subL->_bf = parent->_bf = 0;
	}	
	void RotateLR(Node* parent)
	{
		Node* subL = parent->_left;//��ǰ��¼
		Node* subLR = subL->_right;//��ǰ��¼
		
		int bf = subLR->_bf;//��ǰ��¼
		
		RotateLeft(parent->_left);
		RotateRight(parent);

		subLR->_bf = 0;
		if (bf == 1)
		{
			subL->_bf = -1;
			parent->_bf = 0;
		}
		else if (bf == -1)
		{
			subL->_bf = 0;
			parent->_bf = 1;
		}
		else if (bf==0)
		{
			subL->_bf = 0;
			parent->_bf = 0;
		}
		else
		{
			perror("insert�������");
			exit(-1);
		}
	}
	void RotateRL(Node* parent)
	{
		Node* subR = parent->_right;//��ǰ��¼
		Node* subRL = subR->_left;//��ǰ��¼
		
		int bf = subRL->_bf;
		
		RotateR(parent->_right);
		RotateR(parent);

		if (bf == 0)
		{
			subR->_bf = 0;
			parent->_bf = 0;
			subRL->_bf = 0;
		}
		else if (bf == 1)
		{
			subR->_bf = 0;
			parent->_bf = -1;
			subRL->_bf = 0;
		}
		else if (bf == -1)
		{
			subR->_bf = 1;
			parent->_bf = 0;
			subRL->_bf = 0;
		}
		else
		{
			perror("insert�������");
			exit(-1);
		}
	}

private:
	Node* _root=nullptr;
};