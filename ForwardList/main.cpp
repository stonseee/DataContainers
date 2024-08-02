#include<iostream>
using namespace std;

#define tab "\t"

class Element
{
	int Data;
	Element* pNext;
public:
	Element(int Data, Element* pNext = nullptr) : Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

class ForwardList
{
	Element* Head;
public:
	ForwardList()
	{
		Head = nullptr;
		cout << "LConstrustor\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestrustor\t" << this << endl;
	}

	//adding elements
	void push_front(int Data)
	{
		Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		Element* Temp = Head;       
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}

		Element* New = new Element(Data);

		Temp->pNext = New;
	}
	void insert(int Data, int index)
	{
		Element* New = new Element(Data);	
		if (index == 0)return push_front(Data);
		int ctr = 0;
		Element* Temp = Head;
		Element* TempNext = Head;
		while (Temp)
		{
			++ctr;
			TempNext = Temp->pNext;
			if (ctr == index)
			{
				Temp->pNext = New;
				New->pNext = TempNext;
			}
			Temp = Temp->pNext;
		}
	}
	void pop_front()
	{
		int ctr = 0;
		Element* Temp = Head;
		while (Temp->pNext)
		{
			++ctr;
			if (ctr == 2)Head = Temp;
			Temp = Temp->pNext;
		}
	}
	void pop_back()
	{
		int ctr = 0;
		Element* Temp = Head;
		Element* TempNext = Head;
		while (Temp)
		{
			++ctr;			
			TempNext = Temp->pNext;			
			if (TempNext->pNext == nullptr)
			{
				Temp->pNext = nullptr;
			}			
			Temp = Temp->pNext;			
		}		
	}
	void erase(int index)
	{
		if (index == 0)return pop_front();
		int ctr = 0;
		Element* Temp = Head;	
		Element* TempNext = Head;
		while (Temp)
		{
			++ctr;
			TempNext = Temp->pNext;
			if (ctr == index)
			{
				Temp->pNext = TempNext->pNext;
			}
			Temp = Temp->pNext;
		}
	}

	//methods
	void print() const
	{
		cout << "Head:\t" << Head << endl;
		Element* Temp = Head;
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
	}
};

void main()
{
	setlocale(LC_ALL, "");
	//Element element(5);
	int n;
	cout << "Введите количество элементов : "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
		//list.push_front(rand() % 100);
	}
	list.print();
	//list.pop_front();
	//list.pop_back();
	//list.erase(4);
	//list.insert(4,5);
	list.print();
}