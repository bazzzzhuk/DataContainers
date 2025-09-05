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
	int get_data()const
	{
		return Data;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

class ForwardList
{
	int count = 0;
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
		while (count)pop_front();
		Head = nullptr;
		cout << "FLDestructor" << this << endl;
	}
	//ForwardList(ForwardList&& other)
	//{
	//	//moveConstructor
	//	this->count = other.count;
	//	this->Head = other.Head;
	//	//обнуляем принимаемый объект для того чтобы предотвратить удаление его ресурсов деструктором
	//	//other.count = 0;
	//	//other.Head = nullptr;
	//	cout << "MoveConstructor:\t" << this << endl;

	//}
	int get_count()const
	{
		return count;
	}
	Element* get_head()const
	{
		return Head;
	}
	int get_data(int index)const
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
		return Temp->Data;
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
		count++;
	}
	void push_back(int Data)
	{
		if (!Head) return push_front(Data);
		Element* Temp = Head;
		while (Temp->pNext)Temp = Temp->pNext;
		Temp->pNext = new Element(Data);
		count++;
	}
	void insert(int Data, int index)
	{
		if (index == 0)return push_front(Data);
		if (index >= ForwardList::count)return push_back(Data);
		//1.Доходим ДО нужного элемента (элемент перед добавляемым)
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;
		//2.Создаём добавляемый элемент:
		Element* New = new Element(Data);
		//3.Пристыковываем новый элемент к его следующему элементу:
		New->pNext = Temp->pNext;
		//4. Пристыковываем предыдущий элемент у новому:
		Temp->pNext = New;
		count++;
	}
	//  REMOVING ELEMENTS  //
	void pop_front()
	{
		if (!Head)return;
		Element* Temp = Head;
		Head = Temp->pNext;
		delete Temp;
		count--;
	}
	void pop_back()
	{
		if (!Head)return;
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
		count--;
	}
	void erase(int index)
	{
		if (index == 0)return pop_front();
		if (index >= ForwardList::count)return pop_back();
		Element* Temp = Head;
		for (int i = 0; i < index - 2; i++)Temp = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete Temp->pNext->pNext;
		Temp->pNext->pNext = nullptr;
		count--;
	}
	// methods:
	ForwardList& operator=(ForwardList& other)
	{
		cout << "!#@#" << endl;
		other.Head = nullptr;
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	void print()const
	{
		Element* Temp = Head;//Temp - это итератор.
		//Итератор - это указатель при помощи которого можно перебирать элементы структуры данных.
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
		cout << "Количество элементов: " << ForwardList::count << endl;
	}
};

ForwardList operator+(const ForwardList f1, ForwardList f2)
{
	//int i = f2.get_count();
	Element* Temp = f1.get_head();
	for (int i = f1.get_count() - 1; i >= 0; i--)
	{
		f2.push_front(f1.get_data(i));
		//cout << "Temp " << Temp << " Temp->get_data() " << Temp->get_data() << endl;
		Temp = Temp + 1;
	}
	cout << "F2" << endl;
	f2.print();
	return f2;
}
//#define	BASE_CHECK	
void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	cout << "ForwardList" << endl;
	int n;
	cout << "Enter lenght list: "; cin >> n;
	ForwardList list;
	cout << "push_back" << endl;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.push_back(123);
	list.print();
	cout << DELIMETER;
	cout << "pop_front" << endl;
	list.pop_front();
	list.print();
	cout << DELIMETER;
	cout << "pop_back" << endl;
	list.pop_back();
	list.print();
	cout << DELIMETER;
	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();
	cout << DELIMETER;
#endif

	ForwardList list1;
	list1.push_back(0);
	list1.push_back(1);
	list1.push_back(1);
	list1.push_back(2);
	list1.print();

	ForwardList list2;
	list2.push_back(3);
	list2.push_back(5);
	list2.push_back(8);
	list2.push_back(13);
	list2.push_back(21);
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();

	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list1.insert(value, index);
	list1.print();

	list2.erase(0);
	list2.print();

	//cout << list1.get_data(4) << endl;
	ForwardList fusion = list1 + list2;
	fusion.print();

}