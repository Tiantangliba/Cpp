#include"my_List.h"
int main()
{
	my_list::Test3();
	return 0;
}





//
//int main()
//{
//	list<int> lt;
//	lt.push_back(1);
//	lt.push_back(3);
//	lt.push_back(5);
//	lt.push_back(6);
//	lt.push_back(7);
//	
//	list<int>::iterator it = lt.begin();
//	while (it != lt.end())
//	{
//		cout << *it << " ";
//		it++;
//	}
//	cout << endl;
//
//	 it = lt.begin();
//	while (it != lt.end())
//	{
//		*it *= 2;
//		it++;
//	}
//
//	for (auto& e : lt)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//
//	lt.push_front(50);
//	lt.pop_back();
//	for (auto& e : lt)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//
//	auto pos=find(lt.begin(), lt.end(), 2);
//	if (pos != lt.end())
//	{
//		printf("�ҵ���\n");
//		lt.insert(pos, 3);//pos����ʧЧ����Ϊ��������
//		for (auto& e : lt)
//		{
//			cout << e << " ";
//		}
//		cout << endl;
//	}
//	else
//	{
//		cout << "û�ҵ�" << endl;
//	}
//	auto pos_erase = find(lt.begin(), lt.end(), 10);
//	if (pos_erase != lt.end())
//	{
//		printf("�ҵ���\n");
//		lt.erase(pos_erase);//pos��ʧЧ,�ڵ㶼û�ˣ�Ұָ��
//		for (auto& e : lt)
//		{
//			cout << e << " ";
//		}
//		cout << endl;
//	}
//
//
//	list<int> lt2;
//	lt2.push_back(1);
//	lt2.push_back(3);
//	lt2.push_back(5);
//	lt2.push_back(6);
//	lt2.push_back(7);
//	//splice ����ת��
//	//lt2.sort();
//	//Ϊʲôalgorithm�����Ѿ���sort�ˣ�����Ҫ��sort��
//	//��Ϊ������ò��ˣ��㷨�����sortҪ������ռ���Ҫ������
//	//vector �� string ����
//	//�������sort�õ��ǹ鲢ʵ�ֵ�
//	//n������Ҫ����vector+�㷨��sort  or  list���sort
//	//vector�죬���Ұ�list�����ݷŵ�vector���棬������ٷ���list ���� һֱ��list�����Ÿ���
//	//unique ȥ��  ǰ����������ȥ��
//	//reverse ����
//	//merge�鲢
//	return 0;
//}