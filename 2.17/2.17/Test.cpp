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
	string s1; // ����յ�string�����s1
	string s2("hello bit"); // ��C��ʽ�ַ�������string�����s2
	string s3(s2); // ��������s3
	string s4 = "hello bit";//��ʿ����ת�����Ż����˿������죬���뷢����explict
	string s5(s3, 6, 3);
	string s8(s3, 6, 15);//û15���ַ����ж���ȡ����
	string s9(s3, 6);//ȱʡֵ��npos
	string s6("hello bit",5);//�ó����ַ�����ǰn������
	string s7(10, 'x');//

	for (size_t i = 0; i < s2.size(); i++)
	{
		s2[i]++;
	}
	cout << s2 << endl;

	s2.size();
	s2.length();//ֵ��sizeһ����ƽʱ��size
	s2.capacity();//����,ʵ��+1��
	s2.push_back(' ');//һ��һ���ַ��Ĳ�
	s2.append("hahaha");//���ַ���
	s2 += "233";
	s2 += 'h';
	//�۲�string�������������ƽ̨�й�

	//��μ�������
	string s10;
	s10.reserve(100);//Ԥ���ռ䣬���֪����ǰҪ���Ŀռ䣬�������ݣ��Ϳ������Ч��
	
	string s11;
	s11.resize(100);//����+��ʼ����Ĭ��\0
	s11.resize(100, 'x');
	s11.resize(5);//��sizeС��ɾ�����ݣ�����ǰ5��,capacity�����	

	//���ֱ�����ʽ
	//���������ʡ��������������ָ�룬������������ҿ�
	//��ͨ�����������Զ���д
	string s12("hello world");
	string::iterator it = s12.begin();
	//auto it=s12.begin();
	while (it != s12.end())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;
	//��Χfor,ʵ���Ϸ�Χfor�ĵײ��ǵ�����
	for (auto ch : s12)
	{
		cout << ch << " ";
	}
	//�±���ʣ���
	//����������������ű���,����ҿ�
	string::reverse_iterator rit = s12.rbegin();
	while (rit != s12.rend())
	{
		cout << *rit << " ";
		rit++;
	}

	//const������,������д��ֻ�ܶ�
	Func(s12);
	//const���������
	
	//s12[100];//operator[]Խ��ᱨ�������õ���assert
	//s12.at(100)//atԽ������쳣

	//���Ƽ�������insert��erase��replace���ײ�ʵ���ǿ����¿ռ�
	string s13("world");
	s13.insert(0, "hello");
	s13.insert(5,1,' ');
	s13.insert(4, " ");
	s13.insert(s13.begin() + 5, ' ');//����������

	string s14("hello world");
	s14.erase(5,1);
	s14.erase(s14.begin() + 5);//������ɾ����5���ַ�
	s14.erase(5);

	string s15("hello world");
	s15.replace(5, 1,"%%d");

	string s16("hello world i love you");//Ҫ���滻�ո�Ϊ"%20"
	size_t num = 0;
	for (auto ch : s16)
	{
		if (ch == ' ')
		{
			num++;
		}
	}
	s16.reserve(s16.size()+ 2 * num);//��ǰ���ռ䣬����replace����
	size_t pos = s16.find(' ');
	while (pos != string::npos)
	{
		s16.replace(pos, 1, "%20");
		pos = s16.find(' ', pos + 3);
	}

	string s17("hello world i love you");//Ҫ���滻�ո�Ϊ"%20"
	string newStr;
	size_t num = 0;
	for (auto ch : s17)
	{
		if (ch == ' ')
		{
			num++;
		}
	}
	newStr.reserve(s17.size() + 2 * num);//��ǰ���ռ䣬����replace����
	for (auto ch : s17)
	{
		if (ch != ' ')
			newStr += ch;
		else
			newStr += "%20";
	}
	s17 = newStr;

	//string���swap��std���swap
	//string��swap����Ч
	string s18("xxx");
	s17.swap(s18);
	swap(s17, s18);


	string s19("hello world");
	cout << s19 << endl;//��Ϊ�Զ������ͣ��������ص������룬��size��ӡ
	cout << s19.c_str() << endl;//����const char*ָ�룬���ַ�����ӡ����\0��ֹ
	//�ṩc_str��Ŀ����Ϊ�˼���c������fopen���ļ���Ҫ��c
	s19 += '\0';
	s19 += '\0';
	s19 += "xxx";
	//��ʱ��ӡ�����һ��
	cout << s19 << endl;//��Ϊ�Զ������ͣ��������ص�������
	cout << s19.c_str() << endl;//����char*ָ�룬���ַ�����ӡ

	string s20("string.cpp.tar.zip");//��ȡ��׺
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
	//cin>>s;������cin����Ĭ���ÿո�ͻ���
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




