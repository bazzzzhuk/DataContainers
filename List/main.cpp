#include<iostream>
using namespace std;

#define tab "\t"
#define delimiter "\n---------------------------------\n"

class List
{
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
	}*Head, * Tail; //Объекты классов и структур и указатели на эти объекты можно объявлять 
					//непоссредственно после описания классов и структур
	size_t size;	//Размер списка. size_t - это typedef на unsigned int
public:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	~List()
	{
		//while (Head)pop_front();
		while (Tail)pop_back();

		cout << "LDestructor:\t" << this << endl;
	}

	//   ADDING ELEMENTS
	void push_front(int Data)
	{
		Element* New = new Element(Data);
		if (Head == nullptr && Tail == nullptr)Head = Tail = New; else
		{
			//Создаем элемент в котором будет храниться добавляемое значение
			//2.Пристыковываем новый элемент к списку:
			New->pNext = Head;
			//3.Пристыковываем начальный элемент списка к новому элементу:
			Head->pPrev = New;
			//4.Делаем новый элемент начальным элементом списка:
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
			//цепляем новый элемент за хвост списка:
			New->pPrev = Tail;
			//Пристыковываем список к новому элементу:
			Tail->pNext = New;
			//Делаем новый элемент хвостом списка:
			Tail = New;
		}
		size++;

	}
	void insert(int Data, int Index)
	{
		if (Index < 0)return;
		if (Index == 0||size==0)return push_front(Data);
		if (Index >= size)return push_back(Data);
		//1.Доходим до нужного элемента:
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
		//Независимо от того, каким образом мы дошли до нужного элемента: 
		// с начала списка или с конца списка, процедура добавления элемента будет идентичной
		////////////////////////////////////////////////////////////////
		//2. Создаём новый элемент
		Element* New = new Element(Data);
		//3. Пристыковываем новый элемент к списку
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		//4. Вклиниваем новый элемент в список:
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;

		size++;
	}

	//  REMOVING ELEMENTS:

	void pop_front()
	{
		if (Head == nullptr && Head == nullptr)return;
		if (Head == Tail)//Если голова и хвост равны, значит они указывают либо на ноль, 
						//либо на один и тот же элемент
						//Ситуацию с пустым списком обрабатывает предыдущее условие
						//Ситуацию с вырожденным спском обрабатывает текущее условие 
						// и в этом if удаляется один единственный элемент списка
		{
			delete Head;
			Head = Tail = nullptr;
		}else
		{//Общий случай:
			// 1. Смещаем Голову на следующий элемент:
			Head = Head->pNext;
			//Удаляем элемент из памяти
			delete Head->pPrev;
			//Обнуляем указатель на удаленный элемент (Делаем Хед последним элементом списка)
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
		cout << "Количество элементов списка: " << size;
		cout << delimiter << endl;
	}
	void reverse_print()const
	{
		cout << delimiter << endl;
		cout <<"Tail: " << Tail << endl;
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Head: " << Head << endl;
		cout << "Количество элементов списка: " << size;
		cout << delimiter << endl;
	}
};

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

#endif // BASE_CHECK
#ifdef HOME_WORK
	List list1 = {3,5,8,13,21};
	List list2 = {34,55,89};
	List list3 = list1 + list2;
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;
#endif // HOME_WORK
}