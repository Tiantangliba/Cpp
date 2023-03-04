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

	bool FindR(const K& key)//�ݹ鷨����
	{
		return _FindR(_root, key);
	}
	bool InsertR(const K& key)//�ݹ鷨����
	{
		return _InsertR(_root, key);
	}
	bool EraseR(const K& key)//�ݹ�ɾ��
	{
		return _EraseR(_root, key);
	}
	~BinarySearchTree()
	{
		_Destroy(_root);
	}
	BinarySearchTree(const BinarySearchTree<K>& t)//��������
		//��������Ҳ�ǹ��졣д����һ�ֹ��죬���������ɹ���
	{
		_root = _Copy(t._root);
	}
	//BinarySearchTree()
	//{}
	//C++11:ǿ�Ʊ���������Ĭ�Ϲ���
	BinarySearchTree() = default;
	BinarySearchTree<K>& operator = (BinarySearchTree<K> t)
	{
		swap(_root, t._root);
		return *this;
	}


private:
	Node* _Copy(Node* root)
	{
		if (root == nullptr)
			return nullptr;
		Node* copyroot = new Node(root->_key);
		copyroot->_left = _Copy(root->_left);
		copyroot->_right = _Copy(root->_right);
		return copyroot;
	}
	void _Destroy(Node*& root)
	{
		if (root == nullptr)
			return;
		_Destroy(root->_left);
		_Destroy(root->_right);
		delete root;
		root = nullptr;
	}


	bool _EraseR(Node*& root, const K& key)//�ݹ�ɾ��
	{
		if (root == nullptr)
		{
			return false;
		}
		if (root->_key == key)//ɾ�� ��Ϊ�ջ���Ϊ�ջ����Ҷ���Ϊ��
		{
			Node* del = root;//��¼һ�£�����ɾ��
			if (root->_left == nullptr)
			{
				root = root->_right;
			}
			else if (root->_right == nullptr)
			{
				root = root->_left;
			}
			else
			{
				//������������ڵ㣬�����滻��ɾ��
				Node* min = root->_right;
				while (min->_left)
				{
					min = min->_left;
				}
				//�Ѿ��ҵ�������һ�½ڵ��ֵ
				swap(root->_key, min->_key);
				//������ϣ���ʼɾ��min����ڵ�
				//return Erase(key);//���󣬴�ʱ���Ľṹ�ѽ��仯
				return _Erase(root->_right, key);//��ȷ��ת���ɵ�����ȥ��
			}
			delete del;
			return true;
		}

		else if (root->_key < key)
		{
			return _EraseR(root->_right, key);
		}
		else                       
		{
			return _EraseR(root->_left, key);
		}
	}


	bool _Insert(Node*& root, const K& key)//�ݹ����
		        // �������ã����ô�����ָ�룬���Ҳ����ֶ�����
	{
		if (root == nullptr)
		{
			root = new node(key);
			return true;
		}
		if (root->_key == key)
		{
			return false;
		}
		else if (root->_key < key)//���ֵ������������������
		{
			return _Insert(root->_right, key);
		}
		else                       //���ֵ����С���������������
		{
			return _Insert(root->_left, key);
		}
	}

	bool _Find(Node* root, const K& key)//�ݹ鷨����
	{
		if (root == nullptr)
		{
			return false;
		}
		if (root->_key == key)
		{
			return true;
		}
		else if (root->_key < key)//�ҵ�ֵ�����������
		{
			return _Find(root->_right, key);
		}
		else                       //�ҵ�ֵ����С��������
		{
			return _Find(root->_left, key);
		}
	}

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





