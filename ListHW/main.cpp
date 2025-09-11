#include<iostream>
#include<time.h>
using namespace std;
using std::cout;
using std::cin;
using std::endl;

#define DELIMETER "----------------------\n"
#define tab "\t"

class Element
{
	int Data;
	Element* pPrev; //Адрес предыдущего элемента
	Element* pNext;//Адрес следующего элемента
public:
	Element(int Data, Element* pPrev = nullptr, Element* pNext = nullptr)
	{
		this->Data = Data;
		this->pPrev = pPrev;
		this->pNext = pNext;
	}
	int get_data()const
	{
		return Data;
	}
	friend class List;
};
class List
{
	int count = 0;
	Element* Head;
	Element* Tail;
public:
	List()//Конструктор по умолчанию
	{
		Head = nullptr;
		Tail = nullptr;
		cout << "ListConstructor:\t" << this << endl;
	}
	explicit List(int count) :List()
	{
		while (count--)push_front(count + 1);
		cout << "ListCountConstructor:\t" << this << endl;
	}
	~List()
	{
		//while (Head)pop_front();
		cout << "ListDestructor" << this << endl;
	}

	int get_count()const
	{
		return count;
	}
	Element* get_head()const
	{
		return Head;
	}
	Element* get_tail()const
	{
		return Tail;
	}
	int get_data(int index)const
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
		return Temp->Data;
	}
	// Add
	void push_front(int Data)
	{
		if (!Head && !Tail)
		{
			//cout << "1" << endl;
			Head = Tail = new Element(Data, Tail, Head);
		}
		else {
			//cout << "2" << endl;
			Head = new Element(Data, nullptr, Head);
			Head->pNext->pPrev = Head;
		}
		count++;
	}
	void push_back(int Data)
	{
		if (!Head && !Tail)Head = Tail = new Element(Data, Tail, Head); else
		{
			Tail = new Element(Data, Tail, nullptr);
			Tail->pPrev->pNext = Tail;
		}
		count++;
	}
	void pop_front()
	{
		if (!Head && !Tail)return;
		Element* Temp = Head;
		Head = Head->pNext;
		delete Temp->pPrev;
		Temp -> pPrev = nullptr;
		delete Temp;
		Head->pPrev = nullptr;
		count--;
	}
	void pop_back()
	{
		if (!Head && !Tail)return;
		Element* Del_elem = Tail;
		Tail = Tail->pPrev;
		delete Del_elem;
		Del_elem = nullptr;
		Tail->pNext = nullptr;

		/*delete Del_elem->pNext;
		Del_elem->pNext = nullptr;
		delete Del_elem;
		Del_elem->pPrev = nullptr;*/
		

		count--;
	}
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << "Temp->pPrev:\t " << Temp->pPrev << tab << "Temp: \t" << Temp << tab << "Temp->Data: \t" << Temp->Data << tab << " Temp->pNext:\t " << Temp->pNext << endl;
		cout << "Количество элементов: " << List::count << endl;
	}
	void print_back()const
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << "Temp->pPrev:\t " << Temp->pPrev << tab << "Temp: \t" << Temp << tab << "Temp->Data: \t" << Temp->Data << tab << " Temp->pNext:\t " << Temp->pNext << endl;
		cout << "Количество элементов: " << List::count << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");

	List list(5);
	list.push_front(66);
	list.print();

	list.push_back(77);
	list.print_back();

	list.pop_front();
	list.print();

	list.pop_back();
	list.print();
}