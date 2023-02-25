#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<iostream>
#include<vector>
#include<deque>
#include<algorithm>
#include<assert.h>
#include<functional>
using namespace std;

namespace my_queue
{
	template<class T ,class Contioner=deque>
	class queue
	{
	public:
		void push(const T& val)
		{
			_con.push_back(val);
		}
		void pop()
		{
			_con.pop_front();
		}
		T& back()
		{
			return _con.back();
		}
		T& front()
		{
			return _con.front();
		}
		const T& back()const
		{
			return _con.back();
		}
		const T& front()const
		{
			return _con.front();
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
		//list<T> _con;
		Contioner _con;
	};
}
