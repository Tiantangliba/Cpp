#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<iostream>
#include<vector>
#include<deque>
#include<algorithm>
#include<assert.h>
#include<functional>
using namespace std;

namespace my_stack
{
	template<class T, class Contioner = deque<T>>
	class stack
	{
	public:
		void push(const T& val)
		{
			_con.push_back(val);
		}
		void pop()
		{
			_con.pop_back();
		}
		T& top()
		{
			return _con.back();
		}
		const T& top()const
		{
			return _con.back();
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
		//vector<T> _con;
		Contioner _con;
	};
}