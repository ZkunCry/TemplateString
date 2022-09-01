//Template Class String and Iterators by Eugene
#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string.h>
#include <typeinfo>
#include <fstream>
#include "iterators.h"
using namespace std;


template<typename T>
class Iterator;
template<typename T>
class Reverse_Iterator;

enum Errors
{
	SIZE,
	OUT_OF_RANGE,
	SMALL_NUM
};
class Exception // Abstract exception class(Base Class)
{
protected:
	size_t num;
	char* str;
public:
	virtual void display() = 0; //Virtual abstract method
};

template<typename T>
class String
{

private:
	using pointer_str = T*;
	//Class string fields
	pointer_str str;
	size_t size;
	void assignment(char* pc, const String& other);
	//helper method

	class ExceptionStr :public Exception //Derived class
	{
	public:
		ExceptionStr(size_t Num, const char* string);
		void display()override;
	};


public:
	//Classes Iterators
	typedef Iterator<T> iterator;
	typedef Iterator<const T> const_iterator;
	typedef Reverse_Iterator<T> reverse_iterator;
	typedef Reverse_Iterator<const T> const_reverse_iterator;
	//////
	//  
	//String Constructors and Destructor
	static const int Npos = -1;
	String(const String& other);
	String(String&& other) noexcept; //Move konstructor
	String();
	String(const char* str);
	String(char symbol);
	String(size_t n, char symbol);
	String(int n);
	String(const String& other, size_t pos, size_t count);
	String(const char* ps, size_t count);
	~String()noexcept;
	/////////

	//Operator overloading

	template< typename T2>
	String& To_string(T2 n);
	T& operator()(int i);
	const T& operator[](size_t index)const;
	T& operator[](size_t index);
	const bool operator!=(const String& other)const;
	const bool operator==(const String& other)const;
	String& operator =(const String& other);
	String& operator =(const char* s);
	String& operator =(char c);
	String operator+(const String<T>& other);
	String operator+(size_t number);
	template<typename T>
	friend String operator+(const String& lhs, const char* rhs);
	template<typename T>
	friend String operator+(const String& lhs, const String& rhs);
	const bool operator>(const String& other)const;
	constexpr bool operator<(const String& other)const;
	bool operator>=(const String& other);
	bool operator<=(const String& other);
	template<typename T>
	friend String& operator+=(String& left, const String& right);
	template<typename T>
	friend String& operator+=(String& left, const char symbol);
	template<typename T>
	friend std::ostream& operator<<(std::ostream& out, const String<T>& other);
	template<typename T>
	friend std::istream& operator>>(std::istream& is, String<T>& str);
	/////////////////////////////////////////////

	//Methods for working with strings////
	const char* c_str() const;
	String& Resize(int n);
	String& Resize(short int n, char symbol);
	String SubStr(size_t pos = 0, int count = Npos)const;
	String& Push_back(const char c);
	String& pop_back();
	String& Push_front(const char c);
	String& Pop_front();
	String& Erase(int position);
	String& Erase(size_t index = 0, size_t num = 0);
	void isClear();
	String& lower(size_t start, size_t end);
	String& upper(size_t start, size_t end);
	size_t find(char symbol, size_t position = 0);
	size_t find(const char*  str);
	size_t find(const char* const str, size_t pos = Npos);
	size_t find(const char* const str, size_t pos, size_t n);
	size_t rfind(const char* str, size_t pos = Npos);
	String& append(const String& other, size_t start);
	String& append(const char* other, size_t num);
	String& append(const String& other, size_t start, size_t end);
	String& append(const String& str);
	String& append(size_t n, char c);
	String& insert(size_t num, const char* str);
	String& assign(const String<T>& str);
	String& assign(const String& s, size_t st, size_t num);
	String& assign(const char* ps, size_t st, size_t num);
	String& assign(const char* ps, size_t n);
	String& assign(size_t n, char c);
	String& Replace(size_t pos, size_t len, const String& str);
	String& Replace(size_t pos, size_t len, const char* s);
	String& Replace(size_t pos, size_t len, size_t n, char c);
	String& Replace(const_iterator it1,const_iterator it2,const char *pc);
	size_t Size()const;
	String& reverse();
	const String GetStr()const;
	bool isEmpty();
	void swap(String& str);
	char& at(size_t pos);
	int compare(size_t start, size_t num, const String& s) const;
	int compare(size_t start, size_t num, const char* s) const;
	int compare(const String& s) const noexcept;
	int compare(const char *s) const;
	void readfile(const char *nameF);
	void writefile(const char* nameF);
	//Functions that return a reference to the first and last object of a string
	constexpr char& front();
	const char& back();
	//Class Iterator methods
	iterator begin()const;
	iterator end()const;
	const_iterator cbegin()const;
	const_iterator cend()const;
	reverse_iterator rbegin()const;
	reverse_iterator rend()const;
	const_reverse_iterator rcbegin()const;
	const_reverse_iterator rcend()const;
};

using sstring = String<char>; // This typedef is needed in order not to write many times String<char> and Iterators<char>
template<typename T>
inline String<T>::iterator String<T>::begin()const
{
	return iterator(str);
}
template<typename T>
inline String<T>::iterator String<T>::end()const
{
	return iterator(str + size);
}
//Const_reverse iterator
template<typename T>
inline String<T>::const_reverse_iterator String<T>::rcbegin() const
{
	return const_reverse_iterator(str + size - 1);
}
template<typename T>
inline String<T>::const_reverse_iterator String<T>::rcend() const
{
	return const_reverse_iterator(str - 1);
}
template<typename T>
String<T>::const_iterator String<T>::cbegin()const
{
	return const_iterator(str);
}
template<typename T>
String<T>::const_iterator String<T>::cend() const
{
	return const_iterator(str + size);
}
/////////
//Derived Class ExceptionStr
template<typename T>
inline String<T>::ExceptionStr::ExceptionStr(size_t Num, const char* string)
{
	this->num = Num;
	str = new char[strlen(string) + 1];
	strncpy(str, string, strlen(string));
	str[strlen(string)] = '\0';
}
template<typename T>
void String<T>::ExceptionStr::display()
{
	std::cout << "Exception! - # " << num << " " << str << std::endl;
}
//////////
/// Class Iterator(Const) and Reverse Iterator


template<typename T>
inline String<T>::reverse_iterator String<T>::rbegin() const
{
	return reverse_iterator(str + size - 1);
}
template<typename T>
inline String<T>::reverse_iterator String<T>::rend() const
{
	return reverse_iterator(str-1);
}


///////////////////////////////////////


/////////////////TemplateClass String///////////////////
template<typename T>
inline String<T>::String(const char* ps, size_t count)
{
	this->str = new T[count + 1];
	size = count;
	strncpy(str, ps, size);
	str[size] = 0;
}
template<typename T>
inline String<T>::String(const String& other, size_t pos, size_t count)
{
	this->str = new T[count - pos+1];
	this->size = count - pos;
	strncpy(str, other.str, size);
	str[size] = 0;
}
template<typename T>
String<T>::String()
{
	this->str = new T[1];
	this->size = 0;
	this->str[0] = '\0';
}
template<typename T>
String<T>::String(const char* str)
{
	size = strlen(str);
	this->str = new T[size + 1];
	strncpy(this->str, str, size);
	this->str[size] = '\0';
}
template<typename T>
String<T>::String(const String<T>& other) :String(other.str) {}
template<typename T>
String<T>::String(String<T>&& other)noexcept :String()
{
	swap(other);
}
template<typename T>
String<T>::String(char symbol)
{
	this->str = new T[2];
	this->str[0] = symbol;
	this->str[1] = '\0';
	this->size = 1;
}
template<typename T>
String<T>::String(size_t n, char symbol)
{
	this->str = new T[n + 1];
	for (int i = 0; i < n; i++)
	{
		this->str[i] = symbol;
	}
	this->str[n] = '\0';
	this->size = strlen(this->str);
}
template<typename T>
String<T>::String(int n)
{
	String::To_String(n);
}
template<typename T>
String<T>::~String() noexcept
{
	if (str != nullptr)
	{
		delete[]this->str;
		this->size = 0;
	}
}
//String Size Method
template<typename T>
size_t String<T>::Size()const
{
	return strlen(str);
}
template<typename T>
String<T> String<T>::operator+(const String<T>& other)
{
	String s;
	size_t count = strlen(this->str) + strlen(other.str);
	s.str = new T[count + 1];
	s.size = count;
	int i = 0;
	for (; i < size; i++)
		s[i] = this->str[i];
	for (int j = 0; j < other.size; j++, i++)
		s[i] = other[j];
	s.str[count] = '\0';
	s.size = count;
	return s;
}
//Overloading ()
template<typename T>
inline T& String<T>::operator()(int i)
{
	return (str[i]);
}
template<typename T>
inline const T& String<T>::operator[](size_t index) const
{
	return str[index];
}
template<typename T>
inline T& String<T>::operator[](size_t index)
{
	return this->str[index];
}
template<typename T>
String<T>& String<T>::Replace(size_t pos, size_t len, const String<T>& str)
{
	if (len > Size())
		len = Size();
	String::Erase(pos, len);
	String::insert(pos, str.str);
	return *this;
}
template<typename T>
String<T>& String<T>::Replace(size_t pos, size_t len, const char* s)
{
	String str(s);
	String::Replace(pos, len, str);
	return *this;
}
template<typename T>
String<T>& String<T>::Replace(size_t pos, size_t len, size_t n, char c)
{
	String str(n, c);
	String::Replace(pos, len, str);
	return *this;
}
template<typename T>
inline String<T>& String<T>::Replace(const_iterator it1, const_iterator it2, const char* pc)
{
	String str(pc);
	int pos = String::find(*it1);
	int len = String::find(*it2);
	String::Replace(pos, len, str);
	return *this;
}
//Overloading Binary Operators
template<typename T>
String<T>& operator+=(String<T>& left, const String<T>& right)
{
	left = left + right;
	return left;
}
template<typename T>
inline String<T>& operator+=(String<T>& left, const char symbol)
{
	left.Push_back(symbol);
	return left;
}
template<typename T>
inline String<T> operator+(const String<T>& lhs, const char* rhs)
{
	String<T> temp(rhs);
	temp = lhs + temp;
	return temp;
}
template<typename T>
inline String<T> operator+(const String<T>& lhs, const String<T>& rhs)
{
	String<T> temp(lhs);
	temp = temp + rhs;
	return temp;
}
//Overloaded Comparison Operators
template<typename T>
inline const bool String<T>::operator>(const String<T>& other)const
{
	return size > other.size;
}
template<typename T>
inline constexpr bool String<T>::operator<(const String<T>& other)const
{
	return size < other.size;
}
template<typename T>
inline bool String<T>::operator>=(const String<T>& other)
{
	return strcmp(this->str, other.str) == 0 || strcmp(this->str, other.str) == 1;
}
template<typename T>
inline bool String<T>::operator<=(const String<T>& other)
{
	return strcmp(this->str, other.str) == 0 || strcmp(this->str, other.str) == -1;
}
template<typename T>
inline const bool String<T>::operator==(const String<T>& other)const
{
	return strcmp(this->str, other.str) == 0;
}
template<typename T>
inline const bool String<T>::operator!=(const String<T>& other)const
{
	return strcmp(this->str, other.str) < 0 || strcmp(this->str, other.str) > 0;
}

template<typename T>
String<T>& String<T>::operator =(const String<T>& other)
{
	if (this->str != nullptr)
		delete[] this->str;
	this->size = strlen(other.str);
	this->str = new T[size + 1];
	strncpy(str, other.str, size);
	this->str[size] = '\0';
	return *this;
}
template<typename T>
String<T>& String<T>::operator=(const char* s)
{
	if (this->str != nullptr)
		delete[]this->str;
	size = strlen(s);
	str = new T[size + 1];
	strncpy(str, s, size);
	str[size] = '\0';
	return *this;
}
template<typename T>
String<T>& String<T>::operator=(char c)
{
	delete[]this->str;
	size = 1;
	str = new T[size + 1];
	str[size - 1] = c;
	str[size] = '\0';
	return *this;
}


//Overloaded summation operator (concatenation)


template<typename T>
inline String<T> String<T>::operator+(size_t number)
{
	return this->str + number;
}

//Formation of a string in the style of C (char)
template<typename T>
inline const char* String<T>::c_str() const
{
	return this->str;
}
template<typename T>
inline void String<T>::assignment(char* pc, const String<T>& other)
{
	for (int i = 0; i < size; i++)
		pc[i] = other[i];
	pc[size] = '\0';
}
//Getting a reference to the first element of a string
template<typename T>
inline constexpr char& String<T>::front()
{
	if (size != 0 && str != nullptr)
		return this->str[0];

}
//Compare string
template<typename T>
inline int String<T>::compare(size_t start, size_t num, const String<T>& s) const
{
	const String& temp = String::SubStr(start, num);
	return (temp == s) == 0;
}
template<typename T>
inline int String<T>::compare(size_t start, size_t num, const char* s) const
{
	String stemp(s);
	int BOOL = String::compare(start, num, stemp);
	if (BOOL == 1)
		return 0;
}
template<typename T>
inline int String<T>::compare(const String& s) const noexcept
{
	return (String(this->str) == s) == 0;
}
template<typename T>
inline int String<T>::compare(const char* s) const
{
	return strcmp(this->str, s) == 0;
}
//Returning a reference to an element of a string
template<typename T>
inline char& String<T>::at(size_t pos)
{
	try
	{
		if (pos > size)
			throw ExceptionStr(OUT_OF_RANGE, "Error!Out of Range\n");
		return this->str[pos];
	}
	catch(ExceptionStr exp)
	{
		exp.display();
	}
}
//The function changes the contents of the strings
template<typename T>
void String<T>::swap(String<T>& str)
{
	std::swap(size, str.size);
	char *pc = move(str.str);
	str.str = move(this->str);
	this->str = pc;
}
//String resize
template<typename T>
String<T>& String<T>::Resize(int n)
{
	try
	{
		if (n < 0 || this->str == nullptr)
			throw ExceptionStr(SMALL_NUM, "Your number is smaller null!\n");
		String TempStr;
		int OrigSize = this->size, count = size;
		TempStr.str = new T[n + 1]; //Allocating memory for a temporary string that will store the result
		TempStr.size = n; //Assigning a new size to the original string
		TempStr[n] = '\0'; // Add zero at the end of the line
		if (n < size)
			strncpy(TempStr.str, str, n);
		else
		{
			strncpy(TempStr.str, str, size);
			while (TempStr[count] != '\0') //Filling the selected cells of the array with emptiness (it is necessary so that garbage values are not displayed)
			{
				TempStr[count] = ' ';
				count++; //Increasing the index
			}
		}
		delete[]this->str; /*We clear the memory in order to later change the size of the string when memory is allocated*/
		this->size = n; //Assign a new size
		this->str = new T[size + 1]; //Allocate new memory
		strncpy(str, TempStr.str, size);
		this->str[size] = '\0';
		return *this; // We return as a result the object that needed to be changed
	}
	catch (ExceptionStr exp)
	{
		exp.display();
		return *this;
	}
}
//Overloaded String Size Remapping Method
template<typename T>
String<T>& String<T>::Resize(short int n, char symbol)
{
	if (this->str != nullptr && n > size)
	{
		String TempStr;
		int size = strlen(this->str);
		size_t temp = (strlen(this->str) + abs(size - n) + 1);
		int j = 0, count = 0;
		TempStr.str = new T[temp];
		TempStr.size = temp;
		for (int i = 0; i < temp - 1; i++)
		{
			if (i >= strlen(this->str))
				TempStr[i] = symbol;
			else
				TempStr[i] = this->str[i];
		}
		TempStr[temp - 1] = '\0';
		delete[]this->str;
		this->size = strlen(TempStr.str);
		this->str = new T[size + 1];
		for (int j = 0; TempStr[j] != '\0'; j++)
		{
			this->str[j] = TempStr[j];
		}
		this->str[size] = '\0';
		return *this;
	}
	else
	{
		String::Resize(n);
		return *this;
	}
}
//Method for inserting a character at the end of a string
template<typename T>
String<T>& String<T>::Push_back(const char c)
{
	if (this->str != nullptr)
	{
		String TempStr;
		size_t n = this->size + 1;
		TempStr.str = new T[this->size + 2];
		for (int i = 0; i < this->size + 1; i++)
		{
			if (i == n - 1)
				TempStr[i] = c;
			else
				TempStr[i] = this->str[i];
		}
		TempStr.str[n] = '\0';
		delete[]this->str;
		this->size = n;
		this->str = new T[n + 2];
		for (int i = 0; TempStr[i] != '\0'; i++)
		{
			this->str[i] = TempStr[i];
		}
		this->str[n] = '\0';
		return *this;
	}
}
//Removing an element at the end of a line
template<typename T>
String<T>& String<T>::pop_back()
{
	try
	{
		if (this->size == 0)
			throw ExceptionStr(SIZE, "Your string size = 0!");
	}
	catch (ExceptionStr exp)
	{
		exp.display();
		return *this;
	}
	if (this->size != 0 )
	{
		size_t size = this->size - 1;
		char* pc = new T[size + 1];
		for (int i = 0; i < size; i++)
			pc[i] = str[i];
		pc[size] = '\0';
		delete[]str;
		str = new T[size + 1];
		strncpy(str, pc, size);
		str[size] = '\0';
		size = size;
		return *this;
	}
}
template<typename T>
String<T>& String<T>::Push_front(const char c)
{
	String temp(c);
	String result(this->str);
	temp += result;
	delete[]str;
	str = new T[temp.size + 1];
	for (int i = 0; i < temp.size; i++)
		str[i] = temp[i];
	size = temp.size;
	str[temp.size] = '\0';
	return *this;

}
template<typename T>
String<T>& String<T>::Pop_front()
{
	try
	{
		if (this->size == 0 || str == nullptr)
			throw ExceptionStr(SIZE, "Your size string is smaller 0 or = 0\n");
		String result(this->str);
		result.size = size;
		delete[]this->str;
		str = new T[size];
		for (int i = 0, j = 1; i < size; i++, j++)
			str[i] = result[j];
		size = result.size - 1;
		str[size] = '\0';
		return *this;
	}
	catch (ExceptionStr ex)
	{
		ex.display();
		return *this;
	}
}
//returns a substring of the given string starting at the character at index pos count
//count or to the end of the string if pos + count > S.size().
template<typename T>
String<T> String<T>::SubStr(size_t pos, int count)const
{
	/*If the number of characters to be copied, starting from pos, exceeds the length of the original string,
	then in this case you will need to copy from pos to the end of the line
	If the number of characters to be copied, starting from pos, does not exceed the length of the original string,
	Then the string is copied from pos to count*/

	if(pos <size  || count == Npos ||pos >0 && count >0)
	{ 
		if (count == Npos || count >size)
			count = size-pos;
	String TempStr;
	size_t j = 0;
	/*if (pos > 0) pos--;*/
	TempStr.size = count;
	/*pos++;*/
	TempStr.str = new T[TempStr.size+1]; /*In this case, memory allocation is simple:
				Starting from position pos (including it), characters up to count are copied,
				in this case, it would be rational to take the count of copied characters and use as
				line size*/
	for (size_t i = pos; i < count+pos; j++, i++)
	{
		TempStr[j] = this->str[i];
	}
	TempStr[count] = '\0';
	return TempStr;
	}
	else 
	{
		return String();
	}
}
//Removing characters from a string starting at position
template<typename T>
inline String<T> &String<T>::Erase(int position)
{
	String Temp;
	int j = 0;
	Temp.str = new T[size];
	for (int i = 0; i < size; i++)
	{
		if (i == position)
		{
			Temp[position] = this->str[position + 1];
			j = position + 1;
			i++;
		}
		else
		{
			Temp[j] = this->str[i];
			j++;
		}

	}
	Temp[size - 1] = '\0';
	delete[] this->str;
	str = new T[size];
	for (int i = 0; i < size - 1; i++)
	{
		str[i] = Temp[i];
	}
	size--;
	str[size] = '\0';
	return *this;
}
//Overloaded method for removing characters from a string
template<typename T>
String<T>& String<T>::Erase(size_t index, size_t num)
{
	if (index != 0 && num != 0 && size != 0 || index == 0 && num > 0)
	{
		String<T> Temp;
		size_t j = 0;
		size_t n = (size - (num));
		Temp.str = new T[n + 1];
		for (size_t i = 0; i < size; i++)
		{
			if (i == index)
				i += num - 1;
			else
			{
				Temp[j] = this->str[i];
				j++;
			}

		}
		Temp[n] = '\0';
		delete[] this->str;
		size = n;
		str = new T[n + 1];
		strncpy(str, Temp.str, size);
		str[n] = '\0';
		return *this;
	}
	else if (index == 0 && num == 0)
	{
		this->str[0] = '\0';
		this->size = 0;
		return *this;
	}
}

template<typename T>
inline String<T>& String<T>::assign(const String<T>& s, size_t st, size_t num)
{
	
	if (this->size != 0 || this->str != nullptr)
		delete[]str;
	size_t size = num;
	size_t j = 0;
	str = new T[size + 1];
	for (int i = st; i < num; i++, j++)
		this->str[j] = s[i];
	str[size] = '\0';
	return *this;

}
template<typename T>
String<T>& String<T>::assign(const char* ps, size_t st, size_t num)
{
	if (this->size != 0 || this->str != nullptr)
		delete[]str;
	size_t size = num;
	size_t j = 0;
	str = new T[size + 1];
	for (int i = st; i < num + st; i++, j++)
		this->str[j] = ps[i];
	str[size] = '\0';
	this->size = strlen(str);
	return *this;
}
template<typename T>
inline String<T>& String<T>::assign(const char* ps, size_t n)
{
	delete[]str;
	str = new T[n + 1];
	size = n;
	strncpy(str, ps, n);
	str[n] = '\0';
	return *this;
}
template<typename T>
inline String<T>& String<T>::assign(size_t n, char c)
{
	String temp(n, c);
	delete[] str;
	str = new T[n + 1];
	size = n;
	strncpy(str, temp.str, n);
	str[n] = '\0';
	return *this;
}
//String Assignment
template<typename T>
String<T>& String<T>::assign(const String<T>& str)
{
	size_t size = str.Size();
	if (this->size != 0)
		delete[] this->str;
	this->str = new T[size + 1];
	this->size = size;
	assignment(this->str, str);
	return *this;
}
//Method for finding a specific fragment in a string
/*If the string contains n identical characters, then the function returns the original
	position of the very first character
		which matches*/
template<typename T>
size_t String<T>::find(const char* str)
{
	size_t result = 0, j = 0, q = 0;
	for (int i = 0; i < size; i++)
	{
		if (str[i] == str[q])
		{
			q++;
			result++;
			j = i;
		}
	}
	if (result == strlen(str))
		return j - result + 1;
	else
		return 0;
}
//String Concatenation
template<typename T>
String<T>& String<T>::append(const String<T>& other, size_t start)
{
	String TempStr;
	String resultOther;

	resultOther.str = new T[start + 1];

	for (int i = 0; i < start; i++)
		resultOther[i] = other[i];

	resultOther[start] = '\0';
	resultOther.size = start;

	TempStr.str = new T[this->size + 1];

	for (int i = 0; i < size; i++)
		TempStr[i] = this->str[i];
	TempStr[size] = '\0';
	TempStr = TempStr + resultOther;
	for (int i = 0; i < size; i++)
		TempStr[i] = this->str[i];
	this->str = new T[TempStr.Size() + 1];
	for (int i = 0; i < TempStr.Size(); i++)
		this->str[i] = TempStr[i];
	this->str[TempStr.size] = '\0';
	return *this;
}
//Adding another string to the original string
template<typename T>
String<T>& String<T>::append(const char* other, size_t num)
{
	String TempStr;
	/* Temporary strings needed
	for computing*/
	String resultOther;
	resultOther.size = num;
	resultOther.str = new T[num + 1];

	for (int i = 0; i < num; i++)
		resultOther[i] = other[i];

	resultOther[num] = '\0';

	TempStr.str = new T[this->size + 1];
	TempStr.size = size;
	for (int i = 0; i < strlen(str); i++)
		TempStr[i] = this->str[i];
	TempStr[size] = '\0';
	TempStr = TempStr + resultOther;
	for (int i = 0; i < size; i++)
		TempStr[i] = this->str[i];
	this->str = new T[TempStr.Size() + 1];
	for (int i = 0; i < TempStr.Size(); i++)
		this->str[i] = TempStr[i];
	this->str[TempStr.size] = '\0';
	return *this;
}
//Method that adds two strings, for example
/*String s1 = "123" String s2 = "456 result
s1.append(s2,0)
will be 123456*/
template<typename T>
String<T>& String<T>::append(const String<T>& other, size_t start, size_t end)
{
	String TempStr;
	TempStr.size = size;
	String resultOther;
	int j = 0;
	resultOther.str = new T[end + 1];
	resultOther.size = end;
	for (int i = start; j < end; j++, i++)
		resultOther[j] = other[i];

	resultOther[end] = '\0';

	TempStr.str = new T[this->size + 1];

	for (int i = 0; i < size; i++)
		TempStr[i] = this->str[i];
	TempStr[size] = '\0';
	TempStr = TempStr + resultOther;
	for (int i = 0; i < size; i++)
		TempStr[i] = this->str[i];
	this->str = new T[TempStr.Size() + 1];
	size = TempStr.size;
	for (int i = 0; i < TempStr.Size(); i++)
		this->str[i] = TempStr[i];
	this->str[TempStr.size] = '\0';
	return *this;
}
template<typename T>
String<T>& String<T>::append(const String<T>& str)
{
	String temp(this->str);
	temp = temp + str;
	delete[]this->str;
	size = temp.size;
	this->str = new T[size + 1];
	strncpy(this->str, temp.str, size);
	this->str[size] = '\0';
	return *this;
}
template<typename T>
String<T>& String<T>::append(size_t n, char c)
{
	String temp(str);
	for (int i = 0; i < n; i++)
		temp.Push_back(c);
	delete[]this->str;
	str = new T[temp.size + 1];
	size = temp.size;
	strncpy(str, temp.str, temp.size);
	str[size] = '\0';
	return *this;
}
template<typename T>
//Inserting a character, string at any position in a string
String<T>& String<T>::insert(size_t num, const char* str)
{
	String Result;
	int i = 0, j = 0;
	int size = this->size + strlen(str);
	Result.str = new char[this->size + strlen(str) + 1];
	for (; i < num; i++)
		Result[i] = this->str[i];
	for (i; j < strlen(str); j++, i++)
		Result[i] = str[j];
	for (; i < size; num++, i++)
		Result[i] = this->str[num];
	Result[size] = '\0';
	delete[]this->str;
	this->size = size;
	this->str = new T[size + 1];
	assignment(this->str, Result);
	return *this;
}
//Method that capitalizes all letters
template<typename T>
String<T>& String<T>::upper(size_t start, size_t end)
{
	if (start <= 0 && end <= size)
	{
		for (int i = start; i < end; i++)
		{
			if (str[i] >= 65 && str[i] <= 90)
				continue;
			else if(str[i]!=' ')
				str[i] -= 32;
		}
		return *this;
	}
}
//Method that makes all letters small (lowercase)
template<typename T>
String<T>& String<T>::lower(size_t start, size_t end)
{
	if (start <= 0 && end <= size)
	{
		for (int i = start; i < end; i++)
		{
			if (str[i] >= 97 && str[i] <= 122)
				continue;
			else if(str[i]!=' ')
				str[i] += 32;
		}
		return *this;
	}
}
//Method for finding a character that is in a specific position
template<typename T>
size_t String<T>::find(char symbol, size_t position)
{
	size_t result, res = 0;
	for (int i = position; i < size; i++)
	{
		if (symbol == '\0')
			return Size();
		if (str[i] == symbol)
		{
			return result = i;
			res++;
		}
	}
	if (res == 0)
		std::cout << "Nothing found";
}
template<typename T>
size_t String<T>::find(const char* const str, size_t pos)
{
	try
	{
		if (pos > size || size == 0 || this->str == nullptr)
			throw ExceptionStr(SIZE, "Your string size == 0 or position find is bigger than length");
		size_t result = 0, j = 0, q = 0;
		for (int i = pos; i < size; i++)
		{
			if (this->str[i] == str[q])
			{
				q++;
				result++;
				j = i;
			}
		}
		if (result == strlen(str))
			return j - result + 1;
		else
			return 0;
	}
	catch (ExceptionStr exp)
	{
		exp.display();
		return NULL;
	}
}
template<typename T>
size_t String<T>::find(const char* const str, size_t pos, size_t n)
{
	size_t result = 0, j = 0, q = 0, tempn = n;
	for (int i = pos; i != pos + n; i++)
	{
		if (this->str[i] == str[q])
		{
			q++;
			result++;
			j = i;
		}
	}
	if (result == n)
		return j - result + 1;
	else
		return 0;
}
/*Getter for a string, returns the string it is asking for
	user*/
template<typename T>
const String<T> String<T>::GetStr() const
{
	return this->str;
}
/*Checking if a string is empty or not
	Returns true or false as result*/
template<typename T>
inline bool String<T>::isEmpty()
{
	int L = strlen(this->str);
	if (L > 0)
		return 0;
	else
		return 1;
}
//Checking if a string is empty or not
template<typename T>
inline void String<T>::isClear()
{
	str[0] = '\0';
	this->size = 0;
}
//Getting a reference to the last element of a string
template<typename T>
inline const char& String<T>::back()
{
	try
	{
		if (size == 0 || this->str == nullptr)
			throw ExceptionStr(SIZE, "Your string length == 0 or string = nullptr");
		return this->Str[size - 1];
	}
	catch (ExceptionStr exp)
	{
		exp.display();
	}
}

//Overloading cin and cout
template<typename T>
inline std::ostream& operator<<(std::ostream& out, const String<T>& other)
{
	return out << other.str;
}
template<typename T>
std::istream& operator>>(std::istream& is, String<T>& str)
{
	char* buf = new char[100001]; //create a temporary buffer to write any found string
	is.getline(buf, 100000); //we call the getline function which asks the user to enter a string, the string will be written to the buffer,
	// the string size is limited to 100000 characters
	delete[]str.str; //delete memory
	str.size = strlen(buf);
	str.str = new char[str.size + 1];
	strcpy(str.str, buf);
	delete[]buf;
	return is;
}

template<typename T>
template<typename T2>
inline String<T>& String<T>::To_string(T2 n)
{
	char* buf = new char[10000];
	if(strcmp(typeid(n).name(),"double") == 0)
		sprintf(buf, "%lf", n);
	else if(strcmp(typeid(n).name(), "int") == 0)
		sprintf(buf, "%d", n);
	else 
		sprintf(buf, "%s", n);
	delete[]str;
	size = strlen(buf);
	str = new T[size + 1];
	strncpy(str, buf,size);
	str[size] = '\0';
	delete[]buf;
	return *this;
}
template<typename T>
inline void String<T>::readfile(const char *nameF)
{
	ifstream file(nameF, ios::in | ios::binary);
	if (file.is_open())
		cout << "File is open!\n";
	else
	{
		cout << "File isn't open!\n";
		return;
	}
	char buf[255];
	
	cout << "reading data from a file...\n";
	file.getline(buf, 100);
	file.seekg(0, ios_base::end);
	cout << "Size of file:\n" << file.tellg();
	file.close();
	cout << "Do you want to overwrite your row data or display?\n";
	int choose;
	cin >> choose;
	if (choose == 1)
	{
		delete[]str;
		str = new T[strlen(buf) + 1];
		size = strlen(buf);
		strncpy(str, buf, size);
		str[size] = 0;
	}
	else if (choose == 2)
		cout << buf;
}

template<typename T>
inline void String<T>::writefile(const char* nameF)
{
	if (str != nullptr || size != 0)
	{
		ofstream file (nameF, ios::out || ios::binary);
		if (file.is_open())
			cout << "File is open!\n";
		else
			cout << "File isn't open!\n";
		file.write(str, size);
		cout << "Saving data was successful.\n";
		file.close();
	}
}
template<typename T>
inline String<T>& String<T>::reverse()
{
	for (int i = 0; i < size / 2; i++)
	{
		str[i] = str[i] + str[size - i - 1];
		str[size - i - 1] = str[i] - str[size - i - 1];
		str[i] = str[i] - str[size - i - 1];
	}
	return *this;
}
template<typename T>
inline size_t String<T>::rfind(const char* str, size_t pos)
{
	int n = String::find(str,pos);
	int temp;
	while (n > 0)
	{
		temp = n;
		n = String::find(str, n + 1);
		if (n > 0)
			temp = n;
		else
			break;
	}
	return temp;
}