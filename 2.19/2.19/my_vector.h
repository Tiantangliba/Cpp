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

		vector(const vector<T>& v)//拷贝构造
		{
			_start = new T[v.size()];
			for (size_t i = 0; i < v.size(); i++)
			{
				//不能用memcpy，vector<vector<int>>是浅拷贝
				_start[i] = v._start[i];
			}
			_finish = _start + v.size();
			_end_of_storage = _start + v.capacity();
		}


		//vector(const vector<T>& v)//拷贝构造
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
		template<class InputIterator>//为什么要单独定义模板？
		vector(InputIterator first, InputIterator last)//迭代器区间构造
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
		//vector(const vector<T>& v)//拷贝构造,必须加引用，否则无限递归
		//		:_start(nullptr)
		//		, _finish(nullptr)
		//		, _end_of_storage(nullptr)
		//{
		//	vector<T> tmp(v.begin(),v.end());
		//	//vector tmp(v);//错误
		//	swap(tmp);
		//}
		vector<T>& operator=(vector<T> v)//赋值重载,简洁舒服
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
		size_t capacity()const//容量
		{
			return _end_of_storage - _start;
		}
		size_t size()const//个数
		{
			return _finish - _start;
		}
		void reserve(size_t n)//reserve不改变size
		{
			if (n > capacity())
			{
				size_t sz = size();//提前保留size，因为后面会变
				T* tmp = new T[n];
				if (tmp != nullptr)
				{
					//不能用mem
					//memmove(tmp, _start, sizeof(T)*size());//vector<vector<int>>是浅拷贝
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
			if (n > capacity())//扩容+初始化
			{
				reserve(n);
			}
			else if (n < size())//缩短
			{
				_finish = _start + n;
			}
			else//填充
			{
				while(_finish<_start+n)
				{
					*_finish = val;
					_finish++;
				}
			}
		}

		//vector<string> v;
		//v.push_back("xxxx");//不加const,字符串隐式类型转换产生临时对象，临时对象具有常性
		void push_back( const T& x)//不加引用，传值会深拷贝，代价大
		{
			if (_finish == _end_of_storage)//判断扩容与否
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
		 
		//给返回值，防止出现迭代器失效
		iterator insert(iterator pos, const T& x)//pos不能给引用
		{
			assert(pos >= _start&&pos <= _finish);
			if (_finish == _end_of_storage)//判断扩容与否
			{
				//扩容之后出现pos的野指针问题，为了防止，更新pos
				size_t len = pos - _start;
				reserve(capacity() == 0 ? 4 : 2 * capacity());
				pos = _start + len;
			}
			//pos以及之后的数据往后挪一个
			iterator end = _finish - 1;
			while (end >= pos)
			{
				*(end + 1) = *(end);
				end--;
			}
			//放数据
			*pos = x;
			_finish++;
			return pos;
		}
		iterator erase(iterator pos)//STL规定，erase返回删除后的下一个
		{
			assert(pos<_finish &&pos>=_start);
			iterator begin =  pos + 1;
			while (begin < _finish)
			{
				*(begin-1) = *(begin);
				begin++;
			}
			_finish--;
			//if (size()<capacity()/2)//可以考虑缩容
			//因此，最好不要访问pos，因为不知道库里面是否缩容了，而且 
			return pos;
		}

	private://都是指针
		iterator _start;
		iterator _finish;
		iterator _end_of_storage;
	};

	void Func(const vector<int>& v)//不提供const版本的迭代器不能访问，权限不能放大
	{
		//vector<int>::iterator it = v.begin();//错误
		vector<int>::const_iterator it = v.begin();//正确，const里不能修改
		for (auto e : v)//普通对象走普通迭代器，const对象走const迭代器
		{
			cout << e << " ";
		}
		cout << endl;
	}

	void Test1()
	{
		int a = 1;
		//double& b = a;报错
		const double b = a;//正确
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
		for (auto e : v)//普通对象走普通迭代器，const对象走const迭代器
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
		//在p位置插入数据之后，不要访问p，因为p可能失效
		auto p = find(v.begin(), v.end(), 4);//find之后必须要判断
		if (p != v.end())
		{
			//找到了
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
		//要求删除所有的偶数
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