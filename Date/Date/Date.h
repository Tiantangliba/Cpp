#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<assert.h>
using namespace std;


class Date
{
	friend ostream& operator<<(ostream& out, const Date& d);//友元
	friend istream& operator>>(istream& in, Date& d);

public:
	//Date()//构造
	//Date(int year, int month, int day)//构造的重载
	Date(int year = 1, int month = 1, int day = 1);//利用缺省值的构造
	Date(const Date& d);//拷贝构造，一般会加const修饰
	void Print()const;//函数会传this指针
	int GetMonthDday(int year, int month)const;
	Date& operator+=(int day);//+=
	Date operator+(int day)const;//+  用+=来实现+更简练；用+来实现+=会有消耗

	Date& operator-=(int day);//-=
	Date operator-(int day)const;//-

	int operator-(const Date& d);//date1-date2

	Date& operator++();//++date;
	Date operator++(int);//date++ 规定：参数int仅仅是为了占位，与前置重载区分

	Date& operator--();//前置--  转换成了d.operator--()
	Date operator--(int);//后置--  转换成了d.operator--(0)

	////d7==d8
	//bool operator==(const Date& x1, const Date& x2)//第一个成员是左操作数，第二个成员是右操作数
	//写这种会报错，因为还传了this指针
	//d7==d8  转换成d7.operator ==(d8)
	bool operator==(const Date& x)const;//第一个成员是左操作数，第二个成员是右操作数
	bool operator<(const Date& x)const;
	bool operator<=(const Date& x)const;
	bool operator>(const Date& x)const;
	bool operator>=(const Date& x)const;
	bool operator!=(const Date& x)const;

	//函数参数可以不加引用,但是会去调用拷贝构造，造成浪费，所以加上
	Date&  operator=(const Date& x);//赋值运算符重载

	//void operator<<(ostream& out);//d1.operator<<(cout)



private:
	int _year;
	int _month;
	int _day;
};

//ostream& operator<<(ostream& out, const Date& d);
//istream& operator>>(istream& in, Date& d);
inline ostream& operator<<(ostream& out, const Date& d)
{
	out << d._year << "年" << d._month << "月" << d._day << "日" << endl;
	return out;
}
inline istream& operator>>(istream& in, Date& d)
{
	in >> d._year >> d._month >> d._day;
	return in;
}
