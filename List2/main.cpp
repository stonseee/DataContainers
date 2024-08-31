#include<iostream>
using namespace std;
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"
#define delimiter "-------------------------------"

template<typename T>
class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;

	public:

		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr)
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
	class ConstBaseIterator
	{
	protected:

		Element* Temp;

	public:

		ConstBaseIterator(Element* Temp = nullptr) : Temp(Temp) {}
		~ConstBaseIterator() {}

		//comparison operators
		bool operator==(const ConstBaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ConstBaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}

		//dereference operator
		const T& operator*()const
		{
			return Temp->Data;
		}
	};

public:

	class ConstIterator : public ConstBaseIterator
	{
	public:

		ConstIterator(Element* Temp = nullptr) : ConstBaseIterator(Temp)
		{
			cout << "ConstIteratorConstructor:\t" << this << endl;
		}
		~ConstIterator()
		{
			cout << "ConstIteratorDestructor:\t" << this << endl;
		}
		ConstIterator& operator++()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return *this;
		}
		ConstIterator operator++(int)
		{
			ConstIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return old;
		}
		ConstIterator& operator--()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return *this;
		}
		ConstIterator operator--(int)
		{
			ConstIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return old;
		}		
	};
	class ConstReverseIterator : public ConstBaseIterator
	{
	public:

		ConstReverseIterator(Element* Temp = nullptr) : ConstBaseIterator(Temp)
		{
			cout << "ConstReverseIteratorConstructor:\t" << this << endl;
		}
		~ConstReverseIterator()
		{
			cout << "ConstReverseIteratorDestructor:\t" << this << endl;
		}

		//incremento/decremento
		ConstReverseIterator& operator++()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return *this;
		}
		ConstReverseIterator operator++(int)
		{
			ConstReverseIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return old;
		}
		ConstReverseIterator& operator--()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return *this;
		}
		ConstReverseIterator operator--(int)
		{
			ConstReverseIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return old;
		}		
	};
	class Iterator : public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr) : ConstIterator(Temp) {}
		~Iterator() {}
		T& operator*()
		{
			return ConstBaseIterator::Temp->Data;
		}
	};
	class ReverseIterator : public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr) : ConstReverseIterator(Temp) {}
		~ReverseIterator() {}
		T& operator*()
		{
			return ConstBaseIterator::Temp->Data;
		}
	};
	ConstIterator begin() const
	{
		return Head;
	}
	ConstIterator end() const
	{
		return nullptr;
	}
	ConstReverseIterator rbegin() const
	{
		return Tail;
	}
	ConstReverseIterator rend() const
	{
		return nullptr;
	}
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
	List(const std::initializer_list<T>& il) : List()
	{
		for (T const* it = il.begin(); it != il.end(); ++it)
			push_back(*it);
	}
	List(const List<T>& other) :List()
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
	void push_front(T Data)
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
	void push_back(T Data)
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
	void insert(T Data, int idx)
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
				for (int i = idx; i < size - 1; i++)Temp = Temp->pPrev;
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
	
	List<T>& operator=(const List<T>& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		cout << "ListCopyAssignment:\t" << this << endl;
		return *this;
	}	
};

template<typename T>List<T> operator+(const List<T>& left, const List<T>& right)
{	
	List<T> buffer = left;	
	for (typename List<T>::ConstIterator it = right.begin(); it != right.end(); ++it)
	{
		buffer.push_back(*it);
		//*it *= 10;
	}
	return buffer;
}
template<typename T>void Grow(List<T>& list)
{
	for (typename List<T>::Iterator it = list.begin(); it != list.end(); ++it)
	{
		*it *= 10;
	}
}

//#define BASE_CHECK
//#define ConstIteratorS_CHECK

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
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;
	Grow(list3);
	for (int i : list3)cout << i << tab; cout << endl;
	
}