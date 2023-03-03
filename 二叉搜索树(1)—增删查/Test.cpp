#include"BinarySearchTree.h"
#include<vector>
void Test1()
{
	BinarySearchTree<int> t;
	//int arr[] = { 8, 3, 1, 10, 6, 4, 7, 12, 13 }; 
	int arr[]={ 7, 5, 1, 6, 2, 14, 5, 8 };
	for (auto e : arr)
	{
		t.Insert(e);
		//cout << a << " ";
	}
	t.InOrder();
	cout << endl;
	t.Erase(5);
	t.Erase(1);
	t.InOrder();
}




int main()
{
	Test1();
	return 0;
}