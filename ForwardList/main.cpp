#include<iostream>
using namespace std;

#define tab "\t"
#define DELIMETER "----------------------\n"

class Element
{
	int Data;//значение элемента	
	Element* pNext;//Адрес следующего элемента
public:
	Element(int Data, Element* pNext = nullptr)
	{
		this->Data = Data;
		this->pNext = pNext;
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
		//Конструктор по умолчанию - создаёт пустой список
		Head = nullptr;//если список пустой, то его голова указывает на ноль.
		cout << "FLConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "FLDestructor" << this << endl;
	}
	// Adding elements
	void push_front(int Data)
	{
		//создаем элемент и сохраняем в него добавляемое значение
		Element* New = new Element(Data);
		//привязыввеем новый созданный элемент к началу списка
		New->pNext = Head;
		//Переносим Голову на новый элемент (отправляем новый элемент в Голову)
		Head = New;
	}
	void push_back(int Data)
	{
		if (!Head) return push_front(Data);
		Element* Temp = Head;
		while (Temp->pNext)
		{
			//cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			//if (Temp->pNext)break;
			Temp = Temp->pNext;
		}
		Temp->pNext = new Element(Data);
	}
	void pop_front()
	{
		if (!Head)return;
		Element* Temp = Head;
		Head = Temp->pNext;
		Temp = nullptr;
		delete Temp;
	}
	void pop_back()
	{
		if (!Head)return;
		Element* Temp = Head;
		while ((Temp->pNext)->pNext)
		{
			//cout << Temp->pNext;
			Temp = Temp->pNext;
		}
		Temp->pNext = nullptr;
		delete Temp->pNext;
	}

	// methods:
	void print()const
	{
		Element* Temp = Head;//Temp - это итератор.
		//Итератор - это указатель при помощи которого можно перебирать элементы структуры данных.
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
	cout << "ForwardList" << endl;
	int n;
	cout << "Enter lenght list: "; cin >> n;
	ForwardList list;
	cout << "push_back" << endl;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	cout << DELIMETER;
	cout << "pop_front" << endl;
	list.pop_front();
	list.print();
	cout << DELIMETER;
	cout << "pop_back" << endl;
	list.pop_back();
	list.print();

}