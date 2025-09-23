#include<iostream>
using namespace std;

#define tab "\t"

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
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class Tree;
		friend class UTree;
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
	~Tree()
	{
		cout << "TDestructor:\t" << this << endl;
	}
	virtual void insert(int Data, Element* Root)
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
	int minValue(Element* Root)
	{
		return Root==nullptr? 0 : Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
		/*if (Root->pLeft == nullptr) return Root->Data;
		else return minValue(Root->pLeft);*/
	}
	int maxValue(Element* Root)
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
	double sum(Element* Root)const
	{
		return !Root ? 0 : sum(Root->pLeft) + sum(Root->pRight) + Root->Data;
	}
	
	double avg(Element* Root)const
	{
		return sum(Root) / count(Root);
	}
	void clear(Element* Root)
	{
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
		this->Root = nullptr;
	}
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
};
class UTree :public Tree
{
public:
	bool unique(int Data, Element* Root)const
	{
		/*if (Root == nullptr)return;
		unique(Data, Root->pLeft);
		unique(Data, Root->pRight);*/
		return !Root ? 0 : Root->Data == Data ? 1 : count(Root->pLeft)+ count(Root->pRight);
	}
	void insert(int Data, Element* Root)override 
	{
		if (unique(Data, Root))return;
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

};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Enter count elements: "; cin >> n;
	cout << "Hello Tree" << endl;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100, tree.getroot());
	}
	tree.print(tree.getroot());
	cout << endl;
	cout<<"Min value ---> "<<tree.minValue(tree.getroot())<<endl;
	cout<<"Max value ---> "<<tree.maxValue(tree.getroot())<<endl;
	cout << "Count Elements: " << tree.count(tree.getroot()) << endl;
	cout << "sum Elements: " << tree.sum(tree.getroot()) << endl;
	cout << "avg Elements: " << tree.avg(tree.getroot()) << endl;
	tree.clear(tree.getroot());
	cout << "-------" << endl;
	tree.print(tree.getroot());

	UTree utree;
	utree.print(utree.getroot());
	utree.insert(34, utree.getroot());
	for (int i = 0; i < n; i++)
	{
		utree.insert(rand() % 100, utree.getroot());
	}

	utree.print(utree.getroot());

}