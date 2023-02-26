#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<iostream>
#include<vector>
#include<deque>
#include<algorithm>
#include<assert.h>
#include<functional>
using namespace std;

namespace my_priority_queue
{
	//大堆     那么如何大小堆切换？ ——仿函数
	//Compare进行比较的仿函数，less大堆   greater小堆
	template<class T,class Contioner=vector<T>,class Compare=std::less<T>>
	class priority_queue
	{
	public:
		priority_queue()//写了其中一种构造，其他的构造就要写
		{

		}

		template<class InputIterator>
		priority_queue(InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				_con.push_back(*first);
				first++;
			}
			for (int i = (_con.size() - 1 - 1) / 2; i >= 0; i--)
			{
				Adjustdown(i); 
			}
		}


		void Adjustup(size_t child)
		{
			Compare com;
			size_t father = (child - 1)/2;
			while (child>0)
			{
				//if (_con[father]< _con[child])
				if (com(_con[father] , _con[child]))
				{
					std::swap(_con[child], _con[father]);
					child = father;
					father = (child - 1) / 2;
				}
				else
				{
					break;
				}
			}
		}
		void Adjustdown(size_t father)
		{
			Compare com;
			size_t child = father * 2 + 1;
			while (child < _con.size())
			{
				//if (child + 1 < _con.size() && con[child]< _con[child + 1])
				if (child + 1 < _con.size() && com(_con[child] , _con[child + 1]))
					child += 1;
				//if (_con[father]< _con[child])
				if (com(_con[father],_con[child]))
				{
				std::swap(_con[child], _con[father]);
					father = child;
					child = father * 2 + 1;
				}
				else
				{
					break;
				}
			}

		}
		void push(const T& val)
		{
			_con.push_back(val);
			//向上调整算法
			Adjustup(_con.size()-1);
		}

		void pop()
		{
		std::swap(_con[0], _con[_con.size() - 1]);
			_con.pop_back();
			//向下调整算法
			Adjustdown(0);
		}
		const T& top()const
		{
			return _con[0];
		}
		bool empty()const
		{
			return _con.empty();
		}
		size_t size()const
		{
			return _con.size();
		}
	private:
		Contioner _con;
	};
}