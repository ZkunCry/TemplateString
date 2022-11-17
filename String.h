//Template Class String and Iterators by Eugene
#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string.h>
#include <typeinfo>
#include <fstream>
#include <sstream>
#include "iterators.h"
#include "Allocator.h"
using namespace std;


template<typename T>
class Iterator;
template<typename T>
class Reverse_Iterator;


template<typename T>
class String
{

private:
	using pointer_str = T*;
	//Class string fields
	pointer_str str;
	size_t size;
	size_t capacity;
	size_t count_capacity;
	Allocator<T> allocator;
	void assignment(char* pc, const String& other);
	
public:
	
	
	//Classes Iterators
	typedef Iterator<T> iterator;
	typedef Iterator<const T> const_iterator;
	typedef Reverse_Iterator<T> reverse_iterator;
	typedef Reverse_Iterator<const T> const_reverse_iterator;
	//////
	//  
	//String Constructors and Destructor
	static const size_t Npos = -1;
	String(const String& other);
	String(String&& other) noexcept; //Move konstructor
	String();
	String(const T* str);
	String(T symbol);
	String(size_t n, T symbol);
	String(int n);
	String(const String& other, size_t pos, size_t count);
	String(const T* ps, size_t count);
	~String()noexcept;
	/////////

	//Operator overloading
	int mystrcmp(const T*  lhs, const T*  rhs)const;
	template< typename T2>
	String& To_string(T2 n);
	T& operator()(int i);
	const T& operator[](size_t index)const;
	T& operator[](int pos);
	const bool operator!=(const String& other)const;
	const bool operator==(const String& other)const;
	String& operator =(const String& other);
	String& operator =(const T* s);
	String& operator =(T c);
	String operator+(const String<T>& other);
	String operator+(size_t number);
	String operator+(const T* str);
	template<typename T>
	friend String operator+(const String& lhs, const T* rhs);
	template<typename T>
	friend String operator+(const String& lhs, const String& rhs);
	const bool operator>(const String& other)const;
	constexpr bool operator<(const String& other)const;
	bool operator>=(const String& other);
	bool operator<=(const String& other);
	String& operator+=(const String<T>& right);
	template<typename T>
	friend String& operator+=(String<T>& left, const String<T>& right);
	template<typename T>
	friend String& operator+=(String& left, const T symbol);
	template<typename T>
	friend std::ostream& operator<<(std::ostream& out, const String<T>& other);
	template<typename T>
	friend std::istream& operator>>(std::istream& is, String<T>& str);
	/////////////////////////////////////////////

	//Methods for working with strings////
	const T* c_str() const;
	String& Resize(int n);
	String& Resize(short int n, char symbol);
	String SubStr(size_t pos = 0, size_t count = Npos)const;
	String& Push_back(const T c);
	String& pop_back();
	String& Push_front(const T c);
	String& Pop_front();
	String& Erase(int position);
	String& Erase(size_t index = 0, size_t num = Npos);
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
	T& at(size_t pos);
	int compare(size_t start, size_t num, const String& s) const;
	int compare(size_t start, size_t num, const char* s) const;
	int compare(const String& s) const noexcept;
	int compare(const char *s) const;
	void readfile(const char *nameF,int choose);
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
	operator char* ();
	operator String<T>();
	template<typename U>
	operator String<U>();
	void Reserve(size_t n=0);
	size_t SizeStr(const T* str)const;
};

using sstring = String<char>; // This typedef is needed in order not to write many times String<char> and Iterators<char>
using u16sstring = String<char16_t>;
using u32sstring = String<char32_t>;
using wsstring = String<wchar_t>;

template<typename T>
template<typename U>
inline String<T>::operator String<U>()
{
	return String<U>(str);
}
template<typename T>
inline String<T>::operator String<T>()
{
	return String<T>(str);
}
template<typename T>
inline String<T>::operator char* ()
{
	char* buf = new char[size + 1];
		for (int i = 0; i < size+1; i++)
			buf[i] = (char)str[i];
	return buf;
}
template<typename T>
inline void String<T>::Reserve(size_t n)
{
	if (str && size >0)
	{
		char* tempstr = allocator.allocate(size + 1);
		for (int i = 0; i < size; i++)
			allocator.construct(tempstr + i, str[i]);
		tempstr[size] = 0;
		allocator.deallocate(str, size);
		if(n >capacity)
		str = allocator.allocate(capacity + 16);
		for (int i = 0; i < size; i++)
			allocator.construct(str + i, tempstr[i]);
		str[n] = 0;
	}
}
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
inline size_t String<T>::SizeStr(const T* str)const
{
	size_t count = 0,i=0;
	while (str[i] != 0)
	{
		count++;
		i++;
	}
	return i;
}
template<typename T>
inline String<T>::String(const T* ps, size_t count)
{
	this->str = allocator.allocate(count+1);
	for(int i =0;i<count;i++)
		allocator.construct(str+i, ps[i]);
	size = count;
	str[size] = 0;
}
template<typename T>
inline String<T>::String(const String& other, size_t pos, size_t count)
{
	this->str = allocator.allocate((count - pos)+1);
	this->size = count - pos;
	for (int i = 0; i < size; i++)
		allocator.construct(str + i, other[i]);
	str[size] = 0;
}
template<typename T>
String<T>::String()
{
	this->str = nullptr;
	this->size = 0;
}
template<typename T>
String<T>:: String(const T* str)
{
	size = SizeStr(str);
	this->str = allocator.allocate(size+1);
	for (int i = 0; i < size; i++)
		allocator.construct(this->str + i, str[i]);
	this->str[size] = '\0';
}


template<typename T>
String<T>::String(const String<T>& other) :String(other.str) {}

template<typename T>
String<T>::String(String<T>&& other)noexcept
{
	this->str = other.str;
	this->size = other.size;
	other.str = nullptr;
	other.size = 0;
}
template<typename T>
String<T>::String(T symbol)
{
	str = allocator.allocate(2);
	size= 1;
	allocator.construct(str, symbol);
	str[size] = 0;
}
template<typename T>
String<T>::String(size_t n, T symbol)
{
	this->str = new T[n + 1];
	for (int i = 0; i < n; i++)
		allocator.construct(str + i, symbol);
	this->str[n] = '\0';
	this->size = n;
}
template<typename T>
String<T>::String(int n)
{
	String::To_string(n);
}
template<typename T>
String<T>::~String() noexcept
{
	if (str != nullptr)
	{
		allocator.deallocate(str, size);
		this->size = 0;
	}
}
//String Size Method
template<typename T>
size_t String<T>::Size()const
{
	return size;
}
template<typename T>
String<T> String<T>::operator+(const String<T>& other)
{
	String<T> s;
	size_t count = this->size + other.size;
	s.str = allocator.allocate(count + 1);
	s.size = count;
	int i = 0;
	for (; i < size+1; i++)
		allocator.construct(s.str + i, str[i]);
	i--;
	for (int j = 0; j < other.size; j++, i++)
		allocator.construct(s.str+i,other.str[j]);
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
	return this->str[index];
}
template<typename T>
inline T& String<T>::operator[](int pos)
{
	return this->str[pos];
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
inline String<T>& operator+=(String<T>& left, const T symbol)
{
	left.Push_back(symbol);
	return left;
}
template<typename T>
inline String<T> operator+(const String<T>& lhs, const T* rhs)
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
template<typename T>
inline int String<T>::mystrcmp(const T*  lhs, const T*  rhs)const
{
	size_t count = 0;
	size_t sizelhs = SizeStr(lhs);
	size_t sizerhs = SizeStr(rhs);
	if (sizelhs > sizerhs)
		return 1;
	else if (sizelhs < sizerhs)
		return -1;
	else
		for (int i = 0; i < sizelhs; i++)
		{
			if (lhs[i] > rhs[i])
				return 1;
			else if (lhs[i] < rhs[i])
				return -1;
			else if (lhs[i] == rhs[i])
				count++;
		}
	if (count == sizelhs)
		return 0;
}

//Overloaded Comparison Operators
template<typename T>
inline const bool String<T>::operator>(const String<T>& other)const
{
	return mystrcmp(this->str,other.str) <0;
}
template<typename T>
inline constexpr bool String<T>::operator<(const String<T>& other)const
{
	return  mystrcmp(this->str, other.str) >0;
}
template<typename T>
inline bool String<T>::operator>=(const String<T>& other)
{
	return  mystrcmp(this->str, other.str) ==0 || mystrcmp(this->str, other.str)  == 1;
}
template<typename T>
inline bool String<T>::operator<=(const String<T>& other)
{
	return  mystrcmp(this->str, other.str)  == 0 || mystrcmp(this->str, other.str)  == -1;
}
template<typename T>
inline String<T>& String<T>::operator+=(const String<T>& right)
{
	String& tempstr = *this;
	tempstr = tempstr + right;
	return *this;
}
template<typename T>
inline const bool String<T>::operator==(const String<T>& other)const
{

	return mystrcmp(this->str, other.str) ==0;
}
template<typename T>
inline const bool String<T>::operator!=(const String<T>& other)const
{
	return  mystrcmp(this->str, other.str)  < 0 || mystrcmp(this->str, other.str)  > 0;
}

template<typename T>
String<T>& String<T>::operator =(const String<T>& other)
{
	if (this->str)
		allocator.deallocate(this->str,size);
	int count = 0, i = 0;
	while (other.str[i] != 0)
	{
		count++;
		i++;
	}
	i = 0;
	this->size = count;
	this->str = allocator.allocate(size+1);
	while (other[i] != 0)
	{
		allocator.construct(str+i,other[i]);
		i++;
	}
	this->str[size] = '\0';
	return *this;
}
template<typename T>
String<T>& String<T>::operator=(const T* s)
{
	size_t i = 0;
	if (this->str != nullptr)
		allocator.deallocate(this->str,size);
	size = SizeStr(s);
	str = allocator.allocate(size + 1);
	while (s[i] != 0)
	{
		allocator.construct(str+i,s[i]);
		i++;
	}
	str[size] = '\0';
	return *this;
}
template<typename T>
String<T>& String<T>::operator=(T c)
{
	if(this->str)
		allocator.deallocate(str,size);
	size = 1;
	str = allocator.allocate(size + 1);
	allocator.construct(str, c);
	str[size] = '\0';
	return *this;
}


//Overloaded summation operator (concatenation)


template<typename T>
inline String<T> String<T>::operator+(size_t number)
{
	return this->str + number;
}

template<typename T>
inline String<T> String<T>::operator+(const T* str)
{
	String<T>tempstr(str);
	String<T>& tempthis = *this;
	return tempthis + tempstr;
}

//Formation of a string in the style of C (char)
template<typename T>
inline const T* String<T>::c_str() const
{
	return str;
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
inline T& String<T>::at(size_t pos)
{
	try
	{
		if (pos > size)
		{
			throw out_of_range("String<T>::at ");
		}
		return this->str[pos];
	}
	catch(const std::out_of_range& oor)
	{
		cerr<<"Out of Range error: " << oor.what()<<endl;
	}
}
//The function changes the contents of the strings
template<typename T>
void String<T>::swap(String<T>& str)
{
	
	std::swap(size, str.size);
	std::swap(this->str, str.str);
}
//String resize
template<typename T>
String<T>& String<T>::Resize(int n)
{
	try
	{
		if (n < 0 || this->str == nullptr)
			throw out_of_range("String<T>::Resize ");
		String TempStr;
		int OrigSize = this->size, count = size;
		TempStr.str = allocator.allocate(n + 1);  //Allocating memory for a temporary string that will store the result
		TempStr.size = n; //Assigning a new size to the original string
		TempStr.str[n] = '\0'; // Add zero at the end of the line
		if (n < size)
		{
			for (int i = 0; i < n; i++)
				allocator.construct(TempStr.str + i, this->str[i]);
		}
		else
		{

			for (int i = 0; i < size; i++)
				allocator.construct(TempStr.str + i, this->str[i]);
			while (TempStr.str[count] != '\0') //Filling the selected cells of the array with emptiness (it is necessary so that garbage values are not displayed)
			{
				TempStr.str[count] = ' ';
				count++; //Increasing the index
			}
		}
		allocator.deallocate(str, size); /*We clear the memory in order to later change the size of the string when memory is allocated*/
		this->size = n; //Assign a new size
		this->str = allocator.allocate(size + 1); //Allocate new memory
		for (int i = 0; i < size; i++)
			allocator.construct(this->str+i , TempStr.str[i]);
		this->str[size] = '\0';
		return *this; // We return as a result the object that needed to be changed
	}
	catch (const std::out_of_range &exp)
	{
		cerr<<"Out of Range: " << exp.what()<<endl;
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
String<T>& String<T>::Push_back(const T c)
{
	T* tempstr = allocator.allocate(size+1);
	memcpy(tempstr, str, size+1);
	allocator.deallocate(this->str,size);
	str = allocator.allocate(size + 2);
	for (int i = 0; i < size; i++)
		allocator.construct(str + i, tempstr[i]);
	allocator.construct(str + size, c);
	size++;
	str[size] = 0;
	
	return *this;
	
}
//Removing an element at the end of a line
template<typename T>
String<T>& String<T>::pop_back()
{
	try
	{
		if (this->size == 0)
			throw length_error("String<T>::pop_back ");
	}
	catch (exception &exp)
	{
		cerr<<"Length error: " << exp.what()<<endl;
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
String<T>& String<T>::Push_front(const T c)
{
	try
	{
		if (!this->str)
		{
			throw bad_alloc();
		}
		String<T> temp(c);
		String<T> result(this->str);
		temp += result;
		allocator.deallocate(str,size);
		str =allocator.allocate(temp.size+1);
		for (int i = 0; i < temp.size; i++)
			allocator.construct(str+i,temp[i]);
		size = temp.size;
		str[temp.size] = '\0';
		return *this;
	}
	catch (const std::bad_alloc& alloc)
	{
		cerr << "Bad alloc error: " << alloc.what()<<" String<T>::Push_front" << endl;
		return *this;
	}

}
template<typename T>
String<T>& String<T>::Pop_front()
{
	try
	{
		if (this->size == 0)
			throw length_error("String<T>::Pop_front");
		if (!this->str)
			throw bad_alloc();
		String result(this->str);
		result.size = size;
		allocator.deallocate(str, size);
		str = allocator.allocate(size);
		for (int i = 0, j = 1; i < size; i++, j++)
			str[i] = result[j];
		size = result.size - 1;
		str[size] = '\0';
		return *this;
	}
	catch (const bad_alloc& ba)
	{
		cerr<<"Bad alloc error: " << ba.what()<<" String<T>::Pop_front "<<endl;
		return *this;
	}
	catch (const length_error& le)
	{
		cerr << "Length error: " << le.what() << endl;
		return *this;
	}
}
//returns a substring of the given string starting at the character at index pos count
//count or to the end of the string if pos + count > S.size().
template<typename T>
String<T> String<T>::SubStr(size_t pos, size_t count)const
{
	/*If the number of characters to be copied, starting from pos, exceeds the length of the original string,
	then in this case you will need to copy from pos to the end of the line
	If the number of characters to be copied, starting from pos, does not exceed the length of the original string,
	Then the string is copied from pos to count*/

	if((int)pos <size  || (int)count == Npos ||(int)pos >0 && (int)count >0)
	{ 
		if (count == Npos || count >size)
			count = size-(int)pos;
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
	if (index != 0 && (int)num != 0 && size != 0 || index == 0 && (int)num > 0)
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
	else if (index == 0 && (int)num == 0)
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
	for (int i = st; j < num; i++, j++)
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
	resultOther.str = allocator.allocate(end + 1);
	resultOther.size = end;
	for (int i = start; j < end; j++, i++)
		allocator.construct(resultOther.str + j, other[i]);

	resultOther[end] = '\0';

	TempStr.str = allocator.allocate(size + 1); 

	for (int i = 0; i < size; i++)
		allocator.construct(TempStr.str + i, str[i]);
	TempStr[size] = '\0';
	TempStr = TempStr + resultOther;
	for (int i = 0; i < size; i++)
		allocator.construct(TempStr.str + i, str[i]); 
	this->str = allocator.allocate(TempStr.Size() + 1); 
	size = TempStr.size;
	for (int i = 0; i < TempStr.Size(); i++)
		allocator.construct(str+i, TempStr[i]); 
	this->str[TempStr.size] = '\0';
	return *this;
}
template<typename T>
String<T>& String<T>::append(const String<T>& str)
{
	String temp(this->str);
	temp = temp + str;
	allocator.deallocate(this->str, size);
	size = temp.size;
	this->str = allocator.allocate(size + 1);
	for (int i = 0; i < size; i++)
		allocator.construct(this->str + i, temp.str[i]);
	this->str[size] = '\0';
	return *this;
}
template<typename T>
String<T>& String<T>::append(size_t n, char c)
{
	String temp(str);
	for (int i = 0; i < n; i++)
		temp.Push_back(c);
	allocator.deallocate(str, size);
	size = temp.size;
	str =allocator.allocate(size + 1);
	for (int i = 0; i < size; i++)
		allocator.construct(str + i, temp.str[i]);
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
	return (int)Npos;
}
template<typename T>
size_t String<T>::find(const char* const str, size_t pos)
{
	try
	{
		if (pos > size || size == 0 || this->str == nullptr)
			throw exception( "Exception! Your string size == 0 or position find is bigger than length");
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
	catch (exception &exp)
	{
		cerr<<exp.what();
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
	int L = size;
	if (L > 0)
		return 0;
	else
		return 1;
}
//Checking if a string is empty or not
template<typename T>
inline void String<T>::isClear()
{
	allocator.deallocate(str, size);
	str = allocator.allocate(1);
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
			throw exception("Your string length == 0 or string = nullptr");
		return this->str[size - 1];
	}
	catch (exception & exp)
	{
		cerr<<exp.what();
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
	str.str = new T[str.size + 1];
	for (int i = 0; i < str.size+1; i++)
		str.str[i] = buf[i];
	
	delete[]buf;
	return is;
}

template<typename T>
template<typename T2>
inline String<T>& String<T>::To_string(T2 n)
{
	std::ostringstream oss1;
	oss1 << n;
	allocator.deallocate(str, size);
	size = oss1.str().size();
	str = allocator.allocate(size+1);
	for (int i = 0; i < size+1; i++)
		allocator.construct(str + i, oss1.str()[i]);
	return *this;
}
template<typename T>
inline void String<T>::readfile(const char *nameF,int choose)
{
	ifstream file(nameF, ios::in | ios::binary);
	if (file.is_open()){}
	else
	{
		return;
	}
	char buf[255];
	file.getline(buf, 100);
	file.seekg(0, ios_base::end);
	file.close();
	if (choose == 1)
	{
		allocator.deallocate(str, size);
		str = allocator.allocate(strlen(buf) + 1);
		size = strlen(buf);
		for (int i = 0; i < size+1; i++)
			allocator.construct(str + i, buf[i]);
	}
	else if (choose == 2)
		cout << buf<<endl;
}

template<typename T>
inline void String<T>::writefile(const char* nameF)
{
	ofstream file(nameF, ios::out || ios::binary);
	try
	{
		file.is_open();
		if (str == nullptr || size == 0 )
		{
			throw exception("Exception! Memory hasn't been allocated or file was not found\n");
		}
		file.write(str,size);
		file.close();
	}
	catch (exception& exp)
	{
		cout<<exp.what();
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
	int n = String::find(str,(int)pos);
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


