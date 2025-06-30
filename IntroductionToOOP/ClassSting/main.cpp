#include<Windows.h>
#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define delimiter "\n------------------------------------\n"

class String
{
	int size;	//Размер строки в Байтах
	char* str;	//Указатель на строку в динамической памяти
public:
	int get_size()const
	{
		return size;
	}
	const char* get_str()const
	{
		return str;
	}
	char* get_str()
	{
		return str;
	}

	//				Constructors:
	explicit String(int size = 80)
	{
		this->size = size;
		this->str = new char[size] {};
#ifdef DEBUG
		cout << "DefaultConstructor:\t" << this << endl;
#endif // DEBUG
	}
	String(const char str[])
	{
		size = 0;
		while (str[size++]);
		this->str = new char[size] {};
		for (int i = 0; str[i]; i++)this->str[i] = str[i];
#ifdef DEBUG
		cout << "Constructor:\t\t" << this << endl;
#endif // DEBUG
	}
	String(const String& other)
	{
		//Конструктор копирования дожлен выполнять DeepCopy (Побитовое копирование),
		//т.е. выделять динамическую память под объект и побитово (поэлементно)
		//копировать содержимое динамической памяти из существующего объекта в создаваемый.
		this->size = other.size;
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)this->str[i] = other.str[i];
#ifdef DEBUG
		cout << "CopyConstructor:\t" << this << endl;
#endif // DEBUG
	}
	String(String&& other)
	{
		this->size = other.size;
		this->str = other.str;
		other.size = 0;
		other.str = nullptr;	//Защищаем память от удаления деструктором.
#ifdef DEBUG
		cout << "MoveConstructor:\t" << this << endl;
#endif // DEBUG

	}
	~String()
	{
		delete[] str;
		this->str = nullptr;
		this->size = 0;
#ifdef DEBUG
		cout << "Destructor:\t\t" << this << endl;
#endif // DEBUG
	}

	//				Operators:
	String& operator=(const String& other)
	{
		if (this == &other)return *this;
		delete[] this->str;
		this->size = other.size;
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)this->str[i] = other.str[i];
#ifdef DEBUG
		cout << "CopyAssignment:\t\t" << this << endl;
#endif // DEBUG
		return *this;
	}
	String& operator=(String&& other)
	{
		if (this == &other)return *this;
		delete[] this->str;
		this->size = other.size;
		this->str = other.str;
		other.size = 0;
		other.str = nullptr;
#ifdef DEBUG
		cout << "MoveAssignment:\t\t" << this << endl;
#endif // DEBUG

		return *this;
	}
	char operator[](int i)const
	{
		return str[i];
	}
	char& operator[](int i)
	{
		return str[i];
	}

	//				Methods:
	void info()const
	{
		cout << "Size:\t" << size << endl;
		cout << "Str:\t" << str << endl;
	}
};

String operator+(const String& left, const String& right)
{
	String result(left.get_size() + right.get_size() - 1);	//Default constructor
	for (int i = 0; left.get_str()[i]; i++)
		//result.get_str()[i] = left.get_str()[i];
		result[i] = left[i];
	for (int i = 0; right.get_str()[i]; i++)
		//result.get_str()[left.get_size() - 1 + i] = right.get_str()[i];
		result[left.get_size() - 1 + i] = right[i];
	cout << "Operator+" << endl;
	return result;
}

std::ostream& operator<<(std::ostream& os, const String& obj)
{
	return os << obj.get_str();
}
std::istream& operator>>(std::istream& cin, String& obj)
{
	const int SIZE = 1024;	//Размер буфера - 1kB
	char buffer[SIZE] = {};
	cin >> buffer;
	obj = buffer;
	return cin;
}
std::istream& getline(std::istream& cin, String& obj)
{
	cin.getline(obj.get_str(), obj.get_size());
	return cin;
}

//#define CONSTRUCTORS_CHECK
//#define OPERATOR_PLUS
//#define ISTREAM_OPERATOR
#define PERFORMANCE_TEST

void main()
{
	setlocale(LC_ALL, "");

#ifdef CONSTRUCTORS_CHECK
	String str1(5);	//explicit-конструктор нельзя вызвать оператором '=', но всегда можно вызвать при помощи круглых скобок
	str1.info();
	cout << str1 << endl;

	String str2 = "Hello";
	str2 = str2;
	cout << str2 << endl;

	String str3 = str2;		//CopyConstructor
	cout << str3 << endl;

	String str4;
	str4 = str3;
	cout << str4 << endl;
#endif // CONSTRUCTORS_CHECK

#ifdef OPERATOR_PLUS
	String str1 = "Hello";
	String str2 = "World";
	cout << delimiter << endl;
	String str3;
	str3 = str1 + str2;
	cout << delimiter << endl;
	cout << str3 << endl;
	//MoveSemantic
#endif // OPERATOR_PLUS

#ifdef ISTREAM_OPERATOR
	String str;
	cout << "Введите строку: ";
	SetConsoleCP(1251);
	//cin >> str;
	//cin.getline(str.get_str(), str.get_size());
	getline(cin, str);
	SetConsoleCP(866);
	cout << str << endl;
#endif // ISTREAM_OPERATOR

	String text = R"(When a return statement contains an expression of non-primitive type, its execution copies the expression result into the return slot of the calling function. The compiler invokes the copy or move constructor of the returned type. Then, as the function is exited, destructors for function-local variables are called, which includes any variables named in the expression.
		The C++ standard allows(but doesn't require) the compiler to optionally construct the returned object directly in the return slot of the calling function. This construction skips (or elides) the copy or move constructor executed as part of the return statement. Unlike most other optimizations, this transformation is allowed to have an observable effect on the program's output.Namely, the copy or move constructor and associated destructor are called one less time.The standard still requires that the named returned variable has a defined copy or move constructor, even if the compiler elides the constructor in all cases.
			In versions before Visual Studio 2022 version 17.4, when optimizations are disabled(such as under / Od or in functions marked #pragma optimize("", off)) the compiler only performs mandatory copy and move elision.Under / O2, the older compilers perform optional copy or move elision on return of a named variable in an optimized function when all of these conditions are met : it has no loops or exception handling, it doesn't return multiple symbols with overlapping lifetimes, the type's copy or move constructor doesn't have default arguments.
			Visual Studio 2022 version 17.4 increases the number of places where the compiler does optional copy or move elisions under / Zc : nrvo, whether enabled explicitly, or automatically by using the / O2, / permissive - , or /std : c++20 or later options.Under / Zc : nrvo, the compiler performs optional copy or move elision on return of a named variable for any function when : it has no loops or exception handling(as before); it returns the variable from a loop; it has exception handling; the returned type's copy or move constructor has default arguments. Optional copy or move elisions are never done when /Zc:nrvo- is applied, or when the function returns multiple symbols with overlapping lifetimes, or for a throw of a named variable.)";
	cout << text.get_size() << endl;

	const int SIZE = 100000;
	String arr[SIZE]{};
	String get_text(const String & other);
	for (int i = 0; i < SIZE; i++)
	{
		arr[i] = get_text(text);
	}
	cout << "DONE" << endl;
}

String get_text(const String& other)
{
	String local = other;
	return local;
}

/*
---------------------------------
C++11 MoveSemantic:
MoveConstructor - Конструктор переноса;
MoveAssignment  - Переносящий оператор присваивания;
Move-методы принимают r-value reference: Class&&
CopyConstructor,CopyAssignment - DeepCopy		(Побитовое копирование);
MoveConstrcutor,MoveAssignment - ShallowCopy	(Поверхностное копирование);
---------------------------------
*/