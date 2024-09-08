#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "-------------------------------"

template<typename T>class List
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
		void set_data(T Data);
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
		bool operator==(const ConstBaseIterator& other)const;
		bool operator!=(const ConstBaseIterator& other)const;

		//dereference operator
		const T& operator*()const;
	};

public:

	class ConstIterator : public ConstBaseIterator
	{
	public:

		ConstIterator(Element* Temp = nullptr);
		~ConstIterator();
		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator operator--(int);
	};
	class ConstReverseIterator : public ConstBaseIterator
	{
	public:

		ConstReverseIterator(Element* Temp = nullptr);
		~ConstReverseIterator();

		//incremento/decremento
		ConstReverseIterator& operator++();
		ConstReverseIterator operator++(int);
		ConstReverseIterator& operator--();
		ConstReverseIterator operator--(int);
	};
	class Iterator : public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr) : ConstIterator(Temp) {}
		~Iterator() {}
		
		T& operator*();
	};
	class ReverseIterator : public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr) : ConstReverseIterator(Temp) {}
		~ReverseIterator() {}
		T& operator*();
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

	void set_data(T Data);
};

//                Конец объявления класса

