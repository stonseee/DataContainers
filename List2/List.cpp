#define _CRT_SECURE_NO_WARNINGS
#include"List.h"

//template<typename T>void List<T>::Element::set_data(T Data)
//{
//	this->Data = Data;
//}

/////////////////////////////////////////////////////
/////////////     CONST ITERATORS       /////////////  

//                 ConstIterator
template<typename T>List<T>::ConstIterator::ConstIterator(Element* Temp) : ConstBaseIterator(Temp)
{
	cout << "ConstIteratorConstructor:\t" << this << endl;
}
template<typename T>List<T>::ConstIterator::~ConstIterator()
{
	cout << "ConstIteratorDestructor:\t" << this << endl;
}

template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ConstIterator List<T>::ConstIterator::operator++(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}
template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::ConstIterator List<T>::ConstIterator::operator--(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}

//              ConstReverseIterator
template<typename T>List<T>::ConstReverseIterator::ConstReverseIterator(Element* Temp) : ConstBaseIterator(Temp)
{
	cout << "ConstReverseIteratorConstructor:\t" << this << endl;
}
template<typename T>List<T>::ConstReverseIterator::~ConstReverseIterator()
{
	cout << "ConstReverseIteratorDestructor:\t" << this << endl;
}

template<typename T>typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator++(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
template<typename T>typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator--(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}

//               ConstBaseIterator
template<typename T>bool List<T>::ConstBaseIterator::operator==(const ConstBaseIterator& other)const
{
	return this->Temp == other.Temp;
}
template<typename T>bool List<T>::ConstBaseIterator::operator!=(const ConstBaseIterator& other)const
{
	return this->Temp != other.Temp;
}

template<typename T>const T& List<T>::ConstBaseIterator::operator*()const
{
	return Temp->Data;
}

/////////////     CONST ITERATORS       /////////////  
/////////////////////////////////////////////////////

/////////////////////////////////////////////////////
/////////////         ITERATORS         /////////////  

template<typename T>T& List<T>::Iterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}

template<typename T>T& List<T>::ReverseIterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}

/////////////         ITERATORS         /////////////  
/////////////////////////////////////////////////////

/////////////////////////////////////////////////////
/////////////          MEMBERS          /////////////     

template<typename T>typename List<T>::ConstIterator List<T>::begin() const
{
	return Head;
}
template<typename T>typename List<T>::ConstIterator List<T>::end() const
{
	return nullptr;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::rbegin() const
{
	return Tail;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::rend() const
{
	return nullptr;
}
template<typename T>typename List<T>::Iterator List<T>::begin()
{
	return Head;
}
template<typename T>typename List<T>::Iterator List<T>::end()
{
	return nullptr;
}
template<typename T>typename List<T>::ReverseIterator List<T>::rbegin()
{
	return Tail;
}

template<typename T>typename List<T>::ReverseIterator List<T>::rend()
{
	return nullptr;
}

template<typename T>List<T>::List()
{
	Head = Tail = nullptr;
	size = 0;
	cout << "ListConstrustor:\t" << this << endl;
}

template<typename T>List<T>::List(const std::initializer_list<T>& il) : List()
{
	for (T const* it = il.begin(); it != il.end(); ++it)
		push_back(*it);
}

template<typename T>List<T>::List(const List<T>& other) :List()
{
	*this = other;
	cout << "ListCopyConstructor:\t" << this << endl;
}

template<typename T>List<T>::~List()
{
	//while (Head)pop_front();
	while (Tail)pop_back();
	cout << "ListDestrustor:\t\t" << this << endl;
}

template<typename T>void List<T>::push_front(T Data)
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

template<typename T>void List<T>::push_back(T Data)
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

template<typename T>void List<T>::insert(T Data, int idx)
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

template<typename T>void List<T>::pop_front()
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

template<typename T>void List<T>::pop_back()
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

template<typename T>void List<T>::erase(int idx)
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

template<typename T>void List<T>::print()const
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

template<typename T>void List<T>::reverse_print()const
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

template<typename T>List<T>& List<T>::operator=(const List<T>& other)
{
	if (this == &other)return *this;
	while (Head)pop_front();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
	cout << "ListCopyAssignment:\t" << this << endl;
	return *this;
}

//template<typename T>void List<T>::set_data(T Data)
//{
//	Head->set_data(Data);
//}

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


