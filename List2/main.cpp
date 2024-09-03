#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"List.h"
#include"List.cpp"
using namespace std;
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"
#define delimiter "-------------------------------"

//#define BASE_CHECK
//#define ConstIteratorS_CHECK

template<typename T>void Grow(List<T>& list)
{
	for (typename List<T>::Iterator it = list.begin(); it != list.end(); ++it)
	{
		*it *= 10;
	}
}

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Введите количество элементов: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();
	for (int i = 0; i < 100; i++)list.pop_back();
	list.reverse_print();
#endif // BASE_CHECK

#ifdef ConstIteratorS_CHECK
	List list = { 3, 5, 8, 13, 21 };
	List list1 = { 1, 2, 3, 4, 5 };
	/*for (int i : list)cout << i << tab;
	cout << endl;
	for (List::ReverseConstIterator it = list.rbegin(); it != list.rend(); ++it)
		cout << *it << tab;
	cout << endl;*/
	//list.print();
	//list.reverse_print();

	List list2 = list + list1;
	list2.print();
	list.print();
	list1.print();
#endif // ConstIteratorS_CHECK
	List<int> list1 = { 3, 5, 8, 13, 21 };
	List<int> list2 = { 34, 55, 89 };
	List<int> list3 = list1 + list2;
	//list3.print();
	//for (int i : list1)cout << i << tab; cout << endl;
	//for (int i : list2)cout << i << tab; cout << endl;
	//for (int i : list3)cout << i << tab; cout << endl;
	//Grow(list3);
	for (int i : list3)cout << i << tab; cout << endl;
	list3.print();
	//list1.print();

	List<std::string> s_list = { "Хорошо", "живет", "на", "свете", "Винни", "Пух" };
	for (std::string i : s_list) cout << i << tab; cout << endl;
}