 #define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//class A
//{
//
//public:
//
//	//最好在初始化列表初始化，尽量不在函数体内。
//	//1.哪个对象调用构造函数，初始化列表是它所有成员变量定义的位置
//	//2.不管是否显示在初始化列表写，那么编译器每个变量都会初始化列表定义初始化
//	A()
//		:_a1(1)
//		, _ref(_a1)
//		, _x(3)
//	{
//	}
//
//private:
//	int _a1;//声明
//	int _a2;
//
//	//const int _x;//const变量必须在定义的时候初始化
//	//const int _x==1;//这个不是初始化，而是C++11的缺省值
//	//C++11之前呢
//	//必须给每个成员找一个定义的位置，不然像const这样的成员不好处理
//	//C++规定，const、引用、没有默认构造的自定义类型成员
//	//一个成员只能初始化列表一次
//	const int _x;
//	int& _ref;
//};
//
//int main()
//{
//	A aa;//对象整体的定义，每个成员什么时候定义？
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
////int& add=Add(2,3);//报错
//const int& add = Add(2, 3);//正确
//
//
//int x = 1;
////double& m=x;//报错
//const double& m = x;//正确
//
//namespace AQuene
//{
//	//A实现的代码......
//	struct Node
//	{
//		struct Node* next;
//		int val;
//	};
//}
//namespace BList
//{
//	//B实现的代码......
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
	int* p1 = new int;//new是操作符，也不需要强转
	int* p2 = new int[10];//申请10个int的数组
	delete p1;
	delete[]p2;

	int *p3 = new int(10);//申请一个int，初始化成10
	int* p4 = new int[8]{1, 2, 3};//申请数组，初始化
	delete p3;
	delete[]p4;
	return 0;
}

int main()
{
	//有时，为了提高效率，从内存池申请，会先malloc，再初始化
	//内存池相当于家里的水桶，中间介质，可以更快的用水
	A aa;
	A* pa = (A*)malloc(sizeof(A));
	if (pa == nullptr)
	{
		perror("malloc fail");
		exit(-1);
	}

	//对一块已有的空间初始化——定位new
	new(pa)A;//不给参数
	new(pa)A(1);//给参数
	return 0;
}

template<class Y>
//template<typename Y>//也可以用typename，在这个位置没有区别,不能用struct
void Swap(Y& x, Y& y)
{
	Y tmp = x;
	x = y;
	y = tmp;
}

//也可以定义多个模板参数
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
	//实参传递给形参，自动推演模板类型
	Add(a, b);
	Add(c, d);
	Add(a, (int)c);
	Add((double)b, d);

	//显示实例化
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
		_a = new T[capacity];//不用检查是否失败
		_top = 0;
		_capacity = capacity;
	}

	~Stack()
	{
		delete[] _a;//匹配使用
		_capacity = _top = 0;
	}
private:
	STData* _a;
	size_t _top;
	size_t _capacity;
};

int main()
{
	//Stack叫类名，Stack<int>叫类型
	Stack<int> stA;//类模板只能显示实例化使用
	Stack<double> stA;

	

	return 0;
}

// 如果类模板的声明和定义分离，就要写成如下,要指定类名、类型，还要加上模板参数
template<class T>
Stack<int>::~Stack()
{
	delete[] _a;//匹配使用
	_capacity = _top = 0;
}

//类模板声明和定义都放在同一个文件中，如果分成两个文件（比如.h和.cpp），会出现链接错误