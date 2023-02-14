#include"Date.h"


//Date::Date()//构造
//{
//	_year = 1;
//	_month = 1;
//	_day = 1;
//}
//Date::Date(int year, int month, int day)//构造的重载
//{
//	_year = year;
//	_month = month;
//	_day = day;
//}	
Date::Date(int year, int month, int day)//利用缺省值的构造
{
	if (month > 0 && month<13
		&& (day>0 && day <= GetMonthDday(year,month)))
	{
		_year = year;
		_month = month;
		_day = day;
	}
	else
	{
		cout << "日期非法" << endl;
	}
}

Date::Date(const Date& d)//拷贝构造，一般会加const修饰
{
	_year = d._year;
	_month = d._month;
	_day = d._day;
}
void Date::Print()const//函数会传this指针
{
	cout << _year << "年" << _month << "月" << _day << "日" << endl;
}

int Date::GetMonthDday(int year, int month)const
{
	assert(month > 0 && month < 13);
	int monthArr[] = { 0, 13, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
	{
		return 29;
	}
	return monthArr[month];
}
Date& Date::operator+=(int day)//+=返回值要加引用，因为支持d1=d3+=100；
{
	if (day<0)
	{
		*this -= -day;
		return *this;
	}
	_day += day;
	while (_day > GetMonthDday(_year, _month))
	{
		_day -= GetMonthDday(_year, _month);
		_month++;
		if (_month == 13)
		{
			_year++;
			_month = 1;
		}
	}
	return *this;
}
Date Date::operator+(int day)const//+ 出了作用域，tmp不在，不能用引用返回
{
	//Date tmp(*this);
	Date tmp = *this;//利用中间变量，否则原来的d2值也变了
	//不能加static，静态变量只初始化一次，下次会跳过

	/*tmp._day += x;
	while (tmp._day > GetMonthDday(tmp._year, tmp._month))
	{
		tmp._day -= GetMonthDday(tmp._year, tmp._month);
		tmp._month++;
		if (tmp._month == 13)
		{
			tmp._year++;
			tmp._month = 1;
		}
	
	}*/
	tmp += day;//复用即可
	return tmp;
}


Date& Date::operator-=(int day)//-=
{
	if (day < 0)
	{
		*this += -day;
		return *this;
	}
		_day -= day;
	while (_day <= 0)
	{
		_month--;
		if (_month == 0)
		{
			_year--;
			_month = 12;
		}
		_day += GetMonthDday(_year, _month);
	}
	return *this;
}

Date Date::operator-(int day)const//-
{
	Date tmp(*this);
	tmp -= day;
	return tmp;
}

int Date::operator-(const Date& d)//date1-date2
{
	Date max = *this;
	Date min = d;
	int flag = 1;
	if (*this < d)
	{
		max = d;
		min = *this;
		flag = -1;
	}
	int n = 0;
	while (min != max)
	{
		++min;//实现了前置和后置，此时必须要用前置了
		++n;
	}
	return n*flag;
}

Date& Date::operator++()//++date
{
	*this += 1;
	return *this;
}
Date Date::operator++(int)//date++ 参数int仅仅是为了占位，跟前置重载区分
{
	Date tmp(*this);
	*this += 1;
	return tmp;
}

Date& Date::operator--()//--date
{
	*this -= 1;
	return *this;
}
Date Date::operator--(int)//date-- 参数int仅仅是为了占位，跟前置重载区分
{
	Date tmp(*this);
	*this -= 1;
	return tmp;
}


////d7==d8
//bool Date::operator==(const Date& x1, const Date& x2)//第一个成员是左操作数，第二个成员是右操作数
//会报错，因为还传了this指针
//{
//	return x1._year == x2._year
//		&& x1._month == x2._month
//		&& x1._day == x2._day;
//}

//d7==d8  转换成d7.operator ==(d8)
bool Date::operator==(const Date& x)const//第一个成员是左操作数，第二个成员是右操作数
{
	return _year == x._year
		&& _month == x._month
		&& _day == x._day;
}

bool Date::operator<(const Date& x)const
{
	if (_year < x._year)
		return true;
	else if (_year == x._year&&_month < x._month)
		return true;
	else if (_year == x._year&&_month == x._month&&_day < x._day)
		return true;
	else
		return false;
}

bool Date::operator<=(const Date& x)const
{
	return *this<x || *this == x;
}

bool Date::operator>(const Date& x)const
{
	return !(*this <= x);
}

bool Date::operator>=(const Date& x)const
{
	return !(*this < x);
}

bool Date::operator!=(const Date& x)const
{
	return !(*this == x);
}

//函数参数可以不加引用,但是会去调用拷贝构造，造成浪费，所以加上
Date&  Date::operator=(const Date& x)//赋值运算符重载
{
	if (this != &x)//加上这个if，可以防止出现自己对自己的赋值，例如d1=d1；
	{
		_year = x._year;
		_month = x._month;
		_day = x._day;
	}

	return *this;//加上这个return，就可以连续赋值；
	//出了作用域，*this还在,返回值加上引用
}

//void Date:: operator<<(ostream& out)//但是会报错，因为左右操作数不能调位
//{
//	out << _year << "年" << _month << "月" << _day << "日" << endl;
//}

//为了连续的流插入，函数返回值改为ostream&
//ostream& operator<<(ostream& out, const Date& d)
//{
//	out << d._year << "年" << d._month << "月" << d._day << "日" << endl;
//	return out;
//}
//istream& operator>>(istream& in, Date& d)
//{
//	in>> d._year >> d._month >> d._day;
//	return in;
//}

