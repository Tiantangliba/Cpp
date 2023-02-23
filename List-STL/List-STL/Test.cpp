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
//		printf("找到了\n");
//		lt.insert(pos, 3);//pos不会失效，因为无需扩容
//		for (auto& e : lt)
//		{
//			cout << e << " ";
//		}
//		cout << endl;
//	}
//	else
//	{
//		cout << "没找到" << endl;
//	}
//	auto pos_erase = find(lt.begin(), lt.end(), 10);
//	if (pos_erase != lt.end())
//	{
//		printf("找到了\n");
//		lt.erase(pos_erase);//pos会失效,节点都没了，野指针
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
//	//splice 链表转移
//	//lt2.sort();
//	//为什么algorithm库里已经有sort了，链表还要给sort？
//	//因为库里的用不了，算法库里的sort要求物理空间需要连续，
//	//vector 和 string 可以
//	//链表里的sort用的是归并实现的
//	//n个数据要排序，vector+算法的sort  or  list里的sort
//	//vector快，并且把list的数据放到vector里面，排序好再返回list 都比 一直在list里面排更快
//	//unique 去重  前提是有序，再去重
//	//reverse 逆置
//	//merge归并
//	return 0;
//}