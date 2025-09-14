#include<iostream>
using namespace std;
using std::cout;
using std::endl;
using std::cin;

#define tab "\t"
#define delimiter "\n---------------------------------\n"

class List;
class Element;
class Iterator;

class Element
{
	int Data;
	Element* pNext;
	Element* pPrev;
public:
	Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
		:Data(Data), pNext(pNext), pPrev(pPrev)
	{
		cout << "EConstructor:\t" << this << endl;
	}	
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class List;
	friend class Iterator;
};
class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp=nullptr) :Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "ItDestructor:\t" << this << endl;
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
	bool operator==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}
	int operator*()const
	{
		return Temp->Data;
	}
	int& operator*()
	{
		return Temp->Data;
	}
};
class List
{
	Element* Head;
	Element* Tail;
	size_t size;//�� �����������..
public:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "ListConstructor:\t" << this << endl;
	}
	List(const std::initializer_list<int>& il) :List()
	{
		for (int const* it = il.begin(); it != il.end(); it++)push_back(*it);
	}
	List(const List& other) :List()
	{
		//Deep copy
		*this = other;
		cout << "ListCopyConstructor:\t" << this << endl;
	}
	List(List&& other) :List()
	{
		*this = std::move(other);
	}
	~List()
	{
		while (Tail)pop_back();

		cout << "ListDestructor:\t" << this << endl;
	}
////////////////////////////////////////
	List& operator=(const List& other)
	{
		if (this == &other)return *this;//�� �������� �� this & other ����� ��������?
		while (Head)pop_front();// ������ �������� ������� ��������� �� ������
		//Deep copy
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "ListCopyAssignment:\t" << this << endl;
		return *this;
	}
	List& operator=(List&& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		this->Head = other.Head;
		other.Head = nullptr;
		cout << "ListMoveAssignment:\t" << this << endl;
		return *this;
	}
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	//   ADDING ELEMENTS
	void push_front(int Data)
	{
		Element* New = new Element(Data);
		if (Head == nullptr && Tail == nullptr)Head = Tail = New; else
		{
			//������� ������� � ������� ����� ��������� ����������� ��������
			//2.�������������� ����� ������� � ������:
			New->pNext = Head;
			//3.�������������� ��������� ������� ������ � ������ ��������:
			Head->pPrev = New;
			//4.������ ����� ������� ��������� ��������� ������:
			Head = New;
		}
		size++;
	}
	void push_back(int Data)
	{
		Element* New = new Element(Data);
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = New;
		}
		else
		{
			//������� ����� ������� �� ����� ������:
			New->pPrev = Tail;
			//�������������� ������ � ������ ��������:
			Tail->pNext = New;
			//������ ����� ������� ������� ������:
			Tail = New;
		}
		size++;

	}
	void insert(int Data, int Index)
	{
		if (Index < 0)return;
		if (Index == 0||size==0)return push_front(Data);
		if (Index >= size)return push_back(Data);
		//1.������� �� ������� ��������:
		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
		}
		///////////////////////////////////////////////////////////////////////
		//���������� �� ����, ����� ������� �� ����� �� ������� ��������: 
		// � ������ ������ ��� � ����� ������, ��������� ���������� �������� ����� ����������
		////////////////////////////////////////////////////////////////
		//2. ������ ����� �������
		Element* New = new Element(Data);
		//3. �������������� ����� ������� � ������
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		//4. ���������� ����� ������� � ������:
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;

		size++;
	}
	void erase(int Index)
	{
		if (Index < 0)return;
		if (Index == 0 || size == 0)return pop_front();
		if (Index >= size)return pop_back();
		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
		}
		Temp->pPrev->pNext = Temp->pNext;
		Temp->pNext->pPrev = Temp->pPrev;
		delete Temp;
		size--;
	}

	//  REMOVING ELEMENTS:

	void pop_front()
	{
		if (Head == nullptr && Head == nullptr)return;
		if (Head == Tail)//���� ������ � ����� �����, ������ ��� ��������� ���� �� ����, 
						//���� �� ���� � ��� �� �������
						//�������� � ������ ������� ������������ ���������� �������
						//�������� � ����������� ������ ������������ ������� ������� 
						// � � ���� if ��������� ���� ������������ ������� ������
		{
			delete Head;
			Head = Tail = nullptr;
		}else
		{//����� ������:
			// 1. ������� ������ �� ��������� �������:
			Head = Head->pNext;
			//������� ������� �� ������
			delete Head->pPrev;
			//�������� ��������� �� ��������� ������� (������ ��� ��������� ��������� ������)
			Head->pPrev = nullptr;
		}
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr && Tail == nullptr)return;
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


	//   Methods:
	void print()const
	{

		cout << delimiter << endl;
		cout << "Head: " << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Tail: " << Tail << endl;
		cout << "���������� ��������� ������: " << size;
		cout << delimiter << endl;
	}
	void reverse_print()const
	{
		cout << delimiter << endl;
		cout <<"Tail: " << Tail << endl;
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Head: " << Head << endl;
		cout << "���������� ��������� ������: " << size;
		cout << delimiter << endl;
	}
};

List operator+(List& left, List& right)
{
	List fusion;
	for (int i : left) fusion.push_back(i);
	for (int i : right) fusion.push_back(i);	
	return fusion;
}

//#define BASE_CHECK
#define HOME_WORK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Enter size list: "; cin >> n;
	List list;
	list.pop_front();
	list.print();
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();
	//list.pop_back();
	//list.print();
	//list.reverse_print();

	int index;
	int value;
	cout << "Enter index-in element: "; cin >> index;
	cout << "Enter value-in element: "; cin >> value;
	list.insert(value, index);
	list.print();
	list.reverse_print();

	cout << "Enter index-in element: "; cin >> index;
	list.erase(index);
	list.print();




#endif // BASE_CHECK
#ifdef HOME_WORK
	List list1 = {3,5,8,13,21};
	List list2 = {34,55,89};
	List list3 = list1 + list2;
	List list4 = list3;
	list4.erase(1);
	list1.print();
	list2.print();
	list3.print();
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;
	for (int i : list4)cout << i << tab; cout << endl;
	list4.print();
#endif // HOME_WORK
}