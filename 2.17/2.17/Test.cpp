 #define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
using namespace std;

void Func(const string& s)
{
	string::const_iterator it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;
}
int main()
{
	string s1; // 构造空的string类对象s1
	string s2("hello bit"); // 用C格式字符串构造string类对象s2
	string s3(s2); // 拷贝构造s3
	string s4 = "hello bit";//隐士类型转换，优化成了拷贝构造，不想发生加explict
	string s5(s3, 6, 3);
	string s8(s3, 6, 15);//没15个字符，有多少取多少
	string s9(s3, 6);//缺省值，npos
	string s6("hello bit",5);//用常量字符串的前n个构造
	string s7(10, 'x');//

	for (size_t i = 0; i < s2.size(); i++)
	{
		s2[i]++;
	}
	cout << s2 << endl;

	s2.size();
	s2.length();//值与size一样，平时用size
	s2.capacity();//容量,实际+1；
	s2.push_back(' ');//一个一个字符的插
	s2.append("hahaha");//插字符串
	s2 += "233";
	s2 += 'h';
	//观察string的扩容情况，跟平台有关

	//如何减少扩容
	string s10;
	s10.reserve(100);//预开空间，如果知道提前要开的空间，减少扩容，就可以提高效率
	
	string s11;
	s11.resize(100);//扩容+初始化，默认\0
	s11.resize(100, 'x');
	s11.resize(5);//比size小，删除数据，保留前5个,capacity不会变	

	//三种遍历方式
	//迭代器访问——想象迭代器是指针，迭代器是左闭右开
	//普通迭代器，可以读和写
	string s12("hello world");
	string::iterator it = s12.begin();
	//auto it=s12.begin();
	while (it != s12.end())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;
	//范围for,实际上范围for的底层是迭代器
	for (auto ch : s12)
	{
		cout << ch << " ";
	}
	//下标访问，略
	//方向迭代器——倒着遍历,左闭右开
	string::reverse_iterator rit = s12.rbegin();
	while (rit != s12.rend())
	{
		cout << *rit << " ";
		rit++;
	}

	//const迭代器,不允许写，只能读
	Func(s12);
	//const反向迭代器
	
	//s12[100];//operator[]越界会报错，里面用的是assert
	//s12.at(100)//at越界会抛异常

	//不推荐经常用insert和erase和replace，底层实现是开辟新空间
	string s13("world");
	s13.insert(0, "hello");
	s13.insert(5,1,' ');
	s13.insert(4, " ");
	s13.insert(s13.begin() + 5, ' ');//迭代器插入

	string s14("hello world");
	s14.erase(5,1);
	s14.erase(s14.begin() + 5);//迭代器删除第5个字符
	s14.erase(5);

	string s15("hello world");
	s15.replace(5, 1,"%%d");

	string s16("hello world i love you");//要求替换空格为"%20"
	size_t num = 0;
	for (auto ch : s16)
	{
		if (ch == ' ')
		{
			num++;
		}
	}
	s16.reserve(s16.size()+ 2 * num);//提前开空间，避免replace扩容
	size_t pos = s16.find(' ');
	while (pos != string::npos)
	{
		s16.replace(pos, 1, "%20");
		pos = s16.find(' ', pos + 3);
	}

	string s17("hello world i love you");//要求替换空格为"%20"
	string newStr;
	size_t num = 0;
	for (auto ch : s17)
	{
		if (ch == ' ')
		{
			num++;
		}
	}
	newStr.reserve(s17.size() + 2 * num);//提前开空间，避免replace扩容
	for (auto ch : s17)
	{
		if (ch != ' ')
			newStr += ch;
		else
			newStr += "%20";
	}
	s17 = newStr;

	//string里的swap和std里的swap
	//string的swap更高效
	string s18("xxx");
	s17.swap(s18);
	swap(s17, s18);


	string s19("hello world");
	cout << s19 << endl;//作为自定义类型，调的重载的流插入，按size打印
	cout << s19.c_str() << endl;//返回const char*指针，按字符串打印，遇\0终止
	//提供c_str的目的是为了兼容c，比如fopen打开文件，要用c
	s19 += '\0';
	s19 += '\0';
	s19 += "xxx";
	//此时打印结果不一样
	cout << s19 << endl;//作为自定义类型，调的重载的流插入
	cout << s19.c_str() << endl;//返回char*指针，按字符串打印

	string s20("string.cpp.tar.zip");//获取后缀
	size_t pos = s20.rfind('.');
	if (pos != string::npos)
	{
		string suffix = s10.substr(pos);
		//string suffix = s10.substr(pos, s20.size() - pos);
	}

	//find_first_of 
	//find_last_of

	return 0;
}

int main()
{
	string s;
	//cin>>s;不能用cin，它默认用空格和换行
	getline(cin, s);
	size_t pos = s.rfind(' ');
	if (pos != string::npos)
	{
		cout << s.size() - pos - 1 << endl;;
	}
	else {
		cout << s.size() << endl;
	}
	return 0;
}




