#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<assert.h>
using namespace std;


class Date
{
	friend ostream& operator<<(ostream& out, const Date& d);//��Ԫ
	friend istream& operator>>(istream& in, Date& d);

public:
	//Date()//����
	//Date(int year, int month, int day)//���������
	Date(int year = 1, int month = 1, int day = 1);//����ȱʡֵ�Ĺ���
	Date(const Date& d);//�������죬һ����const����
	void Print()const;//�����ᴫthisָ��
	int GetMonthDday(int year, int month)const;
	Date& operator+=(int day);//+=
	Date operator+(int day)const;//+  ��+=��ʵ��+����������+��ʵ��+=��������

	Date& operator-=(int day);//-=
	Date operator-(int day)const;//-

	int operator-(const Date& d);//date1-date2

	Date& operator++();//++date;
	Date operator++(int);//date++ �涨������int������Ϊ��ռλ����ǰ����������

	Date& operator--();//ǰ��--  ת������d.operator--()
	Date operator--(int);//����--  ת������d.operator--(0)

	////d7==d8
	//bool operator==(const Date& x1, const Date& x2)//��һ����Ա������������ڶ�����Ա���Ҳ�����
	//д���ֻᱨ����Ϊ������thisָ��
	//d7==d8  ת����d7.operator ==(d8)
	bool operator==(const Date& x)const;//��һ����Ա������������ڶ�����Ա���Ҳ�����
	bool operator<(const Date& x)const;
	bool operator<=(const Date& x)const;
	bool operator>(const Date& x)const;
	bool operator>=(const Date& x)const;
	bool operator!=(const Date& x)const;

	//�����������Բ�������,���ǻ�ȥ���ÿ������죬����˷ѣ����Լ���
	Date&  operator=(const Date& x);//��ֵ���������

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
	out << d._year << "��" << d._month << "��" << d._day << "��" << endl;
	return out;
}
inline istream& operator>>(istream& in, Date& d)
{
	in >> d._year >> d._month >> d._day;
	return in;
}
