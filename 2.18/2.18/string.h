#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<assert.h>
using namespace std;

namespace my_string//��ֹ�ͱ�׼��ĳ�ͻ
{
	class string
	{
	public:
		typedef char* iterator;
		typedef const char* const_iterator;

		iterator begin()
		{
			return _str;
		}
		iterator end()
		{
			return _str+_size;
		}
		const iterator begin()const
		{
			return _str;
		}
		const iterator end()const
		{
			return _str + _size;
		}
		//string(const char* str)//����
		//	:_str(new char[strlen(str)+1])
		//	, _size(strlen(str))
		//	, _capacity(strlen(str))
		//{ 
		//	strcpy(_str, str);
		//}
		//string()//��������
		//	:_str(new char[1])//��һ������Ϊ�����������أ�Ҳ���ܸ�nullptr
		//	, _size(0)
		//	, _capacity(0)
		//{
		//	_str[0]='\0';
		//}
		//string(const char* str="\0")//���߸�����ȱʡֵ
		//string(const char* str = "")//���߸�����ȱʡֵ
		//	:_str(new char[strlen(str) + 1])
		//	, _size(strlen(str))
		//	, _capacity(strlen(str))
		//{
		//	strcpy(_str, str);
		//}
		//����д���ԣ���ʼ���ǰ�������˳���Ⱥ��
		//string(const char* str = "")
		//	: _size(strlen(str))
		//	, _capacity(_size)
		//	,_str(new char[_capacity + 1])
		//{
		//	strcpy(_str, str);
		//}
		string(const char* str="")//�Ƽ� ���ó�ʼ���б�
		{ 
			_size = strlen(str);
			_capacity = _size;
			_str = new char[_size+1];
			strcpy(_str, str);
		}
		//��ͳд��
		//string(const string&s)//��������
		//	:_str(new char[s._capacity+1])
		//	, _size(s._size)
		//	, _capacity(s._capacity)
		//{
		//	strcpy(_str, s._str); 
		//}
		////s1=s2
		////s1=s1
		//string& operator=(const string& s)//��ֵ����
		//{
		//	if (this != &s)//��ֹ�Լ����Լ���ֵ����ʱ�ͷſռ���Ҳ����Լ��� 
		//	{
		//		delete[]_str;
		//		_str = new char[s._capacity + 1];
		//		strcpy(_str, s._str);
		//		_size = s._size;
		//		_capacity = s._capacity;
		//		//_str = (char*)realloc(_str, _size*sizeof(char));
		//		//������realloc����Ϊ����
		//	}
		//	return *this;
		//}

		//�ִ�д��������tmp
		void swap(string& tmp)//*this��tmp����
		{
			::swap(tmp._str, _str);//����std��׼��Ľ������õ���ģ��
			:: swap(tmp._size, _size);
			::swap(tmp._capacity, _capacity);
		}
		string(const string&s)//��������
			:_str(nullptr)
			, _size(0)
			, _capacity(0)
		{
			string tmp(s._str);
			swap(tmp);
		}
		//s1=s2
		//s1=s1
		//string& operator=(const string& s)//��ֵ���أ�����
		//{
		//	if (this != &s)//��ֹ�Լ����Լ���ֵ����ʱ�ͷſռ���Ҳ����Լ��� 
		//	{
		//		string tmp(s);
		//		swap(tmp);
		//      //::swap(tmp,*this);//�������ջ�����
		//	}
		//	return *this;
		//}

		//s����tmp
		string& operator=(string s)//��ֵ����,��������ֵ����
		{
			swap(s);
			return *this;
		}

		~string()//����
		{
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}
		const char* c_str()const//��������this	
		{
			return _str;
		}
		size_t size()const
		{
			return _size;
		}
		size_t capacity()const
		{
			return _capacity;
		}
		char& operator[](size_t pos)
		{
			assert(pos < _size);
			return _str[pos];
		}
		const char& operator[](size_t pos)const
		{
			assert(pos < _size);
			return _str[pos];
		}

		void reserve(size_t n)
		{
			if (n>_capacity)
			{
				char* tmp = new char[n+1];//��ΪҪ��/0
				strcpy(tmp, _str);
				delete[]_str;
				_str = tmp;
				_capacity = n;
			}
		}
		void resize(size_t n,char ch='\0')
		{
			if (n > _size)
			{
				//��������
				reserve(n);
				for (size_t i = 0; i < n - _size; i++)
				{
					_str[i] = ch;
				}
				_str[n] = '\0';
				_size = n;
			}
			else
			{
				//ɾ������
				_size = n;
				_str[_size] = '\0';
			}
			if (n>_capacity)
			{
				char* tmp = new char[n + 1];//��ΪҪ��/0
				strcpy(tmp, _str);
				delete[]_str;
				_str = tmp;
				_capacity = n;
			}
		}
		void push_back(char ch)
		{
			//if (_size == _capacity)//��������
			//{
			//	reserve(_capacity = 0 ? 4 : 2 * _capacity);
			//}
			//_str[_size] = ch;
			//_size++;
			//_str[_size] = '\0';//�ǵü���\0
			insert(_size, ch);
		}
		void append(const char* str)
		{
			size_t len = strlen(str);

			if (_size +len> _capacity)//��������
			{
				reserve(_size+len+1);//_capacity�������
			}
			strcpy(_str + _size, str);
			//strcat(_str,str);//���ã���ΪstrcatҪ��\0��ʵ�ʵ���Ҳ��������
			_size += len;
			//insert(_size, str);
		}
		void append(size_t n, char ch)
		{
			reserve(_size + n);
			for (size_t i = 0; i < n; i++)
			{
				push_back(ch);
			}
		}
		string& operator+=(char ch)//֧������+=
		{
			push_back(ch);
			return *this;
		}
		string& operator+=(const char* str)
		{
			append(str);
			return *this;
		}

		string& insert(size_t pos, char ch)//pos֮ǰ��
		{
			assert(pos <= _size);
			if (_size == _capacity)//��������
			{
				reserve(_capacity = 0 ? 4 : 2 * _capacity);
			}
			size_t end = _size+1;
			while (end > pos)
			{
				_str[end] = _str[end-1];
				end--;
			}
			_str[pos] = ch;
			_size++;
			return *this;
		}
		string& insert(size_t pos, char* str)
		{
			assert(pos <= _size);
			size_t len = strlen(str);
			if (_size + len> _capacity)//��������
			{
				reserve(_size + len + 1);//_capacity�������
			}
			//Ų��
			size_t end = _size+len;
			while (end>=pos+len)
			{
				_str[end] = _str[end - len];
				end--;
			}
			strncpy(_str + pos, str, len);
			_size += len;
			return *this;
		}
		void erase(size_t pos, size_t len = npos)
		{
			assert(pos < _size);
			if (len == npos || pos + len >= _size)
			{
				_str[pos] = '\0';
				_size = pos;
			}
			else
			{
				strcpy(_str + pos, _str + pos + len);
				_size -= len;
			}
		}
		void clear()
		{
			_str[0] = '\0';
			_size = 0;
		}
		size_t find(char ch, size_t pos = 0)
		{
			assert(pos < _size);
			for (size_t i = pos; i<_size; i++)
			{
				if (ch == _str[i])
					return i;
			}
			return npos;
		}
		size_t find(const char* sub, size_t pos = 0)const
		{
			assert(pos < _size);
			const char* ptr=strstr(_str + pos, sub);//strstr
			if (ptr == nullptr)
			{
				return npos;
			}
			return ptr - _str;
		}
		string substr(size_t pos,size_t len=npos)const
		{
			size_t reallen = len;
			if (len == npos || pos + len > _size)
			{
				reallen = _size - pos;
			}
			string sub;
			for (size_t i = 0; i<reallen; i++)
			{
				sub += _str[pos+i];
			}
			return sub;
		}

		bool operator>(const string& s)const
		{
			return strcmp(_str, s._str)>0;
		}
		bool operator==(const string& s)const
		{
			return strcmp(_str, s._str) == 0;
		}
		bool operator>=(const string& s)const
		{
			return *this > s||*this == s;
		}
		bool operator<=(const string& s)const
		{
			return !(*this > s);
		}
		bool operator<(const string& s)const
		{
			return !(*this >= s);
		}
		bool operator!=(const string& s)const
		{
			return !(*this == s);
		}

	private:
		//char _buff[16];15����Ч�ַ���<16����buff�У�>=16����_str��,VS������
		size_t _size;
		size_t _capacity;
		char* _str;
		static size_t npos;//��̬��Ա����������������ֵ
		//const static size_t npos=-1;//���ǣ�const static���Ը�ֵ������Ҳ���ö�����
		//����Ҫ�ŵ�public��
	};
	
	size_t string::npos=-1;//��̬��Ա������������߶���
	ostream& operator<<(ostream& out, const string& s)
	{
		for (size_t i = 0; i < s.size(); i++)
		{
			out << s[i];//s[i]�Ѿ�����
		}
		return out;
	}
	istream& operator>>(istream& in, string& s)
	{
		s.clear();//std���string����Ļ����
		char ch;
		ch=in.get();
		char tmp[32];//��������s����̬����,�����ڻ�����
		size_t i = 0;
		while (ch != ' '&&ch != '\0')
		{
			tmp[i++] = ch;
			if (i == 32 - 1)//���˾͸�s
			{
				tmp[32] = '\0';
				s += tmp;
				i = 0;
			}
			ch = in.get();
		}

		//ʣ�µĸ�s
		tmp[i] = '\0';
		s += tmp;
		return in;
	}


	void Test1()
	{
		string s1("hello i love you");
		string s2;
		string::iterator it = s1.begin();
		while (it != s1.end())
		{
			cout << *it << endl;
			it++;
		}
		cout << endl;
	}
	void Test2()
	{
		string s1("hello i love you");
		string s2(s1);
		string s3("hahahahha");
		s1 = s3;
	}
	void Test3()
	{
		string s1("hello i love you");
		string s3("hahahahha");
		swap(s1, s3);//std��׼���swap����ģ��
		//��������std��swap���������
		s1.swap(s3);//ģ��ʵ�ֵ�string��swap
	}
}



