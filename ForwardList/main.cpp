//ForwardList
#include <iostream>
#define tab "\t"

using namespace std;
using std::cin;
using std::cout;
using std::endl;

class FordwardList;
FordwardList operator+(const FordwardList& left, const FordwardList& right);

class Element
{
	int Data;      //значение элемента
	Element* pNext;// адрес следующего элемента
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

	}
	~Element()
	{
		count--;
#ifdef DEBUG

		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

	}
	friend class ForwardList;
	friend class Iterator;
	friend ConstIterator;
};
int Element::count = 0; //инициализируем статическую переменную объявленную внутри класса

class ConstIterator
{
	Element* Temp;
public:
	ConstIterator(Element* Temp = nullptr) :Temp(Temp)
	{
#ifdef DEBUG
		cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG
	}
	~ConstIterator()
	{
#ifdef DEBUG
		cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG
	}

	ConstIterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}

	bool operator==(const ConstIterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const ConstIterator& other)const
	{
		return this->Temp != other.Temp;
	}
	const int& operator*()const
	{
		return Temp->Data;
	}
};


class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr) :Temp(Temp)
	{
#ifdef DEBUG

		cout << "ItConstructor:\t" << this << endl;

#endif // DEBUG

	}
	~Iterator()
	{
#ifdef DEBUG

		cout << "ItDestructor:\t" << this << endl;

#endif // DEBUG

	}
	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	bool operator ==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator !=(const Iterator& other) const
	{
		return this -> Temp != other.Temp;
	}
	int& operator*()
	{
		return Temp->Data;
	}
};



class ForwardList
{
	Element* Head;//голова списка,содержит указатель на нулевой элемен списка
	int size;
public:
	ConstIterator cbegin()const
	{
		return Head;
	}
	Iterator begin()const
	{
		return Head;
	}
	Iterator end()const
	{
		return nullptr;
	}
	ConstIterator cend()const
	{
		return nullptr;
	}
	Iterator end()
	{
		return nullptr;
	}
	ForwardList()
	{
		Head = nullptr;
		size = 0;// если списсок пуст ,то его голова указывает на 0
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList (const std::initializer_list<int>& il):ForwardList()
	{
		//initializer_list-il- это контейнер.Контейнер-это объект который организует хранение других объектов в памяти
		cout << typeid(il.begin()).name() << endl;
		for(int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	ForwardList (const ForwardList& other)
	{
		//Shallow copy:
		cout << "CopyConstructor:\t" << endl;
	}

	ForwardList (ForwardList&& other)noexcept
	{
		//Shallow copy:
		this->size = other.size;
		this->Head = other.Head;
		other.size = 0;
		other.Head = nullptr;
		cout << "MoveConstructor:\t" << this << endl;
	}

	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" <<this<< endl;
	}
	int get_size()
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
		//Element* New = new Element(Data);
		//Доходим до конца списка
		Element* Temp = Head;
		while (Temp->pNext)
			  Temp = Temp->pNext;
		//Добавляем элемент в конец списка
		Temp->pNext=new Element(Data);
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
	void erase(int Index,int Data)
	{
		if (Index == 0) return pop_front();
		if (Index > size) return;
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
			Temp = Temp->pNext;
		Element* buffer = Temp->pNext;
		Temp->pNext = buffer->pNext;
		delete buffer;
		size--;
	}

	void pop_front() // удаляет элемент с начала списка
	{
		Element *Temp = Head;
		Head = Head->pNext;
		delete Temp;
		size--;
	}
	void pop_back(int Index, int Data)  // удаляет элемент с конца списка
	{
		/*Element* Temp = Head;
		while (Temp->pNext->pNext)
		{
			Temp=Temp->pNext;
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;*/
		erase(size - 1,Data);
		size--;
	}
	


	//        Methods:
	void reverse()
	{
		ForwardList buffer;
		while (Head)
		{
			buffer.push_front(Head->Data);	//Начальный элемент добавляет в начало буфера
			pop_front();	//удаляем начальный элемент из исходного списка
		}
		Head = buffer.Head;
		buffer.Head = nullptr;
	}
	void print()const
	{
		Element* Temp = Head; // Temp- это итератор
		//Итератор-это указатель . с помощью которого можно получить доступ
		//	к элементам структуры данных
		//while (Temp)
		//{
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//	Temp = Temp->pNext;// переход на следующий элемент
		//}
		for (Element*Temp=Head;Temp;Temp=Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;

		cout << "колличество элементов списка: " << size<< endl;
		cout << "общее колличество элементов списка " << size << endl;
	}
	
};
ForwardList operator+ (const ForwardList& left, const ForwardList& right)
{
	ForwardList cat;
	for (ConstIterator it = left.cbegin(); it != left.cend(); ++it)	cat.push_back((*it) *= 10);
	for (ConstIterator it = right.cbegin(); it != right.cend(); ++it)	cat.push_back(*it);
	return cat;
}
//#define BASE_CHECK
//#define RANGE_FOR_ARRAY
//#define RANGE_BASED_FOR_LIST
#define HOME_WORK_1
//#define PREFORMANCE_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;

	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
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
	list.pop_back(index, value);
	list.print();

	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index, value);
	list.print();

	//ForwardList list2;
	//list2.push_back(3);
	//list2.push_back(5);
	//list2.push_back(8);
	//list2.print();  
#endif // BASE_CHECK
#ifdef RANGE_FOR_ARRAY
	int arr[] = { 3,5,8,13,21 };
	/*for (int i = 0; i < sizeof(arr)/sizeof(int); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;*/

	// Range-based for loops
	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_FOR_ARRAY

	ForwardList list = { 3,5,8,13,21 };
	//list.print();
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
#ifdef RANGE_BASED_FOR_LIST

	ForwardList list2 = { 34,55,89 };
	for (int i : list2)cout << i << tab; cout << endl;

#endif // RANGE_BASED_FOR_LIST

#ifdef HOME_WORK_1
	ForwardList list = { 3, 5, 8, 13, 21 };
	//list.print();
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;

	ForwardList list2 = { 34, 55, 89 };
	for (int i : list2)cout << i << tab; cout << endl;

	ForwardList list3 = list + list2;
	for (int i : list3)cout << i << tab; cout << endl;

	for (int i : list)cout << i << tab; cout << endl;
#endif // HOME_WORK_1

#ifdef PREFORMANCE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	cout << "Список заполнен" << endl;
	ForwardList list2 = list;
	//for (int i : list)cout << i << tab; cout << endl;
	//for (int i : list2)cout << i << tab; cout << endl;  
#endif // PREFORMANCE_CHECK
}