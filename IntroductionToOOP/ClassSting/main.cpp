#include<iostream>
using namespace std;

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

	//								Constructors:
	explicit String(int size = 80)
	{
		this->size = size;
		this->str = new char[size] {};
		cout << "DefaultConstructor:\t" << this << endl;
	}
	String(const char str[])
	{
		while (str[size++]);
		this->str = new char[size] {};
		for (int i = 0; str[i]; i++)this->str[i] = str[i];
		cout << "Constructor:\t\t" << this << endl;
	}
	String(const String& other)
	{
		//Конструктор копирования должен DeepCopy(Побитовое копирование)
		//т.е. выделять динамическую память под обьект и побитово (поэлементно)
		//копировать содержимое динамической памяти из существующего обьекта в создаваемый
		this->size = other.size;
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)this->str[i] = other.str[i];
	}
	~String()
	{
		delete[] str;
		this->str = nullptr;
		this->size = 0;
		cout << "Destructor:\t\t" << this << endl;
	}
	//								Operators:
	String& operator=(const String& other)
	{
		if (this== &other)return *this;
		delete[] this->str;
		this->size = other.size;
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)this->str[i] = other.str[i];
		cout << "CopyAssignment\t\t" << this << endl;
	}

	//									Methods:
	void info()const
	{
		cout << "Size:\t" << size << endl;
		cout << "Str:\t" << str << endl;
	}
};

std::ostream& operator<<(std::ostream& os, const String& obj)
{
	return os << obj.get_str();
}

void main()
{
	setlocale(LC_ALL, "");
	String str1(5);	//explicit-конструктор нельзя вызвать оператором присвоить, но всегда можно вызвать при помощи круглых скобок
	str1.info();
	cout << str1 << endl;

	String str2 = "Hello";
	cout << str2 << endl;

	String str3 = str2;		//CopyConstructor
	cout << str3 << endl;

	String str4;
	str4 = str3;
	cout << str4 << endl;
}