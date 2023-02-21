#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
#include<string>
#include<assert.h>
using namespace std;

namespace my_vector
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;

		iterator begin()
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}
		const_iterator begin()const
		{
			return _start;
		}
		const_iterator end()const
		{
			return _finish;
		}
		vector()
			:_start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{}

		vector(size_t n, const T& val = T())
			:_start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
			reserve(n);
			for (size_t i = 0; i < n; i++)
			{
				push_back(val);
			}
		}

		vector(const vector<T>& v)//��������
		{
			_start = new T[v.size()];
			for (size_t i = 0; i < v.size(); i++)
			{
				//������memcpy��vector<vector<int>>��ǳ����
				_start[i] = v._start[i];
			}
			_finish = _start + v.size();
			_end_of_storage = _start + v.capacity();
		}


		//vector(const vector<T>& v)//��������
		//	:_start(nullptr)
		//	, _finish(nullptr)
		//	, _end_of_storage(nullptr)
		//{
		//	reserve(v.size());
		//	for (const auto& e : v)
		//	{
		//		push_back(e);
		//	}
		//}
		template<class InputIterator>//ΪʲôҪ��������ģ�壿
		vector(InputIterator first, InputIterator last)//���������乹��
			:_start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
			while(first != last)
			{
				push_back(*first);
				first++;
			}
		}

		void swap(vector<int>& v)
		{
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_end_of_storage, v._end_of_storage);
		}
		//vector(const vector<T>& v)//��������,��������ã��������޵ݹ�
		//		:_start(nullptr)
		//		, _finish(nullptr)
		//		, _end_of_storage(nullptr)
		//{
		//	vector<T> tmp(v.begin(),v.end());
		//	//vector tmp(v);//����
		//	swap(tmp);
		//}
		vector<T>& operator=(vector<T> v)//��ֵ����,������
		{
			swap(v);
			return *this;
		}

		~vector()
		{
			delete[]_start;
			_start = _finish = _end_of_storage = nullptr;
		}
		const T& operator[](size_t pos)const
		{
			assert(pos < size());
			return _start[pos];
		}
		size_t capacity()const//����
		{
			return _end_of_storage - _start;
		}
		size_t size()const//����
		{
			return _finish - _start;
		}
		void reserve(size_t n)//reserve���ı�size
		{
			if (n > capacity())
			{
				size_t sz = size();//��ǰ����size����Ϊ������
				T* tmp = new T[n];
				if (tmp != nullptr)
				{
					//������mem
					//memmove(tmp, _start, sizeof(T)*size());//vector<vector<int>>��ǳ����
					for (size_t i = 0; i < sz; i++)
					{
						tmp[i] = _start[i];
					}
					delete[]_start;
				}
				_start = tmp;
				_finish = _start + sz;
				_end_of_storage = _start + n;
			}
		}
		void resize(size_t n ,const vector<T>& val=T())
		{
			if (n > capacity())//����+��ʼ��
			{
				reserve(n);
			}
			else if (n < size())//����
			{
				_finish = _start + n;
			}
			else//���
			{
				while(_finish<_start+n)
				{
					*_finish = val;
					_finish++;
				}
			}
		}

		//vector<string> v;
		//v.push_back("xxxx");//����const,�ַ�����ʽ����ת��������ʱ������ʱ������г���
		void push_back( const T& x)//�������ã���ֵ����������۴�
		{
			if (_finish == _end_of_storage)//�ж��������
			{
				reserve(capacity()== 0 ? 4: 2 * capacity());
			}
			*_finish = x;
			_finish++;
		}
		void pop_back()
		{
			assert(_finish > _start);
			_finish--;
		}
		 
		//������ֵ����ֹ���ֵ�����ʧЧ
		iterator insert(iterator pos, const T& x)//pos���ܸ�����
		{
			assert(pos >= _start&&pos <= _finish);
			if (_finish == _end_of_storage)//�ж��������
			{
				//����֮�����pos��Ұָ�����⣬Ϊ�˷�ֹ������pos
				size_t len = pos - _start;
				reserve(capacity() == 0 ? 4 : 2 * capacity());
				pos = _start + len;
			}
			//pos�Լ�֮�����������Ųһ��
			iterator end = _finish - 1;
			while (end >= pos)
			{
				*(end + 1) = *(end);
				end--;
			}
			//������
			*pos = x;
			_finish++;
			return pos;
		}
		iterator erase(iterator pos)//STL�涨��erase����ɾ�������һ��
		{
			assert(pos<_finish &&pos>=_start);
			iterator begin =  pos + 1;
			while (begin < _finish)
			{
				*(begin-1) = *(begin);
				begin++;
			}
			_finish--;
			//if (size()<capacity()/2)//���Կ�������
			//��ˣ���ò�Ҫ����pos����Ϊ��֪���������Ƿ������ˣ����� 
			return pos;
		}

	private://����ָ��
		iterator _start;
		iterator _finish;
		iterator _end_of_storage;
	};

	void Func(const vector<int>& v)//���ṩconst�汾�ĵ��������ܷ��ʣ�Ȩ�޲��ܷŴ�
	{
		//vector<int>::iterator it = v.begin();//����
		vector<int>::const_iterator it = v.begin();//��ȷ��const�ﲻ���޸�
		for (auto e : v)//��ͨ��������ͨ��������const������const������
		{
			cout << e << " ";
		}
		cout << endl;
	}

	void Test1()
	{
		int a = 1;
		//double& b = a;����
		const double b = a;//��ȷ
		vector<string> v;
		v.push_back("xxxx");
	}
	void Test2()
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(5);
		v.push_back(6);
		v.push_back(2);
		v.push_back(4);
		for (size_t i = 0; i < v.size(); i++)
		{
			cout << v[i] << " ";
		}
		cout << endl;
		vector<int>::iterator it = v.begin();
		while (it != v.end())
		{
			cout << *it << " ";
			it++;
		}
		cout << endl;
		for (auto e : v)//��ͨ��������ͨ��������const������const������
		{
			cout << e << " ";
		}
		cout << endl;
		Func(v);
	}
	void Test3()
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(5);
		v.push_back(6);
		//v.push_back(2);
		v.push_back(4);
		sort(v.begin(), v.end());
		for (auto e : v)
		{
			cout << e << " ";
		}
		cout << endl;
		//��pλ�ò�������֮�󣬲�Ҫ����p����Ϊp����ʧЧ
		auto p = find(v.begin(), v.end(), 4);//find֮�����Ҫ�ж�
		if (p != v.end())
		{
			//�ҵ���
			v.insert(p, 20);
		}
		for (auto e : v)
		{
			cout << e << " ";
		}
		cout << endl;
	}

	void Test4()
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(5);
		v.push_back(6);
		v.push_back(2);
		v.push_back(4);
		//Ҫ��ɾ�����е�ż��
		auto it = v.begin();
		while (it != v.end())
		{
			if (*it % 2 == 0)
				it=v.erase(it);
			else
			    it++; 
		}
		for (auto e : v)
		{
			cout << e << " ";
		}
		cout << endl;
	}
	void Test5()
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(5);
		v.push_back(6);
		v.push_back(2);
		v.push_back(4);
		vector<int> v2(v);
		for (auto e : v2)
		{
			cout << e << " ";
		}
		cout << endl;
		vector<int> v3;
		v3 = v2;
		for (auto e : v3)
		{
			cout << e << " ";
		}
		cout << endl;
		//vector<string> Vstr("def", "abc");
		//for (size_t i = 0; i < Vstr.size(); i++)
		//{
		//	cout << Vstr[i] << endl;
		//}
	}

}