#include"Date.h"

void Test2()
{
	Date d1(2023, 2, 14);
	//cout << d1;为什么cout支持内置类型？
	//自定义类型需要自己写个重载

	int i = 1;
	double d = 2;
	cout << i;//cout.operator<<(i)//int 
	//"<<"流插入，本质是运算符的重载+函数重载（自动识别类型）
	cout << d;//cout.operator<<(d)//double

	//d1.operator<<(cout);
	//d1<<cout;

	operator<<(cout, d1);
	cout << d1;
}

void Test3()
{
	Date d1;
	//cin >> d1;

}

int main()
{
	Date d1;
	Date d2(2023, 2, 9);
	Date d3(2023, 2);

	Date d4(d1);//拷贝构造
	Date d5 = d1;//拷贝构造
	d1 = d3;//赋值运算符重载，转换成d1.operator(d3)
	d1 = d2 = d3;//连续赋值
	d1 = d1;//自己对自己赋值
	d1 = d3 += 100;//加等再赋值，因此加等也要有返回值

	//实现一个函数，获取多少天以后得日期
	Date d6=d1+100;
	d1.Print();
	d2.Print();
	d3.Print();
	d6.Print();

	Date d7(2023, 2, 10);
	Date d8(2023, 4, 5);
	////operator==(d7, d8);//不用这种
	//d7 == d8;//转换成去调用这个operator==(d7, d8)

	////cout << d7 == d8 << endl;要加括号，运算符的优先级
	//cout << (d7 == d8) << endl;


	d7.operator ==(d8);
	cout << (d7== d8) << endl;//转换成去调用d7.operator ==(d8)
	return 0;
}