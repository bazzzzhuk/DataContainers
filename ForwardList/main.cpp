#include<iostream>
#include<time.h>
using namespace std;
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"
#define DELIMETER "----------------------\n"
class ForwardList;
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
	friend class Iterator;
	friend class ForwardList;
	friend class ForwardList operator+(const ForwardList& left, const ForwardList& right);
};


class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr) :Temp(Temp)
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
	explicit ForwardList(int count) :ForwardList()
	{
		while (count--)push_front(0);
		cout << "FLCOUNTConstructor:\t" << this << endl;
	}
	ForwardList(const std::initializer_list<int>& il) :ForwardList()
	{
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	ForwardList(ForwardList&& other) :ForwardList()
	{
		*this = std::move(other);
	}
	~ForwardList()
	{
		clock_t t_start = clock();
		while (Head)pop_front();
		clock_t t_end = clock();
		cout << "FLDestructor" << this << "\t in time --> " << double(t_end - t_start) / CLOCKS_PER_SEC << endl;
	}

	////Operators 

	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;//не являются ли this & other одним объектом?
		while (Head)pop_front();// Старое значение объекта удаляется из памяти
		//Deep copy
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_front(Temp->Data);
		reverse();
		cout << "FLCopyAssignment:\t" << this << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		this->Head = other.Head;
		this->count = other.count;
		other.Head = nullptr;
		other.count = 0;
		cout << "FLMoveAssignment:\t" << this << endl;
		return *this;

	}
	//ForwardList& operator
	int operator[](int index)const
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
		return Temp->Data;
	}
	int& operator[](int index)
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
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
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
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
	ForwardList& operator=(ForwardList& other)
	{
		cout << "!#@#" << endl;
		other.Head = nullptr;
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}

	void reverse()
	{
		ForwardList reverse;//этот список будет задом-наперёд
		while (Head)//пока список содержит элементы 
		{
			reverse.push_front(Head->Data);//добавляем головной элемент 
			pop_front();//и удаляем начальный элемент списка
		}
		//Head = reverse.Head;//подменяем наш список реверсным
		//count = reverse.count;
		*this = std::move(reverse);//встроенная функция которая явным образом вызывает moveAssignment,
		//если он есть, в противном случае behavior is undefined.
		reverse.Head = nullptr;//поскольку реверсный список является локальной переменной
		//для него будет вызван деструктор, который полностью его очистит, а он указывает на ту же память
		//на которую указывает наш основной список, следовательно деструктор удалит и наш основной список.
	}
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
	/*void Print()
	{
	cout typeid(arr).name()<<endl;
	cout <<sizeof(arr)/sizeof(arr[0])<<endl;
	}*/
};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList	fusion;
	for (Element* Temp = left.get_head(); Temp; Temp = Temp->pNext)
	{
		fusion.push_front(Temp->get_data());

	}
	for (Element* Temp = right.get_head(); Temp; Temp = Temp->pNext)
	{
		fusion.push_front(Temp->get_data());
	}
	fusion.reverse();
	return fusion;
}


//#define	BASE_CHECK	
//#define PLUS_CHECK
//#define PERFORMANCE_CHECK
#define SUBSCRIPTOR_OPER_CHECK
//#define COPY_SEMANTIC_PERFORMANCE_CHECK
//#define MOVE_SEMANTIC_CHECK
//#define RANGE_BASED_FOR_ARRAY

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
	for (int i = 0; i < list1.get_count(); i++)cout << list1[i] << tab; cout << endl;

	ForwardList list2;
	list2.push_back(3);
	list2.push_back(5);
	list2.push_back(8);
	list2.push_back(13);
	list2.push_back(21);
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	for (int i = 0; i < list2.get_count(); i++)cout << list2[i] << tab; cout << endl;

	ForwardList list3;
	cout << DELIMETER;
	list3 = list1 + list2;
	cout << DELIMETER;
	for (int i = 0; i < list3.get_count(); i++)cout << list3[i] << tab; cout << endl;


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
#ifdef SUBSCRIPTOR_OPER_CHECK
	clock_t start;
	clock_t end;

	int n;
	start = clock();
	cout << "Enter size list: "; cin >> n;
	ForwardList list(n);
	for (int i = 0; i < list.get_count(); i++)
		list[i] = rand() % 100;
	end = clock();
	cout << "List DONE in " << double(end - start) / CLOCKS_PER_SEC << "  sec." << endl;
	system("PAUSE");
	for (int i = 0; i < list.get_count(); i++)cout << list[i] << tab;
	cout << endl;

#endif // SUBSCRIPTOR_OPER_CHECK
#ifdef COPY_SEMANTIC_PERFORMANCE_CHECK

	int n;
	cout << "Enter lenght list: "; cin >> n;
	clock_t t_start, t_end;

	ForwardList list1;
	t_start = clock();
	for (int i = 0; i < n; i++)
		list1.push_front(rand() % 100);
	t_end = clock();
	cout << "List done in " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec." << endl;
	system("PAUSE");
	t_start = clock();
	ForwardList list2 = list1;
	t_end = clock();
	cout << "Copy complete for " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec." << endl;
	//for (int i = 0; i < list2.get_count(); i++)cout << list2[i] << tab; cout << endl;
	//for (int i = 0; i < list1.get_count(); i++)cout << list1[i] << tab; cout << endl;  
#endif // COPY_SEMANTIC_PERFORMANCE_CHECK
#ifdef MOVE_SEMANTIC_CHECK

	clock_t t_start, t_end;
	ForwardList list1;
	ForwardList list2;
	t_start = clock();
	for (int i = 0; i < 10000000; i++)list1.push_front(rand());
	for (int i = 0; i < 10000000; i++)list1.push_front(rand());
	t_end = clock();
	cout << "list filled for " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec." << endl;
	system("PAUSE");



	t_start = clock();
	ForwardList list3 = list1 + list2;
	t_end = clock();
	cout << "lists concatenated for " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec." << endl;

	t_start = clock();
	ForwardList list4 = list3;
	t_end = clock();
	cout << "lists concatenated for " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec." << endl;

#endif // MOVE_SEMANTIC_CHECK
#ifdef RANGE_BASED_FOR_ARRAY

	int arr[] = { 3,5,8,13,21 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;
	//Range-based for - for для диапазона. Под диапазоном понимается контейнер (какой-то набор элементов)
	//
	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;
	cout << typeid(arr).name() << endl;
	Print(arr);
#endif // RANGE_BASED_FOR_ARRAY

	//ForwardList list = { 3,5,8,13,21 };// Перечисление значений в фигурных скобках через запятую неявно создают объект класса 'initializer list'
	//list.print();
	//for (int i : list)cout << i << tab; cout << endl;
	//cout << DELIMETER << endl;
	//for (Iterator it = list.begin(); it != list.end(); ++it)
	//{
	//	cout << *it << endl;
	//}
}