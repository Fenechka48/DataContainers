//ForwardList
#include <iostream>
#define tab "\t"

using namespace std;

class Element
{
	int Data;      //значение элемента
	Element* pNext;// адрес следующего элемента
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "Destructor:\t" << this<< endl;
	}
	friend class ForwardList;
};
int Element::count = 0; //инициализируем статическую переменную объявленную внутри класса
class ForwardList
{
	Element* Head;//голова списка,содержит указатель на нулевой элемен списка
	int size;
public:
	ForwardList()
	{
		Head = nullptr;
		size = 0;// если списсок пуст ,то его голова указывает на 0
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" <<this<< endl;
	}
	int GetSize()
	{
		return size;
	}
	
	//             Adding elements:
	void push_front(int Data)
	{
		// 1.Создаем новый элемент
		//Element* New = new Element(Data);
		//2. Новый элемент должен указываать на начало спеиска
		//New->pNext = Head;
		//3. Голову списка "переводим" на новый элемент
		Head = new Element(Data,Head);
		size++;
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
		size++;

	}
	void insert(int Index, int Data)
	{
		if (Index == 0) return push_front(Data);
		if (Index>size) return;
		//1.создаем новый элемент
		Element* New = new Element(Data);
	    //2. доходим до нужного элемента
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
			Temp = Temp->pNext;
		New->pNext = Temp->pNext;
		Temp->pNext = New;
		size++;
	}

	void pop_front(int Data) // удаляет элемент с начала списка
	{
		Element *Temp = Head;
		Head = Head->pNext;
		delete Temp;
		size--;
	}
	void pop_back()  // удаляет элемент с конца списка
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext)
		{
			Temp=Temp->pNext;
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
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
		cout << "колличество элементов списка: " << size<< endl;
		cout << "общее колличество элементов списка " << size << endl;
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
	//cout << "Элементов в списке: " << list.GetSize() << endl;
	//list.push_back(123);
	//list.print();
	//list.pop_front(1);
    //list.print();
	//list.pop_back();
	//list.print();
	int value;
	int index;
	cout << "введите индекс добавляемого элемента: "; cin >> index;
	cout << "введите значение добавляемого элемента: "; cin >> value;
	list.insert(index, value);
	list.print();
	list.pop_back();
	list.print();

	ForwardList list2;
	list2.push_back(3);
	list2.push_back(5);
	list2.push_back(8);
	list2.print();
}