#include<iostream>
#include<time.h>
using namespace std;
using std::cout;
using std::cin;
using std::endl;

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
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

	}
	int get_data()const
	{
		return Data;
	}
	~Element()
	{
#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

	}
	friend class ForwardList;
	friend class ForwardList operator+(const ForwardList& left, const ForwardList& right);
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
	ForwardList(const ForwardList& other) :ForwardList()
	{
		//Deep copy
		*this = other;
		cout << "FLCopyConstructor:\t" << this << endl;
	}
	ForwardList(int n)
	{
		Head = nullptr;
		for (int i = 0; i < n; i++)
		{
			//list.push_back(rand() % 100);
			//this->push_front(rand() % 100);
			this->push_front(NULL); // 4.097 sec. 50000
			//this->push_back(NULL);// 4.233 sec. 50000
		}
		//cout << "SingleARGConstructor:\t" << this << endl;
	}
	ForwardList(ForwardList&& other)//moveConstructor
	{
		this->count = other.count;
		this->Head = other.Head;
		other.count = 0;
		other.Head = nullptr;
		cout << "MoveConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		clock_t t_start = clock();
		while (count)pop_front();
		clock_t t_end = clock();
		cout << "FLDestructor" << this << "\t in time --> " << double(t_end - t_start) / CLOCKS_PER_SEC << endl;
	}

	////Operators 

	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;//не являются ли this & other одним объектом?
		clock_t t_start = clock();
		while (Head)pop_front();// Старое значение объекта удаляется из памяти
		//Deep copy
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);

		//cout << "FLCopyAssignment:\t" << this << endl;
		clock_t t_end = clock();
		cout << "FLCopyAssignment:\t" << this << "\t in time --> " << double(t_end - t_start) / CLOCKS_PER_SEC << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other)
	{
		if (this == &other)return *this;
		//delete old memory
		delete Head;
		//shallowCopy
		this->count - other.count;
		this->Head = other.Head;
		//обнуляем принимаемый объект
		other.count = 0;
		other.Head = nullptr;
		cout << "MoveAssignment:\t\t" << this << endl;
		return *this;
	}
	int& operator[](int n)
	{
		Element* Temp = Head;
		for (int i = 0; i < n; i++)Temp = Temp->pNext;
		return Temp->Data;
	}

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
		////создаем элемент и сохраняем в него добавляемое значение
		//Element* New = new Element(Data);
		////привязыввеем новый созданный элемент к началу списка
		//New->pNext = Head;
		////Переносим Голову на новый элемент (отправляем новый элемент в Голову)
		//Head = New;
		Head = new Element(Data, Head);
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
		//Element* New = new Element(Data);
		//3.Пристыковываем новый элемент к его следующему элементу:
		//New->pNext = Temp->pNext;
		//4. Пристыковываем предыдущий элемент у новому:
		//->pNext = New;
		Temp->pNext = new Element(Data, Temp->pNext);
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
		if (!Head || Head->pNext == nullptr)return pop_front();
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
		for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;
		Element* erase = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete erase;
		//Temp->pNext->pNext = nullptr;
		count--;
	}
	// methods:
	void print()const
	{
		//Element* Temp = Head;//Temp - это итератор.
		////Итератор - это указатель при помощи которого можно перебирать элементы структуры данных.
		//while (Temp)
		//{
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//	Temp = Temp->pNext;
		//}
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов: " << ForwardList::count << endl;
	}
};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList	fusion;
	for (Element* Temp = left.get_head(); Temp; Temp = Temp->pNext)
	{
		fusion.push_back(Temp->get_data());

	}
	for (Element* Temp = right.get_head(); Temp; Temp = Temp->pNext)
	{
		fusion.push_back(Temp->get_data());
	}
	return fusion;
}


//#define	BASE_CHECK	
#define PLUS_CHECK
//#define PERFORMANCE_CHECK
//#define SINGLE_ARG_CONSTR_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	cout << "ForwardList" << endl;
	int n;
	cout << "Enter lenght list: "; cin >> n;
	ForwardList list;
	//cout << "push_front" << endl;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
		//list.push_back(rand() % 100);
	}
	//list.print();
	cout << DELIMETER;
	//list.push_back(123);
	/*cout << "pop_front" << endl;
	list.pop_front();
	list.print();
	cout << DELIMETER;
	cout << "pop_back" << endl;
	list.pop_back();
	list.print();
	cout << DELIMETER;*/
	/*int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();*/
	cout << DELIMETER;
#endif

#ifdef PLUS_CHECK
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

	ForwardList fusion;
	cout << DELIMETER;
	fusion = list1 + list2;
	cout << DELIMETER;
	fusion.print();

	/*int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list1.insert(value, index);
	list1.print();

	list2.erase(3);
	list2.print();*/
	//cout << list1.get_data(4) << endl;
	//ForwardList fusion = list1 + list2;
	//fusion.print();
#endif

#ifdef PERFORMANCE_CHECK
	int n;
	cout << "Enter lenght list: "; cin >> n;
	ForwardList list;
	clock_t t_start = clock();
	//cout << "push_front" << endl;
	for (int i = 0; i < n; i++)
	{
		//list.push_back(rand() % 100);
		list.push_front(rand() % 100);
	}
	clock_t t_end = clock();
	cout << "FORWARDLIST filled for " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec. ";
	system("PAUSE");
#endif // PERFORMANCE_CHECK

#ifdef SINGLE_ARG_CONSTR_CHECK
	ForwardList list(50000);//50000 - 4.298 sec.
	//list.print();
	clock_t t_start = clock();
	for (int i = 0; i < list.get_count(); i++)
		list[i] = rand() % 100;
	clock_t t_end = clock();
	cout << "FORWARDLIST filled with [] for " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec. ";
	//for (int i = 0; i < list.get_count(); i++)cout << list[i] << tab;
	cout << endl;
#endif // SINGLE_ARG_CONSTR_CHECK



}