 #define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//class A
//{
//
//public:
//
//	//����ڳ�ʼ���б��ʼ�����������ں������ڡ�
//	//1.�ĸ�������ù��캯������ʼ���б��������г�Ա���������λ��
//	//2.�����Ƿ���ʾ�ڳ�ʼ���б�д����ô������ÿ�����������ʼ���б����ʼ��
//	A()
//		:_a1(1)
//		, _ref(_a1)
//		, _x(3)
//	{
//	}
//
//private:
//	int _a1;//����
//	int _a2;
//
//	//const int _x;//const���������ڶ����ʱ���ʼ��
//	//const int _x==1;//������ǳ�ʼ��������C++11��ȱʡֵ
//	//C++11֮ǰ��
//	//�����ÿ����Ա��һ�������λ�ã���Ȼ��const�����ĳ�Ա���ô���
//	//C++�涨��const�����á�û��Ĭ�Ϲ�����Զ������ͳ�Ա
//	//һ����Աֻ�ܳ�ʼ���б�һ��
//	const int _x;
//	int& _ref;
//};
//
//int main()
//{
//	A aa;//��������Ķ��壬ÿ����Աʲôʱ���壿
//	return 0;
//}
//int Add(int x,int y)
//{
//
//}
//
//const int c = 1;
//int d = c;
//
//int a = 10;
////int& add=Add(2,3);//����
//const int& add = Add(2, 3);//��ȷ
//
//
//int x = 1;
////double& m=x;//����
//const double& m = x;//��ȷ
//
//namespace AQuene
//{
//	//Aʵ�ֵĴ���......
//	struct Node
//	{
//		struct Node* next;
//		int val;
//	};
//}
//namespace BList
//{
//	//Bʵ�ֵĴ���......
//	struct Node
//	{
//		struct Node* next;
//		int val;
//	};
//}
//
//int main()
//{
//	 AQuene::Node;
//	 BList::Node;
//	return 0;
//}
class A
{
public:
	A(int a = 0)
		:_a(a)
	{

	}
private:
	int _a;
};

int main()
{
	int* p1 = new int;//new�ǲ�������Ҳ����Ҫǿת
	int* p2 = new int[10];//����10��int������
	delete p1;
	delete[]p2;

	int *p3 = new int(10);//����һ��int����ʼ����10
	int* p4 = new int[8]{1, 2, 3};//�������飬��ʼ��
	delete p3;
	delete[]p4;
	return 0;
}

int main()
{
	//��ʱ��Ϊ�����Ч�ʣ����ڴ�����룬����malloc���ٳ�ʼ��
	//�ڴ���൱�ڼ����ˮͰ���м���ʣ����Ը������ˮ
	A aa;
	A* pa = (A*)malloc(sizeof(A));
	if (pa == nullptr)
	{
		perror("malloc fail");
		exit(-1);
	}

	//��һ�����еĿռ��ʼ��������λnew
	new(pa)A;//��������
	new(pa)A(1);//������
	return 0;
}

template<class Y>
//template<typename Y>//Ҳ������typename�������λ��û������,������struct
void Swap(Y& x, Y& y)
{
	Y tmp = x;
	x = y;
	y = tmp;
}

//Ҳ���Զ�����ģ�����
template<class Y,class X>
void Func()
{
}

int main()
{
	int a = 1, b = 2;
	Swap(a, b);

	double c = 1.0, d = 2.0;
	Swap(c, d);
	return 0;
}

template<class T>
T Add(const T& left, const T& right)
{
	return left + right;
}

int main()
{
	int a = 1, b = 2;
	double c = 1.2, d = 2.2;
	//ʵ�δ��ݸ��βΣ��Զ�����ģ������
	Add(a, b);
	Add(c, d);
	Add(a, (int)c);
	Add((double)b, d);

	//��ʾʵ����
	Add<int>(a, c);
	Add<double>(b, d);

	return 0;
}


template<class T>
class Stack
{
public:
	Stack(int capacity = 4)
	{
		_a = new T[capacity];//���ü���Ƿ�ʧ��
		_top = 0;
		_capacity = capacity;
	}

	~Stack()
	{
		delete[] _a;//ƥ��ʹ��
		_capacity = _top = 0;
	}
private:
	STData* _a;
	size_t _top;
	size_t _capacity;
};

int main()
{
	//Stack��������Stack<int>������
	Stack<int> stA;//��ģ��ֻ����ʾʵ����ʹ��
	Stack<double> stA;

	

	return 0;
}

// �����ģ��������Ͷ�����룬��Ҫд������,Ҫָ�����������ͣ���Ҫ����ģ�����
template<class T>
Stack<int>::~Stack()
{
	delete[] _a;//ƥ��ʹ��
	_capacity = _top = 0;
}

//��ģ�������Ͷ��嶼����ͬһ���ļ��У�����ֳ������ļ�������.h��.cpp������������Ӵ���