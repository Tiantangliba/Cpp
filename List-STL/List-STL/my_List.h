#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<iostream>
#include<list>
#include<algorithm>
#include<assert.h>
using namespace std;

namespace my_list//��ͷ˫��ѭ������
{
	template<class T>
	struct list_node
	{
		T _data;
		list_node<T>* _next;
		list_node<T>* _prev;

		list_node(const T& val=T())
			:_data(val)
			, _next(nullptr)
			, _prev(nullptr)
		{}
	};

	template<class T,class Ref,class Ptr>//Ϊ��֧��const,����ģ��
	struct __list_iterator//���������������  ΪʲôҪ��һ�������Ľṹ�壿��Ϊ�����Ļ������������ʵ��ǽڵ㣬����ֱ���õ���������
	{
		typedef list_node<T> Node;
		typedef __list_iterator<T, Ref, Ptr> iterator;

		Node* _node;//���ĳ�Ա

		__list_iterator(Node* node)
			:_node(node)
		{}
		//ǧ����Ҫ�������ڵ������������

		bool operator!=(const iterator& it)const
		{
			return _node != it._node;
		}
		bool operator==(const iterator& it)const
		{
			return _node == it._node;
		}
		//T& operator*()//T���Զ�������AA������������*it���Զ�������AA,ûoperator*����
		Ref operator*()
		{
			return _node->_data;
		}

		//T* operator->()//�Ҿ�����->���ʣ����ǲ����������أ�
		Ptr operator->()//�Ҿ�����->����,���ǲ����������أ�
		{
			return &(operator*()); 
		}


		//++it
		iterator& operator++()
		{
			_node = _node->_next;
			return *this;
		}
		//it++
		iterator operator++(int)
		{
			iterator tmp(*this);
			_node = _node->_next;
			return tmp;
		}
		//--it
		iterator& operator--()
		{
			_node = _node->_prev;
			return *this;
		}
		//it--
		iterator& operator--(int)
		{
			iterator tmp(*tmp);
			_node = _node->_prev;
			return tmp;
		}
	};


	template<class T>
	class list
	{
		typedef list_node<T> Node;
	public:
		typedef __list_iterator<T,T&,T*> iterator;
		typedef __list_iterator<T, const T&, const T*> const_iterator;
		const_iterator begin()const
		{
			return const_iterator(_head->_next);
		}
		const_iterator end()const
		{
			return const_iterator(_head);
		}
		iterator begin()
		{
			return iterator(_head->_next);
		}
		iterator end()
		{
			return iterator(_head);
		}
		void empty_init()
		{
			_head = new Node;
			_head->_next = _head->_prev = _head;
		}
		list()
		{
			empty_init();
		}
		template<class InputIterator>
		list(InputIterator first, InputIterator last)
		{
			empty_init();

			while (first != last)
			{
				push_back(*first);
				first++;
			}
		}
		void swap(list<T>& x)
		{
		std::swap(_head, x._head);
		}

		list(const list<T>& lt)
		{
			empty_init();
			list<T> tmp(lt.begin(), lt.end());
			swap(tmp);
		}
		list<T>& operator=(list<T> lt)//��Ҫ������
		{
			swap(lt);
			return *this;
		}

		void clear()//clear����ͷ�ڵ�
		{
			iterator it = begin();
			while (it != end())
			{
				it=erase(it);
			}
		}
		~list()
		{
			clear();
			delete _head;
			_head = nullptr;
		}
		void push_back(const T& val)
		{
			//Node* newnode = new Node(val);

			//Node* tail = _head->_prev;
			////����
			//tail->_next = newnode;
			//newnode->_prev = tail;
			//newnode->_next = _head;
			//_head->_prev = newnode;
			insert(end(), val);
		}
		void push_front(const T& val)
		{
			inssert(begin(), val);
		}
		iterator insert(iterator pos, const T& val)
		{
			Node* newnode = new Node(val);

			Node* cur = pos._node;
			Node* prev = cur->_prev;

			//����
			prev->_next = newnode;
			newnode->_prev = newnode;
			newnode->_next = cur;
			cur->_prev = newnode;

			return iterator(newnode);
		}
		iterator erase(iterator pos)
		{
			assert(pos != end());
			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* next = cur->_next;
			prev->_next = next;
			next->_prev = prev;
			delete cur;
			return iterator(next);
		}
		void pop_front()
		{
			erase(begin());//erase�������ǲ���ͷ
		}
		void pop_back()
		{
			erase(--end());
		}

	private:
		Node* _head;
	};

	void Test1()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(3);
		lt.push_back(4);
		lt.push_back(6);
		lt.push_back(7);

	}

	struct AA
	{
		int _a1;
		int _a2;
		AA(int a1=0,int a2=0)
			:_a1(a1)
			, _a2(a2)
		{}

	};
	void Test2()
	{
		list<AA> lAA;
		lAA.push_back(AA(1, 3));
		lAA.push_back(AA());
		list<AA>::iterator it = lAA.begin();
		while (it != lAA.end())
		{
			cout << (*it)._a1 << " ";
			cout << it->_a1 << " ";
			it++;
		}
		cout << endl;
	}

	void Test3()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(3);
		lt.push_back(4);
		lt.push_back(6);
		lt.push_back(7);
		list<int> lt2;
		lt2 = lt;
		list<int> lt3=lt;
		for (auto& e : lt2)
		{
			cout << e << " ";
		}
		cout << endl;
		for (auto& e : lt3)
		{
			cout << e << " ";
		}
		cout << endl;

	}
}