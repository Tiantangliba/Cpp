#include"Date.h"


//Date::Date()//����
//{
//	_year = 1;
//	_month = 1;
//	_day = 1;
//}
//Date::Date(int year, int month, int day)//���������
//{
//	_year = year;
//	_month = month;
//	_day = day;
//}	
Date::Date(int year, int month, int day)//����ȱʡֵ�Ĺ���
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
		cout << "���ڷǷ�" << endl;
	}
}

Date::Date(const Date& d)//�������죬һ����const����
{
	_year = d._year;
	_month = d._month;
	_day = d._day;
}
void Date::Print()const//�����ᴫthisָ��
{
	cout << _year << "��" << _month << "��" << _day << "��" << endl;
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
Date& Date::operator+=(int day)//+=����ֵҪ�����ã���Ϊ֧��d1=d3+=100��
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
Date Date::operator+(int day)const//+ ����������tmp���ڣ����������÷���
{
	//Date tmp(*this);
	Date tmp = *this;//�����м����������ԭ����d2ֵҲ����
	//���ܼ�static����̬����ֻ��ʼ��һ�Σ��´λ�����

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
	tmp += day;//���ü���
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
		++min;//ʵ����ǰ�úͺ��ã���ʱ����Ҫ��ǰ����
		++n;
	}
	return n*flag;
}

Date& Date::operator++()//++date
{
	*this += 1;
	return *this;
}
Date Date::operator++(int)//date++ ����int������Ϊ��ռλ����ǰ����������
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
Date Date::operator--(int)//date-- ����int������Ϊ��ռλ����ǰ����������
{
	Date tmp(*this);
	*this -= 1;
	return tmp;
}


////d7==d8
//bool Date::operator==(const Date& x1, const Date& x2)//��һ����Ա������������ڶ�����Ա���Ҳ�����
//�ᱨ����Ϊ������thisָ��
//{
//	return x1._year == x2._year
//		&& x1._month == x2._month
//		&& x1._day == x2._day;
//}

//d7==d8  ת����d7.operator ==(d8)
bool Date::operator==(const Date& x)const//��һ����Ա������������ڶ�����Ա���Ҳ�����
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

//�����������Բ�������,���ǻ�ȥ���ÿ������죬����˷ѣ����Լ���
Date&  Date::operator=(const Date& x)//��ֵ���������
{
	if (this != &x)//�������if�����Է�ֹ�����Լ����Լ��ĸ�ֵ������d1=d1��
	{
		_year = x._year;
		_month = x._month;
		_day = x._day;
	}

	return *this;//�������return���Ϳ���������ֵ��
	//����������*this����,����ֵ��������
}

//void Date:: operator<<(ostream& out)//���ǻᱨ����Ϊ���Ҳ��������ܵ�λ
//{
//	out << _year << "��" << _month << "��" << _day << "��" << endl;
//}

//Ϊ�������������룬��������ֵ��Ϊostream&
//ostream& operator<<(ostream& out, const Date& d)
//{
//	out << d._year << "��" << d._month << "��" << d._day << "��" << endl;
//	return out;
//}
//istream& operator>>(istream& in, Date& d)
//{
//	in>> d._year >> d._month >> d._day;
//	return in;
//}

