#include"Date.h"

void Test2()
{
	Date d1(2023, 2, 14);
	//cout << d1;Ϊʲôcout֧���������ͣ�
	//�Զ���������Ҫ�Լ�д������

	int i = 1;
	double d = 2;
	cout << i;//cout.operator<<(i)//int 
	//"<<"�����룬�����������������+�������أ��Զ�ʶ�����ͣ�
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

	Date d4(d1);//��������
	Date d5 = d1;//��������
	d1 = d3;//��ֵ��������أ�ת����d1.operator(d3)
	d1 = d2 = d3;//������ֵ
	d1 = d1;//�Լ����Լ���ֵ
	d1 = d3 += 100;//�ӵ��ٸ�ֵ����˼ӵ�ҲҪ�з���ֵ

	//ʵ��һ����������ȡ�������Ժ������
	Date d6=d1+100;
	d1.Print();
	d2.Print();
	d3.Print();
	d6.Print();

	Date d7(2023, 2, 10);
	Date d8(2023, 4, 5);
	////operator==(d7, d8);//��������
	//d7 == d8;//ת����ȥ�������operator==(d7, d8)

	////cout << d7 == d8 << endl;Ҫ�����ţ�����������ȼ�
	//cout << (d7 == d8) << endl;


	d7.operator ==(d8);
	cout << (d7== d8) << endl;//ת����ȥ����d7.operator ==(d8)
	return 0;
}