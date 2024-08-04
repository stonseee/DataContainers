#include<iostream>
using namespace std;
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"

class Element
{
	int Data;
	Element* pNext;
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) : Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

int Element::count = 0;

class ForwardList
{
	Element* Head;
	unsigned int size;
public:
	ForwardList()
	{
		Head = nullptr;
		size = 0;
		cout << "LConstrustor\t" << this << endl;
	}
	ForwardList(const ForwardList& other) : ForwardList()
	{
		*this = other;
		cout << "LCopyConstrustor\t" << this << endl;
	}
	ForwardList(ForwardList&& other)noexcept : Head(other.Head), size(other.size)
	{
		other.Head = nullptr;
		other.size = 0;			
		cout << "MoveConstructor\t" << this << endl;
	}
	~ForwardList()
	{
		while (Head)pop_front();		
		cout << "LDestrustor\t" << this << endl;
	}

	//operators
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "LCopyAssignment\t" << this << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other)noexcept
	{
		if (this == &other)return *this;
		delete this->Head;
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		cout << "MoveAssignment\t" << this << endl;
		return *this;
	}

	//adding elements
	void push_front(int Data)
	{
		Head = new Element(Data, Head);		
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		Element* Temp = Head;       
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = new Element(Data);
		size++;
	}
	void insert(int Data, int Index)
	{
		if (Index > Head->count)return;
		if (Index == 0) return push_front(Data);
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}
	void pop_front()
	{
		if (Head == nullptr)return;
		Element* erased = Head;
		Head = Head->pNext;
		delete erased;
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr || Head->pNext == nullptr)return pop_front();
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}
	void erase(int Index)
	{		
		if (Index >= size)return;
		if (Index == 0) return pop_front();
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++) Temp = Temp->pNext;
		Element* erased = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete erased;
		size--;
	}

	//methods
	void print() const
	{		
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов: " << Element::count << endl;
	}
};

//#define BASE_CHECK
//#define COUNT_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
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
	//list.erase(5);
	list.insert(123, 2);
	list.print();
#endif // BASE_CHECK

#ifdef COUNT_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1.print();

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();
#endif // COUNT_CHECK

	int n;
	cout << "Введите количество элементов : "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_back(rand() % 100);
		list.push_front(rand() % 100);
	}
	
	cout << "List filled" << endl;

	//list.print();
	//ForwardList list2 = list;	
	ForwardList list2 = std::move(list);	
	//ForwardList list2;
	//list2 = list;
	list2.print();
	
}