#include<iostream>
using namespace std;

	//Создавая структуру или класс мы создаем новый тип данных.
	//!!!	Класс - это тип данных		!!!
	//!!!	Структура - это тип данных	!!!
class Point
{
	double x;
	double y;
public:
	double get_x()const
	{
		return x;
	}
	double get_y()const
	{
		return y;
	}
	void set_x(double x)
	{
		this->x = x;
	}
	void set_y(double y)
	{
		this->y = y;
	}

	//					Constructors:
	/*Point()
	{
		x = y = 0;
		cout << "DefaultConstructor:\t" << this << endl;
	}
	Point(int x)
	{
		this->x = x;
		this->y = 0;
		cout << "Constructor:\t\t" << this << endl;
	}*/
	Point(double x=0, double y=0)
	{
		this->x = x;
		this->y = y;
		cout << "Constructor:\t\t" << this << endl;
	}
	~Point()
	{
		cout << "Destructor:\t\t" << this << endl;
	}

	//				Methods:
	void print()const
	{
		cout << "X = " << get_x() << "\tY = " << get_y() << endl;
	}
};

//#define STRUCT_POINT
//#define OBJECT_LIFETIME

void main()
{
	setlocale(LC_ALL, "");

#ifdef STRUCT_POINT
	int a;		//Объявление переменной 'a' типа 'int'
	Point A;	//Объявление переменной 'A' типа 'Point'
				//Создание объекта 'A' структуры 'Point'
				//Создание экземпляра 'A' структуры 'Point'
	A.x = 2;
	A.y = 3;
	cout << A.x << "\t" << A.y << endl;

	Point* pA = &A;
	cout << pA->x << "\t" << pA->y << endl;
#endif // STRUCT_POINT

	Point A;	//Здесь неявно вызывается конструктор по умолчанию,
				//поскольку мы создаем объект "По умолчанию"
	//A.set_x(2);
	//A.set_y(3);
	//cout << A.get_x() << "\t" << A.get_y() << endl;
	A.print();

	Point B = 5;
	//cout << B.get_x() << "\t" << B.get_y() << endl;
	B.print();

	Point C(7, 8);
	C.print();
	

#ifdef OBJECT_LIFETIME
	for (int i = 0; i < 10; i++)
	{
		cout << i << "\t";
	}
	//cout << i << endl;
	cout << endl;
#endif // OBJECT_LIFETIME

}

/*
-----------------------------------------------
.  - Оператор прямого доступа (Point operator)
	 Используется для получения доступа к полям объекта по имени объекта;
-> - Оператор косвенного доступа (Arrow operator)
	 Используется для получения доступа к полям объекта по адресу объекта;
-----------------------------------------------
*/

/*
-----------------------------------------------
Модификаты доступа:
	private:	закрытые поля, доступны только внутри класса;
	public:		открытые поля, доступны в любом месте программы;
	protected:	защищенные поля, доступны внутри класса, и его дочерних классов;
-----------------------------------------------
get/set-методы:
get (взять, получить) - открывают доступ к переменным членам класса на чтение,
						т.е., позволяют получить значения закрытых переменных;
set (задачть, установить)-открывают доступ к закрытым переменным членам класса
						на запись, т.е., позволяют задавать значения закрытых 
						переменных;
-----------------------------------------------
*/

/*
-----------------------------------------------
Constructor - это метод, который создает объект.
	-По умолчанию - это конструктор, который может быть вызван без параметров;
	-Без параметров;
	-С параметрами;
	-Конструктор копирования;
	-Конструктор переноса;
~Destructor - это метод, который уничтожает объект по завершении его времени жизни;
AssignmentOperator;
-----------------------------------------------
*/