#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "-------------------------------"

//template<typename T>List<T> operator+(const List<T>& left, const List<T>& right);

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
	}*Head, * Tail;
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
	ConstIterator begin() const;	
	ConstIterator end() const;
	ConstReverseIterator rbegin() const;
	ConstReverseIterator rend() const;
	Iterator begin();
	Iterator end();
	ReverseIterator rbegin();
	ReverseIterator rend();

	//constructors
	List();
	List(const std::initializer_list<T>& il);	
	List(const List<T>& other);	
	~List();	

	//adding elements
	void push_front(T Data);
	void push_back(T Data);	
	void insert(T Data, int idx);	

	//removing elements
	void pop_front();	
	void pop_back();	
	void erase(int idx);	

	//methods
	void print()const;	
	void reverse_print()const;	

	List<T>& operator=(const List<T>& other);
	
};

template<typename T>List<T> operator+(const List<T>& left, const List<T>& right);
