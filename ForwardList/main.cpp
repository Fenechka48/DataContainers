//ForwardList
#include <iostream>
#define tab "\t"
using namespace std;
class Element
{
	int Data;      //�������� ��������
	Element* pNext;  // ����� ���������� ��������
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "Destructor:\t" << this<< endl;
	}
	friend class ForwardList;
};
class ForwardList
{
	Element* Head; //������ ������,�������� ��������� �� ������� ������ ������
public:
	ForwardList()
	{
		Head = nullptr; // ���� ������� ���� ,�� ��� ������ ��������� �� 0
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" <<this<< endl;
	}
	//             Adding elements:
	void push_front(int Data)
	{
		// 1.������� ����� �������
		Element* New = new Element(Data);
		//2. ����� ������� ������ ���������� �� ������ �������
		New->pNext = Head;
		//3. ������ ������ "���������" �� ����� �������
		Head = New;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		//������� ����� �������
		Element* New = new Element(Data);
		//������� �� ����� ������
		Element* Temp = Head;
		while (Temp->pNext)
			Temp = Temp->pNext;
		//��������� ������� � ����� ������
		Temp->pNext=New;
		
	}
	//        Methods:
	void print()const
	{
		Element* Temp = Head; // Temp- ��� ��������
		//��������-��� ��������� . � ������� �������� ����� �������� ������
		//	� ��������� ��������� ������
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;// ������� �� ��������� �������
		}
	}

};


void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "������� ������ ������: "; cin >> n;

	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//ist.push_front(rand() % 100);
		list.push_back(rand()%100);
	}
	list.print();
	list.push_back(123);
	list.print();
}