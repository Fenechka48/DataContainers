﻿#include <iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr)
			:Data(Data), pLeft(pLeft), pRight(pRight)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class Tree;
		friend class UniqueTree;
	}*Root;
public:
	Element* getRoot()
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
	void insert(int Data)
	{
		insert(Data, Root);
	}
	int minValue()const
	{
		return minValue(Root);
	}
	int maxValue()const
	{
		return maxValue(Root);
	}

	int Count()const
	{
		return Count(Root);
	}
	int Sum()const
	{
		return Sum(Root);
	}
	double Avg()
	{
		return (double)Sum(Root) / Count(Root);
	}
	int Depth()
	{
		return Depth(Root);
	}
	void print()const
	{
		print(Root);
		cout << endl;
	}
private:
	
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
	int minValue(Element* Root) const
	{
		if (Root == nullptr)return 0;
		/*if (Root->pLeft = nullptr) return Root->Data;
		return minValue(Root->pLeft);*/
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
	}
	int maxValue(Element* Root) const
	{
		if (Root == nullptr)return 0;
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}
	int Count(Element* Root) const
	{
		if (Root == nullptr)return 0;
		else return Count(Root->pLeft) + Count(Root->pRight) + 1;
	}
	int Sum(Element* Root) const
	{
		if (Root == nullptr)return 0;
		else return Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data;
	}
	double Avg() const
	{
		return (double)Sum(Root) / Count(Root);
	}
	int Depth(Element* Root) const
	{
		if (Root == nullptr)return 0;
		return
			Root==nullptr ? 0:
			Depth(Root->pLeft) + 1 >
			Depth(Root->pRight) + 1 ?
			Depth(Root->pLeft) + 1 :
			Depth(Root->pRight) + 1;
		/*if (Root == nullptr)return 0;
		if (Depth(Root->pLeft) + 1 > Depth(Root->pRight) + 1) return Depth(Root->pLeft);
		else return Depth(Root->pRight) + 1;*/
	}
	void print(Element* Root) const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << "\t";
		print(Root->pRight);
	}
};
class UniqueTree :public Tree
{
public:
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
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
};
void main()
{
	setlocale(LC_ALL, "");
	int n=1000;
	cout << "Введите размер дерева: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();
	cout << endl;
	cout << "Минимальное значение в дереве: " << tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue() << endl;
	cout << "Количество элементов дерева: " << tree.Count() << endl;
	cout << "Сумма элементов дерева: " << tree.Sum() << endl;
	cout << "Среднее арифметическое элементов: " << tree.Avg() << endl;
	cout << "Глубина дерева: " << tree.Depth() << endl;
	UniqueTree tree2;
	for (int i = 0; i < n; i++)
	{
		tree2.insert(rand() % 100, tree2.getRoot());
	}
	/*while (tree2.Count(tree2.getRoot()) < n)
	{
		tree2.insert(rand() % 100, tree2.getRoot());
	}*/
	tree2.print();
	cout << endl;
	cout << "Минимальное значение в дереве:  " << tree2.minValue() << endl;
	cout << "Максимальное значение в дереве: " << tree2.maxValue() << endl;
	cout << "Количество элементов дерева:" << tree2.Count() << endl;
	cout << "Сумма элементов дерева: " << tree2.Sum() << endl;
	cout << "Среднее арифметическое элементов: " << tree2.Avg() << endl;
	cout << "Глубина дерева: " << tree2.Depth() << endl;
}