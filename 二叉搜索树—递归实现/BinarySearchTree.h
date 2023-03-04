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

	bool FindR(const K& key)//递归法查找
	{
		return _FindR(_root, key);
	}
	bool InsertR(const K& key)//递归法插入
	{
		return _InsertR(_root, key);
	}
	bool EraseR(const K& key)//递归删除
	{
		return _EraseR(_root, key);
	}
	~BinarySearchTree()
	{
		_Destroy(_root);
	}
	BinarySearchTree(const BinarySearchTree<K>& t)//拷贝构造
		//拷贝构造也是构造。写了仍一种构造，都不会生成构造
	{
		_root = _Copy(t._root);
	}
	//BinarySearchTree()
	//{}
	//C++11:强制编译器生成默认构造
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


	bool _EraseR(Node*& root, const K& key)//递归删除
	{
		if (root == nullptr)
		{
			return false;
		}
		if (root->_key == key)//删除 左为空或右为空或左右都不为空
		{
			Node* del = root;//记录一下，方便删除
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
				//找右树的最左节点，进行替换后删除
				Node* min = root->_right;
				while (min->_left)
				{
					min = min->_left;
				}
				//已经找到，交换一下节点的值
				swap(root->_key, min->_key);
				//交换完毕，开始删除min这个节点
				//return Erase(key);//错误，此时树的结构已进变化
				return _Erase(root->_right, key);//正确，转换成到子树去找
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


	bool _Insert(Node*& root, const K& key)//递归插入
		        // 加上引用，不用传二级指针，而且不用手动链接
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
		else if (root->_key < key)//插的值比你大，往你的右树插入
		{
			return _Insert(root->_right, key);
		}
		else                       //插的值比你小，往你的左树插入
		{
			return _Insert(root->_left, key);
		}
	}

	bool _Find(Node* root, const K& key)//递归法查找
	{
		if (root == nullptr)
		{
			return false;
		}
		if (root->_key == key)
		{
			return true;
		}
		else if (root->_key < key)//找的值比你大，往右找
		{
			return _Find(root->_right, key);
		}
		else                       //找的值比你小，往左找
		{
			return _Find(root->_left, key);
		}
	}

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





