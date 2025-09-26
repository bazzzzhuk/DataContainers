#include<iostream>
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
	int depth(int Data)const
	{
		return depth(Data, Root);
	}
	void print()const
	{
		print(Root);
		cout << endl;
	}
	void tree_print()const
	{
		return tree_print(Root, depth());
	}

private:
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
	/// >>--->
	const int depth(Element* Root)const
	{
		return !Root ? 0 : 1 + (depth(Root->pLeft) < depth(Root->pRight) ? depth(Root->pRight) : depth(Root->pLeft));
	}
	const int depth(int Data, Element* Root)const
	{
		return Data == Root->Data ? 0 : 1 + (Data < Root->Data ? depth(Data, Root->pLeft) : depth(Data, Root->pRight));
	}
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
	
	void tree_print(Element* Root, int level)const
	{
		if (Root)
		{
			if (depth(Root->Data) == level)
			{
				for (int i = 0; i < level--; ++i) cout << "__";
				cout << Root->Data;
			}
			tree_print(Root->pLeft, level - 1);
			cout << endl;
			tree_print(Root->pRight, level - 1);
		}

		////()
		//int rows = depth();
		//int cols = rows * 2;
		//int** arr = new int* [rows];
		//for (int i = 0; i < rows; i++)
		//{
		//	arr[i] = new int[cols] {0};
		//}

		//if (!Root)return;
		//cout << Root->Data<<" ";
		//tree_print(Root->pLeft, level);
		//tree_print(Root->pRight, level);
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
//#define BASE_CHECK
#define DEPTH_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Enter count elements: "; cin >> n;
	cout << "Hello Tree" << endl;
	Tree tree;
	clock_t t_start, t_end;
	t_start = clock();
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	t_end = clock();
	cout << "Constr " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec." << endl;
	t_start = clock();
	tree.minValue();
	t_end = clock();
	cout << "Min value in time " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec." << endl;
	t_start = clock();
	tree.maxValue();
	t_end = clock();
	cout << "Max value in time " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec." << endl;
	t_start = clock();
	tree.count();
	t_end = clock();
	cout << "Count Elements: " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec." << endl;
	t_start = clock();
	tree.sum();
	t_end = clock();
	cout << "Sum Elements in " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec." << endl;
	cout << "AVG Elements: " << tree.avg() << endl;

	/*UniqueTree u_tree;
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
	cout << "AVG Elements: " << u_tree.avg() << endl;*/
#endif // BASE_CHECK
#ifdef DEPTH_CHECK
	Tree tree =
	{
				50,
		25,				75,
	16,     32,		 58,   85 ,
	8, 17, 31,  39,54, 60,83,90,53
	};
	tree.print();
	int value;
	/*cout << "Enter erase element: ";  cin >> value;
	tree.erase(value);
	tree.print();*/
	cout << "Depth: " << tree.depth() << endl;
	/*
	cout << "Enter element: "; cin >> value;
	cout << "Depth element" << " value : " << tree.depth(value) << endl;*/
	cout << "===============================" << endl;
	tree.tree_print();
#endif

}