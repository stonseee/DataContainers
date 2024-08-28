#include<iostream>
using namespace std;
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"
#define delimiter "-------------------------------"

class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;

	public:

		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			: Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "ElementConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "ElementDestructor:\t" << this << endl;
		}
		friend class List;
	}*Head, *Tail;
	size_t size;

public:

	class Iterator
	{
		Element* Temp;

	public:

		Iterator(Element* Temp = nullptr) : Temp(Temp)
		{
			cout << "IteratorConstructor:\t" << this << endl;
		}
		~Iterator()
		{
			cout << "IteratorDestructor:\t" << this << endl;
		}
		Iterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}
		Iterator operator++(int)
		{
			Iterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		Iterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		Iterator operator--(int)
		{
			Iterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}

		//comparison operators
		bool operator==(const Iterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const Iterator& other)const
		{
			return this->Temp != other.Temp;
		}

		//dereference operator
		const int& operator*()const
		{
			return Temp->Data;
		}
		int& operator*()
		{
			return Temp->Data;
        }
	};
	class ReverseIterator
	{
		Element* Temp;

	public:

		ReverseIterator(Element* Temp = nullptr) : Temp(Temp)
		{
			cout << "ReverseIteratorConstructor:\t" << this << endl;
		}
		~ReverseIterator()
		{
			cout << "ReverseIteratorDestructor:\t" << this << endl;
		}

		//incremento/decremento
		ReverseIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ReverseIterator operator++(int)
		{
			ReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ReverseIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ReverseIterator operator--(int)
		{
			ReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}

		//comparison operators
		bool operator==(const ReverseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ReverseIterator& other)const
		{
			return this->Temp != other.Temp;
		}

		//dereference operators
		const int& operator*()const
		{
			return Temp->Data;
		}
		int& operator*()
		{
			return Temp->Data;
		}
	};
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	ReverseIterator rbegin()
	{
		return Tail;
	}
	ReverseIterator rend()
	{
		return nullptr;
	}

	//constructors
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "ListConstrustor:\t" << this << endl;
	}
	List(const std::initializer_list<int>& il) : List()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
			push_back(*it);
	}
	List(const List& other) :List()
	{
		*this = other;
		cout << "ListCopyConstructor:\t" << this << endl;
	}
	~List()
	{
		//while (Head)pop_front();
		while (Tail)pop_back();
		cout << "ListDestrustor:\t\t" << this << endl;
	}
	
	//adding elements
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{					
			Head = Head->pPrev = new Element(Data, Head, nullptr);
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
			Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		}
		size++;
	}
	void insert(int Data, int idx)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{	
			Element* Temp = Head;
			if (idx < size / 2)
			{
				Temp = Head;
				for (int i = 0; i < idx; i++)Temp = Temp->pNext;
			}
			else
			{
				Temp = Tail;
				for (int i = 0; i < size - idx - 1; i++)Temp = Temp->pPrev;
			}
			Element* New = new Element(Data);
			Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);			
		}
		size++;
	}

	//removing elements
	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr) return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
		}
		else
		{
			Head = Head->pNext;
			delete Head->pPrev;
			Head->pPrev = nullptr;
		}		
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr && Tail == nullptr) return;
		if (Head == Tail)
		{
			delete Tail;
			Head = Tail = nullptr;
		}
		else
		{
			Tail = Tail->pPrev;
			delete Tail->pNext;
			Tail->pNext = nullptr;
		}
		size--;
	}	
	void erase(int idx)
	{		
		if (idx <= 0) return pop_front();
		if (idx >= size) return pop_back();		
		Element* Temp;
		if (idx < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < idx; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - idx - 1; i++)Temp = Temp->pPrev;
		}		
		Temp->pPrev->pNext = Temp->pNext;
		Temp->pNext->pPrev = Temp->pPrev;
		delete Temp;
		size--;
	}

	//methods
	void print()const
	{
		cout << delimiter << endl;
		cout << "Head:\t" << Head << endl;

		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout 
			<< Temp->pPrev << tab
			<< Temp << tab
			<< Temp->Data << tab
			<< Temp->pNext << endl;

		cout << "Tail:\t" << Tail << endl;
		cout << "Количество элементов списка: " << size << endl;
		cout << delimiter << endl;
	}
	void reverse_print()const
	{
		cout << delimiter << endl;
		cout << "Tail:\t" << Tail << endl;

		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout 
			<< Temp->pPrev << tab
			<< Temp << tab
			<< Temp->Data << tab
			<< Temp->pNext << endl;

		cout << "Head:\t" << Head << endl;
		cout << "Количество элементов списка: " << size << endl;
		cout << delimiter << endl;
	}
	
	List& operator=(const List& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		cout << "ListCopyAssignment:\t" << this << endl;
		return *this;
	}	
};

List operator+(List& left, List& right)
{	
	List copy = left;	
	for(List::Iterator it = right.begin(); it != right.end(); ++it)
	{
		copy.push_back(*it);
	}		
	return copy;		
}

//#define BASE_CHECK

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

	List list = { 3, 5, 8, 13, 21 };
	List list1 = { 1, 2, 3, 4, 5 };
	/*for (int i : list)cout << i << tab;
	cout << endl;
	for (List::ReverseIterator it = list.rbegin(); it != list.rend(); ++it)
		cout << *it << tab;
	cout << endl;*/
	//list.print();
	//list.reverse_print();

	List list2 = list + list1;
	list2.print();
	list.print();
	list1.print();
}