#include<iostream>
using namespace std;
using std::cout;
using std::cin;
using std::endl;

class Element
{
private:
	int Data;
	Element* pNext;
	Element* pPrev;
public:
	Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) : Data(Data), pNext(pNext), pPrev(pPrev)
	{
		cout << "ElementConstructor\t" << this << endl;
	}
	~Element()
	{
		cout << "ElementDestructor\t" << this << endl;
	}
	friend class List;
};

class List
{
private:
	int size = 0;
	Element* Head;
	Element* Tail;
public:
	List()
	{
		Head = nullptr;
		Tail = nullptr;
		int size = 0;
		cout << "ListConstructor\t" << this << endl;
	}
	~List()
	{		
		while(Tail)pop_back();
		cout << "ListDestructor\t" << this << endl;
	}

	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{
			Element* New = new Element(Data);
			New->pNext = Head;
			Head->pPrev = New;
			Head = New;
		}
		size++;
	}
	void push_back(int Data)
	{		
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{		
			Element* New = new Element(Data);
			New->pPrev = Tail;
			Tail->pNext = New;
			Tail = New;				
		}
		size++;
	}
	void insert(int idx, int Data)
	{
		if (idx <= 0)return push_front(Data);
		if (idx >= size)return push_back(Data);
		Element* Temp = Head;
		for (int i = 0; i < idx; ++i)
		{			
			Temp = Temp->pNext;
		}
		Element* New = new Element(Data);
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;
		size++;
	}
 
	void pop_back()
	{
		if (Head == Tail)
		{
			delete Tail;
			Head = nullptr;
			Tail = nullptr;
		}
		if (Head != Tail)
		{
			Tail = Tail->pPrev;
			delete Tail->pNext;
			Tail->pNext = nullptr;
		}
		size--;
	}
	void pop_front()
	{
		if (Head == Tail)
		{
			delete Head;
			Head = nullptr;
			Tail = nullptr;
		}
		if (Head != Tail)
		{
			Head = Head->pNext;
			delete Head->pPrev;
			Head->pPrev = nullptr;
		}
		size--;
	}

	void print()
	{
		Element* Temp = Head;
		for (int i = 0; i < size; ++i)
		{
			cout << Temp->Data << "\t";
			Temp = Temp->pNext;
		}
		cout << endl;
		cout << "size " << size << endl;
	}
	void reverse_print()
	{
		Element* Temp = Tail;
		for (int i = 0; i < size; ++i)
		{
			cout << Temp->Data << "\t";
			Temp = Temp->pPrev;
		}
		cout << endl;
		cout << "size " << size << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");

	int n = 7;	
	List list;	
	for (int i = 0; i < n; i++)
	{
		//list.push_back(rand() % 100);
		list.push_front(rand() % 100);
	}
	list.insert(4, 99);
	list.pop_front();	
	list.print();	
	list.reverse_print();	
}