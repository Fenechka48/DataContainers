//ForwardList
#include <iostream>
#define tab "\t"
#define delimeter   
using namespace std;

class Element
{
	int Data;      //значение элемента
	Element* pNext;  // адрес следующего элемента
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
	Element* Head; //голова списка,содержит указатель на нулевой элемен списка
public:
	ForwardList()
	{
		Head = nullptr; // если списсок пуст ,то его голова указывает на 0
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" <<this<< endl;
	}
	//             Adding elements:
	void push_front(int Data)
	{
		// 1.Создаем новый элемент
		Element* New = new Element(Data);
		//2. Новый элемент должен указываать на начало спеиска
		New->pNext = Head;
		//3. Голову списка "переводим" на новый элемент
		Head = New;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		//Создаем новый элемент
		Element* New = new Element(Data);
		//Доходим до конца списка
		Element* Temp = Head;
		while (Temp->pNext)
			Temp = Temp->pNext;
		//Добавляем элемент в конец списка
		Temp->pNext=New;

	}

	void pop_front(int Data) // удаляет элемент с начала списка
	{
		Element *Temp = Head;
		Head = Head->pNext;
		delete Temp;
	}
	//        Methods:
	void print()const
	{
		Element* Temp = Head; // Temp- это итератор
		//Итератор-это указатель . с помощью которого можно получить доступ
		//	к элементам структуры данных
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;// переход на следующий элемент
		}
	}

};


void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите размер списка: "; cin >> n;

	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand()%100);
	   
	}
	list.print();
	list.push_back(123);
	list.print();
	list.pop_front(1);
    list.print();
}