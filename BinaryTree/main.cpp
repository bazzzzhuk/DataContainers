#include<iostream>
#include<time.h>
#include<algorithm>
using namespace std;
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"
//#define DEBUG

class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) :
			Data(Data), pLeft(pLeft), pRight(pRight)
		{
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

		}
		friend class Tree;
		friend class UniqueTree;
	}*Root;
public:
	Element* getroot()const
	{
		return Root;
	}
	Tree() :Root(nullptr)
	{
		cout << "TConstructor:\t" << this << endl;
	}
	Tree(const std::initializer_list<int>& il) :Tree()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
		{
			insert(*it, Root);
			cout << "ILconstructor:\t" << this << endl;
		}
	}
	~Tree()
	{
		clear(Root);
		cout << "TDestructor:\t" << this << endl;
	}
	void balance()
	{
		balance(Root);
	}
	void clear()
	{
		return clear(Root);
		//Root = nullptr;
	}
	void insert(int Data)
	{
		insert(Data, Root);
	}
	void erase(int Data)
	{
		erase(Data, Root);
	}
	int minValue()const
	{
		return minValue(Root);
	}
	int maxValue()const
	{
		return maxValue(Root);
	}
	int sum()const
	{
		return sum(Root);
	}
	int count()const
	{
		return count(Root);
	}
	double avg()const
	{
		return (double)sum(Root) / count(Root);
	}
	int depth()const
	{
		return depth(Root);
	}
	void depth_print(int depth, int width = 4)const
	{
		depth_print(depth, Root, width);
		cout << endl;
	}
	void tree_print()const
	{
		tree_print(depth(), 4 * depth() / 4);
	}
	void print()const
	{
		print(Root);
		cout << endl;
	}

private:
	void balance(Element* Root)
	{
		if (Root == nullptr)return;

		if (abs(count(Root->pLeft) - count(Root->pRight)) <= 2)return;
		if (count(Root->pLeft) < count(Root->pRight))
		{
			if (Root->pLeft)insert(Root->Data, Root->pLeft);
			else Root->pLeft - new Element(Root->Data);
			Root->Data = minValue(Root->pRight);
			erase(minValue(Root->pRight), Root->pRight);
			//balance(Root);
		}
		if (count(Root->pLeft) > count(Root->pRight))
		{
			if (Root->pRight)insert(Root->Data, Root->pRight);
			else Root->pRight = new Element(Root->Data);
			Root->Data = maxValue(Root->pLeft);
			erase(maxValue(Root->pLeft), Root->pLeft);
		}
		balance(Root->pLeft);
		balance(Root->pRight);
		balance(Root);
	}
	void clear(Element*& Root)
	{
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
		Root = nullptr;
	}
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr) this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	void erase(int Data, Element*& Root)
	{
		if (Root == nullptr)return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->pLeft == Root->pRight)
			{
				delete Root;
				Root = nullptr;
			}
			else
			{//для того чтобы дерево балансировалось при удалении элементов,
				//нужно его взвесить:
				if (count(Root->pLeft) > count(Root->pRight))
				{
					//и если левая ветка тяжелее чем правая, то берем из неё максимальное значение
					//потому что оно ближе всего к удаляемому значениюЖ
					Root->Data = maxValue(Root->pLeft);
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					//в проивном случае берем минимально значение из правой ветки
					//потому что оно ближе всего к удаляемому значению
					Root->Data = minValue(Root->pRight);
					erase(minValue(Root->pRight), Root->pRight);

				}
			}
		}
	}
	int minValue(Element* Root)const
	{
		return Root == nullptr ? 0 : Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
		/*if (Root->pLeft == nullptr) return Root->Data;
		else return minValue(Root->pLeft);*/
	}
	int maxValue(Element* Root)const
	{
		return !Root ? 0 : Root->pRight ? maxValue(Root->pRight) : Root->Data;
		/*if (Root->pRight == nullptr) return Root->Data;
		else return maxValue(Root->pRight);*/
	}
	int count(Element* Root)const
	{
		return !Root ? 0 : count(Root->pLeft) + count(Root->pRight) + 1;
		/*if (Root == nullptr)return 0;
		else return count(Root->pLeft) + count(Root->pRight) + 1;*/

	}
	int sum(Element* Root)const
	{
		return Root == nullptr ? 0 : sum(Root->pLeft) + sum(Root->pRight) + Root->Data;
	}
	int depth(Element* Root)const
	{
		/*return Root == nullptr ? 0 :
			depth(Root->pLeft) + 1 > depth(Root->pRight) + 1 ?
			depth(Root->pLeft) + 1:
		depth(Root->pRight)+1;*/

		/*if (Root == nullptr)return 0;
		int l_depth = depth(Root->pLeft)+1;
		int r_depth = depth(Root->pRight)+1;
		return l_depth < r_depth ? r_depth : l_depth;*/

		return Root == nullptr ? 0 : std::max(depth(Root->pLeft) + 1, depth(Root->pRight) + 1);
	}
	void depth_print(int depth, Element* Root, int width)const
	{
		if (Root == nullptr)
		{
			/*cout.width(width/width/2);
			cout << "";*/
			return;
		}
		if (depth == 0)
		{
			cout.width(width*1.3);
			cout << Root->Data;
		}
		depth_print(depth - 1, Root->pLeft, width);
		depth_print(depth - 1, Root->pRight, width);
	}
	void tree_print(int depth, int width)const
	{
		if (depth == -1)
		{
			/*cout.width(width);
			cout << " ";*/
			return;
		}
		tree_print(depth - 1, width * 1.55);
		depth_print(depth - 1, width);
		cout << endl;
	}
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
};
class UniqueTree :public Tree
{
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr) this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if (Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
public:
	void insert(int Data)
	{
		insert(Data, Root);
	}
};

template<typename T>
void measure_performance(const char message[], T(Tree::* function)()const, const Tree& tree)
{
	//int* (function)() - указатель на функцию которая ничего не принимает и возвращает значение типа инт
	clock_t start = clock();
	T rezult = (tree.*function)();
	clock_t end = clock();
	cout << message << rezult << " \t\t\tВычеслено за " << double(end - start) / CLOCKS_PER_SEC << " секунд\n";
}

//#define BASE_CHECK
//#define ERASE_CHECK
#define DEPTH_CHECK
//#define PERFORMANCE_CHECK


void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Enter count elements: "; cin >> n;
	cout << "Hello Tree" << endl;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();
	cout << endl;
	cout << "Min value ---> " << tree.minValue() << endl;
	cout << "Max value ---> " << tree.maxValue() << endl;
	cout << "Count Elements: " << tree.count() << endl;
	cout << "Sum Elements: " << tree.sum() << endl;
	cout << "AVG Elements: " << tree.avg() << endl;

	UniqueTree u_tree;
	for (int i = 0; i < n; i++)
	{
		u_tree.insert(rand() % 100);
	}
	u_tree.print();
	cout << endl;
	cout << "Min value ---> " << u_tree.minValue() << endl;
	cout << "Max value ---> " << u_tree.maxValue() << endl;
	cout << "Count Elements: " << u_tree.count() << endl;
	cout << "Sum Elements: " << u_tree.sum() << endl;
	cout << "AVG Elements: " << u_tree.avg() << endl;
#endif // BASE_CHECK
#ifdef ERASE_CHECK

	Tree tree =
	{
				50,
		25,				75,
	16,     32,		 58,   85,91,98
	};
	tree.print();
	/*int value;
	cout << "Enter erase element: ";  cin >> value;
	tree.erase(value);*/
	//tree.erase(50);
	tree.print();
	cout << "Depth tree: " << tree.depth() << endl;
	measure_performance("Глубина дерева: ", &Tree::depth, tree);
#endif // ERASE_CHECK
#ifdef DEPTH_CHECK

	Tree tree =
	{
				50,
		25,				75,
	16,     32,		 58,   85//,91//,98
	};
	tree.print();
	cout << "Depth tree: " << tree.depth() << endl;
	//tree.depth_print(1);
	tree.tree_print();

	Tree tree2 = { 55,34,21,13,8,5,3 };
	tree2.tree_print();
	tree2.balance();
	tree2.tree_print();


#endif // ERASE_CHECK
#ifdef PERFORMANCE_CHECK
	int n;
	cout << "Enter count elements: "; cin >> n;
	cout << "Hello Tree" << endl;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	/*tree.print();
	cout << endl;
	cout << "Min value ---> " << tree.minValue() << endl;
	cout << "Max value ---> " << tree.maxValue() << endl;
	cout << "Count Elements: " << tree.count() << endl;
	cout << "Sum Elements: " << tree.sum() << endl;
	cout << "AVG Elements: " << tree.avg() << endl;
	cout << "Tree depth: " << tree.depth() << endl;*/
	measure_performance("Минимальное значение в дереве: ", &Tree::minValue, tree);
	measure_performance("Максимальное значение в дереве: ", &Tree::maxValue, tree);
	measure_performance("Количество элементов в дереве: ", &Tree::count, tree);
	measure_performance("Сумма элементов значение в дереве: ", &Tree::sum, tree);
	measure_performance("Средне-арифметическое элементов значение в дереве: ", &Tree::avg, tree);
	measure_performance("Глубина дерева: ", &Tree::depth, tree);
#endif // PERFORMANCE_CHECK


}