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
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this<< endl;
	}
	friend class ForwardList;
	friend class Iterator;
};
int Element::count = 0; //инициализируем статическую переменную объявленную внутри класса
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

	Iterator begin()
	{
		return Head;
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
	ForwardList operator+ (const ForwardList& left, const ForwardList& right)
	{
		//ForwardList cat(left.get_size() + right.get_size() - 1);
		//for (int i = 0; i < left.get_size(); i++)
		//	cat[i] = left[i];
		////cat.get_str()[i] = left.get_str()[i];
		//for (int i = 0; i < right.get_size(); i++)
		//	cat[i + left.get_size() - 1] = right[i];
		////cat.get_str()[i + left.get_size() - 1] = right.get_str()[i];
		//return cat;
	}
};
//#define BASE_CHECK
//#define RANGE_FOR_ARRAY

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

	ForwardList list2 = { 34,55,89 };
	for (int i : list2)cout << i << tab; cout << endl;

	ForwardList list3 = list + list2;                 // Move Constructor
	for (int i : list3) cout << i << tab; cout << endl;
}