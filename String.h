//Template Class String and Iterators by Eugene
#pragma once

#include <iostream>
#include <string.h>
#include <typeinfo>
#include <fstream>
#include <sstream>
#include <utility>
#include "iterators.h"
#include "Allocator.h"

				

using namespace std;


template<typename T>
class Iterator;
template<typename T>
class Reverse_Iterator;
template <typename T>
class Allocator;

template<typename T>
class String
{
	using pointer_str = T*;
private:
	pointer_str str;
	size_t size;
	size_t capacity;
	size_t coefficient;
	size_t old_capacity;
	Allocator<T> allocator;


public:

	static const size_t Npos = -1;
	//Classes Iterators
	using iterator = Iterator<T>;
	using const_iterator  = Iterator<const T>;
	using reverse_iterator  = Reverse_Iterator<T>;
	using const_reverse_iterator  = Reverse_Iterator<const T>;
	//////
	//  
	//String Constructors and Destructor
	String(const String& other);
	String(String&& other) noexcept; //Move konstructor
	String();
	String(const T* str);
	String(T symbol);
	String(size_t n, T symbol);
	String(int n);
	String(const String& other, size_t pos, size_t count);
	String(const T* ps, size_t count);
	template<typename T2>
	String (const T2* str);
	template <typename T2>
	String(const String<T2>& other);
	~String()noexcept;
	size_t Copy(T* str, size_t _Count, size_t _Pos=0);
	int mystrcmp(const T* lhs, const T* rhs)const;
	template< typename T2>
	String& To_string(T2 n);
	/////////

	T& operator()(int i);
	const T& operator[](size_t index)const;
	T& operator[](int pos);
	template<typename T2>
	const bool operator!=(const String<T2>& other)const;
	template<typename T2>
	const bool operator==(const String<T2>& other)const;
	String& operator=(String&& other)noexcept;
	String& operator =(const String& other);
	template<typename T2>
	String& operator=(const String<T2>& s);
	String& operator =(const T* s);
	String& operator =(T c);
	String operator+(const String<T>& other);
	String operator+(size_t number);
	template<typename T>
	friend String operator+(const String& lhs, const String& rhs);
	const bool operator>(const String& other)const;
	constexpr bool operator<(const String& other)const;
	bool operator>=(const String& other);
	bool operator<=(const String& other);
	template<typename T,typename T2>
	friend String<T>& operator+=(String<T>& left, const String<T2>& right);
	template<typename T>
	friend std::ostream& operator<<(std::ostream& out, const String<T>& other);
	template<typename T>
	friend std::istream& operator>>(std::istream& is, String<T>& str);
	/////////////////////////////////////////////
	//Methods for working with strings////
	const T* c_str() const noexcept;
	String& Resize(int n);
	String& Resize(short int n, T symbol);
	String SubStr(size_t pos = 0, size_t count = Npos)const;
	String& Push_back(const T c);
	String& pop_back();
	String& Push_front(const T c);
	String& Pop_front();
	String& Erase(int position);
	String& Erase(size_t index, size_t num);
	void isClear() noexcept;
	String& lower(size_t start, size_t end);
	String& upper(size_t start, size_t end);
	size_t find(T symbol, size_t position = 0);
	size_t find(const T* const str, size_t pos = 0);
	size_t find(const T* const str, size_t pos, size_t n);
	size_t rfind(const T* str, size_t pos = Npos);
	String& append(const String& other, size_t start);
	String& append(const T* other, size_t num);
	String& append(const String& other, size_t start, size_t end);
	String& append(const String& str);
	String& append(size_t n, T c);
	template<typename T2>
	String& insert(size_t num, const T2* str);
	String& assign(const String<T>& str);
	String& assign(const String<T>& s, size_t st, size_t num);
	String& assign(const T* ps, size_t st, size_t num);
	String& assign(const T* ps, size_t n);
	String& assign(size_t n, T c);
	String& assign(String<T> &&str)noexcept;
	String& Replace(size_t pos, size_t len, const String& str);
	template<typename T2>
	String& Replace(size_t pos, size_t len, const T2* s);
	String& Replace(const_iterator it1,const_iterator it2,const T *pc);
	size_t Size()const noexcept;
	size_t Capacity()const noexcept;
	String& reverse();
	const String GetStr()const noexcept;
	bool isEmpty()noexcept;
	void swap(String& str);
	T& at(size_t pos);
	int compare(size_t start, size_t num, const String& s) const;
	int compare(size_t start, size_t num, const char* s) const;
	int compare(const String& s) const noexcept;
	int compare(const char *s) const;
	void readfile(const char *nameF,int choose);
	void writefile(const char* nameF);
	//Functions that return a reference to the first and last object of a string
	constexpr T& front();
	const char& back();
	//Class Iterator methods
	iterator begin()const noexcept;
	iterator end()const noexcept;
	const_iterator cbegin()const noexcept;
	const_iterator cend()const noexcept;
	reverse_iterator rbegin()const noexcept;
	reverse_iterator rend()const noexcept;
	const_reverse_iterator rcbegin()const noexcept;
	const_reverse_iterator rcend()const noexcept;
	operator char* ();
	template<typename U>
	operator String<U>();
	size_t SizeStr(const T* str)const noexcept;
	template<typename T2>
	size_t SizeStr(const T2* str)const noexcept;
};
// This using is needed in order not to write many times String<char> and Iterators<char>
using sstring = String<char>; 
using u16sstring = String<char16_t>;
using u32sstring = String<char32_t>;
using wsstring = String<wchar_t>;
//Const_reverse iterator

template<typename T>
inline String<T>::const_reverse_iterator String<T>::rcbegin() const noexcept
{
	return const_reverse_iterator(str + size - 1);
}
template<typename T>
inline String<T>::const_reverse_iterator String<T>::rcend() const noexcept
{
	return const_reverse_iterator(str - 1);
}
template<typename T>
String<T>::const_iterator String<T>::cbegin()const noexcept
{
	return const_iterator(str);
}
template<typename T>
String<T>::const_iterator String<T>::cend() const noexcept
{
	return const_iterator(str + size);
}
/////////

//////////
/// Class Iterator(Const) and Reverse Iterator
template<typename T>
inline String<T>::iterator String<T>::begin()const noexcept
{
	return iterator(str);
}
template<typename T>
inline String<T>::iterator String<T>::end()const noexcept
{
	return iterator(str + size);
}

template<typename T>
inline String<T>::reverse_iterator String<T>::rbegin() const noexcept
{
	return reverse_iterator(str + size - 1);
}
template<typename T>
inline String<T>::reverse_iterator String<T>::rend() const noexcept
{
	return reverse_iterator(str-1);
}


///////////////////////////////////////


/////////////////TemplateClass String///////////////////
template<typename T>
inline size_t String<T>::SizeStr(const T* str)const noexcept
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
	if (count > capacity)
		while (count > capacity)
			capacity += 10;
	this->str = allocator.allocate(capacity+1);
	for(int i =0;i<count;i++)
		allocator.construct(str+i, ps[i]);
	size = count;
	str[size] = 0;
}

template<typename T>
template<typename T2>
inline String<T>::String(const String<T2>& other)
{
	size = other.Size();
	if (size > capacity)
		while (size > capacity)
			capacity += 10;
	this->str = new T[capacity + 1];
	for (int i = 0; i < size; i++)
		 allocator.construct(str + i, other[i]);
	this->str[size] = '\0';
}

template<typename T>
template<typename T2>
inline String<T>::String(const T2* str)
{
	
	size = SizeStr(str);
	if (size > capacity)
		while (size > capacity)
			capacity += 10;
	this->str = allocator.allocate(capacity + 1); 
	for (int i = 0; i < size; i++)
		this->str[i] = str[i];
	this->str[size] = '\0';
}
template<typename T>
inline String<T>::String(const String& other, size_t pos, size_t count):String(other.SubStr(pos,count)){}
template<typename T>
inline String<T>::String()
{
	this->str = allocator.allocate(10,str);
	this->capacity  = 10;
	this->size = 0;
}
template<typename T>
inline String<T>:: String(const T* str)
{

	size = SizeStr(str);
	if (size > capacity)
		while (size > capacity)
			capacity += 10;
	this->str = allocator.allocate(capacity+1);
	for (int i = 0; i < size; i++)
		allocator.construct(this->str + i, str[i]);
	this->str[size] = '\0';
}


template<typename T>
inline String<T>::String(const String<T>& other) :String(other.str) {}

template<typename T>
inline String<T>::String(String<T>&& other)noexcept
{

	this->str = other.str;
	this->size = other.size;
	this->capacity = other.capacity;
	other.str = nullptr;
	other.size = 0;
}
template<typename T>
inline String<T>::String(T symbol)
{
	capacity = 10;
	str = allocator.allocate(capacity);
	size= 1;
	allocator.construct(str, symbol);
	str[size] = 0;
}
template<typename T>
inline String<T>::String(size_t n, T symbol)
{
	this->size = n;
	if (size > capacity)
		while (size > capacity)
			capacity += 10;
	this->str = new T[capacity + 1];
	for (int i = 0; i < n; i++)
		allocator.construct(str + i, symbol);
	this->str[n] = '\0';
}
template<typename T>
inline String<T>::String(int n)
{
	String::To_string(n);
}
template<typename T>
String<T>::~String() noexcept
{

	if (str != nullptr)
	{
		allocator.deallocate(str, size);
		str = nullptr;
		this->size = 0;
		this->capacity = 0;
	}
}
template<typename T>
inline size_t String<T>::Copy(T* str, size_t _Count, size_t _Pos)
{
	String<T> tempstr((this->SubStr(_Pos, _Count)));
	for (int i = 0; i < tempstr.size; i++)
		str[i] = tempstr[i];
	return tempstr.size;
}
//String Size Method
template<typename T>
inline size_t String<T>::Size()const noexcept
{
	return size;
}
template<typename T>
inline size_t String<T>::Capacity() const noexcept
{
	return capacity;
}
template<typename T>
String<T> String<T>::operator+(const String<T>& other)
{
	
	try
	{
		if (other.str == nullptr || other.size == 0)
			throw bad_alloc();
		String<T> s;

		size_t count = this->size + other.size;
		if (count > capacity)
			while (count > capacity)
				capacity += 10;
		s.str = allocator.allocate(capacity + 1);
		s.size = count;
		int i = 0;
		for (; i < size + 1; i++)
			allocator.construct(s.str + i, str[i]);
		i--;
		for (int j = 0; j < other.size; j++, i++)
			allocator.construct(s.str + i, other.str[j]);
		s.str[count] = '\0';
		s.size = count;
		return s;
	}
	catch (const std::bad_alloc& ex)
	{
		cout << "Allocation failed: " << ex.what() << endl;
		return String();
	}
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
	try
	{
		if (len > Size())
			throw range_error("String<T>::Replace");
		String::Erase(pos, len);
		String::insert(pos, str.str);
		return *this;
	}
	catch (range_error& re)
	{
		cerr << "Range error: " << re.what()<<endl;
	}
}

template<typename T>
template<typename T2>
String<T>& String<T>::Replace(size_t pos, size_t len, const T2* s)
{
	try
	{
		if (len > Size())
			throw range_error("String<T>::Replace");
		String str(s);
		String::Replace(pos, len, str);
		return *this;
	}
	catch (range_error& re)
	{
		cerr << "Range error: " << re.what() << endl;
	}
}

template<typename T>
inline String<T>& String<T>::Replace(const_iterator it1, const_iterator it2, const T* pc)
{
		String str(pc);
		int pos = String::find(*it1);
		int len = String::find(*it2);
		String::Replace(pos, len, str);
		return *this;
}
//Overloading Binary Operators
template<typename T,typename T2>
String<T>& operator+=(String<T>& left, const String<T2>& right)
{
	left = left + right;
	return left;
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
	return mystrcmp(this->str,other.str) >0;
}
template<typename T>
inline constexpr bool String<T>::operator<(const String<T>& other)const
{
	return  mystrcmp(this->str, other.str) <0;
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
template<typename T2>
inline const bool String<T>::operator==(const String<T2>& other)const
{
	String<T> str(other);
	return mystrcmp(this->str, str.c_str()) ==0;
}

template<typename T>
template<typename T2>
inline const bool String<T>::operator!=(const String<T2>& other)const
{
	String<T> str(other);
	return  mystrcmp(this->str, str.c_str())  < 0 || mystrcmp(this->str, str.c_str())  > 0;
}
template<typename T>
inline String<T>& String<T>::operator=(String&& other) noexcept
{
	swap(other);
	return *this;
}
template<typename T>
template<typename T2>
inline String<T>& String<T>::operator=(const String<T2>& s)
{
	if (SizeStr(s.c_str())> capacity)
	{
		while (size > capacity)
			capacity += 10;
		allocator.deallocate(this->str, size);
		this->str = allocator.allocate(capacity + 1);
	}
	int count = SizeStr(s.c_str()), i =0;

	this->size = count;
	this->str = new T[size + 1];
	while (s[i] != 0)
	{
		str[i] = s[i];
		i++;
	}
	this->str[size] = '\0';
	return *this;
}
template<typename T>
template<typename T2>
inline size_t String<T>::SizeStr(const T2* str) const noexcept
{
	size_t count = 0, i = 0;
	while (str[i] != 0)
	{
		count++;
		i++;
	}
	return i;
}
template<typename T>
String<T>& String<T>::operator =(const String<T>& other)
{
	try
	{
		if (other.str == nullptr)
			throw bad_alloc();
		if (other.size > capacity)
		{
			while (other.size > capacity)
				capacity += 10;
			allocator.deallocate(this->str, size);
			this->str = allocator.allocate(capacity + 1);
		}
		int count = 0, i = 0;
		while (other.str[i] != 0)
		{
			count++;
			i++;
		}
		i = 0;
		this->size = count;
		while (other[i] != 0)
		{
			allocator.construct(str + i, other[i]);
			i++;
		}
		this->str[size] = '\0';
		return *this;
	}
	catch (const bad_alloc& ba)
	{
		cerr << "Allocation failed: " << ba.what() <<": operator=" << endl;
	}
}
template<typename T>
String<T>& String<T>::operator=(const T* s)
{
	size_t i = 0;
	size = SizeStr(s);
	if (size > capacity)
	{
		while (size > capacity)
			capacity += 10;
		allocator.deallocate(this->str, size);
		str = allocator.allocate(capacity + 1);
	}
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
	capacity = 10;
	str = allocator.allocate(capacity + 1);
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

//Formation of a string in the style of C (char)
template<typename T>
inline const T* String<T>::c_str() const noexcept
{
	return str;
}

//Getting a reference to the first element of a string
template<typename T>
inline constexpr T& String<T>::front()
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
	return mystrcmp(this->str, s) == 0;
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

inline void String<T>::swap(String<T>& str)
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
		(*this).Resize(n, ' ');
		return *this; 
	}
	catch (const std::out_of_range &exp)
	{
		cerr<<"Out of Range: " << exp.what()<<endl;
		return *this;
	}
}
//Overloaded String Size Remapping Method
template<typename T>
String<T>& String<T>::Resize(short int n, T symbol)
{
	if (this->str != nullptr)
	{
		if (n > capacity)
		{
			while (n > capacity)
				capacity += 10;
			String temp(*this);
			allocator.deallocate(str, size);
			str = allocator.allocate(capacity);
			for (int i = 0; i < n; i++)
			{
				str[i] = temp[i];
				if (i == size)
					str[i] = symbol;
			}
			str[size] = 0;
			size = n;
		}
		else if(n > size)
		{
			for (int i = size; i < n; i++)
				str[i] = symbol;
			size = n;
			str[size] = 0;
		}
		else
		{
			str[n] = 0;
			size = n;
		}
		
	}
	return *this;
}
//Method for inserting a character at the end of a string
template<typename T>
String<T>& String<T>::Push_back(const T c)
{
	if (size+1 < capacity)
	{
		allocator.construct(str + size++, c);
		str[size] = 0;
		return *this;
	}
	else
	{
		capacity += 10;
		T* tempstr = allocator.allocate(capacity + 2);
		for (int i = 0; i < size; i++)
		{
			tempstr[i] = std::move(str[i]);
			allocator.destroy(str + i);
		}
		allocator.deallocate(this->str, size);
		str = tempstr;
		allocator.construct(str + size++, c);
		str[size] = 0;
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
		T* pc = allocator.allocate(size+1);
		for (int i = 0; i < size; i++)
			allocator.construct(pc+i,str[i]);
		pc[size] = '\0';
		allocator.deallocate(str,size);
		str = allocator.allocate(size + 1);
		for (int i = 0; i < size; i++)
			allocator.construct(str + i, pc[i]);
		str[size] = '\0';
		this->size = size;
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
		T* tempstr = allocator.allocate(size + 2);
		int j = 1;
		for (int i = 0; i < size; i++,j++)
		{
			tempstr[j] = std::move(str[i]);
			allocator.destroy(str + i);
		}
		allocator.deallocate(this->str, size);
		str = tempstr;
		allocator.construct(str+0, c);
		size++;
		str[size] = 0;
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
	try
	{
		if ((int)pos > size  || (int)pos < 0 && (int)count < 0)
			throw  range_error("String<T>::SubStr");
		else
		{

			if (count == Npos || count > size)
				count = size - (int)pos;
			String TempStr;
			size_t j = 0;
			TempStr.size = count;
			if (TempStr.size > TempStr.capacity)
			{
				while (TempStr.size > TempStr.capacity)
					TempStr.capacity += 10;
				TempStr.str = new T[TempStr.capacity + 1];
			}
			for (size_t i = pos; i < count + pos; j++, i++)
			{
				TempStr.str[j] = this->str[i];
			}

			TempStr.str[count] = '\0';
			return TempStr;
		}

	}
	catch (range_error& ex)
	{
		cerr << "Range error: " << ex.what() << endl;
		return String();
	}
}
//Removing characters from a string starting at position
template<typename T>
inline String<T> &String<T>::Erase(int position)
{
	try
	{

		if (position > size)
			throw out_of_range("String<T>::Erase");
		for (int i = 0; i < size; i++)
		{
			if (i == position)
			{
				while (str[i+1]!=0)
				{
					std::swap(str[i], str[i + 1]);
					i++;
				}
			}
		}
		size--;
		str[size] = 0;

		return *this;
	}
	catch (out_of_range& err)
	{
		cerr << "Out_of_range: " << err.what() << endl;
		return *this;
	}
}
//Overloaded method for removing characters from a string
template<typename T>
String<T>& String<T>::Erase(size_t index, size_t num)
{
	if (index != 0 && (int)num != 0 && size != 0 || index == 0 && (int)num > 0)
	{
		for (int i = 0; i < num; i++)
			String::Erase(index);
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
	try
	{
		if (this->size == 0 || str == nullptr)
			throw exception("String<T>::assign");
		if (num > capacity)
		{
			while (num > capacity)
				capacity += 10;
			delete[]str;
			
			str = new T[capacity + 1];
		}
		size_t size = num;
		size_t j = 0;
		this->size = size;
			for (int i = st; j < num; i++, j++)
				this->str[j] = s[i];
			str[size] = '\0';
			return *this;

	}
	catch (exception& err)
	{
		cerr << "bad_alloc: " << err.what();
		return *this;
	}
}
template<typename T>
String<T>& String<T>::assign(const T* ps, size_t st, size_t num)
{
	try
	{
		if (this->size == 0 || this->str == nullptr)
			throw exception("String<T>::assign");
		if (num > capacity)
		{
			while (num > capacity)
				capacity += 10;
			delete[]str;

			str = new T[capacity + 1];
		}
		this->size = num;
		size_t j = 0;
		for (int i = st; i < num; i++, j++)
			this->str[j] = ps[i];
		str[size] = '\0';
		return *this;
	}
	catch (exception& ex)
	{
		cerr << "Bad_alloc: " << ex.what();
		return *this;
	}
}
template<typename T>
inline String<T>& String<T>::assign(const T* ps, size_t n)
{
	try
	{
		if(str == nullptr || size == 0)
			throw exception("String<T>::assign");
		if (n > capacity)
		{
			while (n > capacity)
				capacity += 10;
			delete[]str;
			str = new T[capacity + 1];
		}
		size = n;
		for (int i = 0; i < n; i++)
			str[i] = ps[i];
		str[size] = '\0';
		return *this;
	}
	catch (exception& ex)
	{
		cerr << "Bad_alloc: " << ex.what();
		return *this;
	}
}
template<typename T>
inline String<T>& String<T>::assign(size_t n, T c)
{
	try
	{
		if (str == nullptr || size == 0)
			throw exception("String<T>::assign");
		if (n > capacity)
		{
			while (n > capacity)
				capacity += 10;
			delete[]str;
			str = new T[capacity + 1];
		}
		size = n;
		for (int i = 0; i < size; i++)
			str[i] = c;
		str[size] = '\0';
		return *this;
	}
	catch (exception& ex)
	{
		cerr << "Bad_alloc: " << ex.what();
		return *this;
	}
}

template<typename T>
inline String<T>& String<T>::assign(String<T>&& str) noexcept
{
	*this = std::move(str);
	return *this;
}
//String Assignment
template<typename T>
String<T>& String<T>::assign(const String<T>& str)
{
	try
	{
		if (this->str == nullptr && str.str == nullptr)
			throw bad_alloc();
		if (str.size > capacity)
		{
			while (str.size > capacity)
				capacity += 10;
			delete[]this->str;
			this->str = new T[capacity + 1];
		}
		this->size = str.size;
		for (int i = 0; i < size; i++)
			allocator.construct(this->str + i, str[i]);
		return *this;
	}
	catch (const bad_alloc& ba)
	{
		cerr << "Allocation failed: " << ba.what() << endl;
	}
}
//Method for finding a specific fragment in a string
/*If the string contains n identical characters, then the function returns the original
	position of the very first character
		which matches*/

//String Concatenation
template<typename T>
String<T>& String<T>::append(const String<T>& other, size_t start)
{
	try
	{
		if (other.str == nullptr || str == nullptr || other.size == 0 || size == 0)
			throw exception("String<T>::append");
		else if (start > size || start < 0)
			throw out_of_range("String<T>::append");
		(*this) = (*this) + other.SubStr(start, other.size);
		return *this;
	}
	catch (out_of_range& out)
	{
		cerr << "out_of_range: " << out.what();
		return *this;
	}
	catch (exception& ex)
	{
		cerr << "bad_alloc: " << ex.what();
		return *this;
	}
}
//Adding another string to the original string
template<typename T>
String<T>& String<T>::append(const T* other, size_t num)
{
	try
	{
		if (other == nullptr || str == nullptr || SizeStr(other) == 0 || size == 0)
			throw exception("String<T>::append");
		else if (num > size || num < 0)
			throw out_of_range("String<T>::append");
		(*this) = (*this) + String(other, num);
		return *this;
	}
	catch (out_of_range& out)
	{
		cerr << "out_of_range: " << out.what();
		return *this;
	}
	catch (exception& ex)
	{
		cerr << "bad_alloc: " << ex.what();
		return *this;
	}
}
//Method that adds two strings, for example
/*String s1 = "123" String s2 = "456 result
s1.append(s2,0)
will be 123456*/
template<typename T>
String<T>& String<T>::append(const String<T>& other, size_t start, size_t end)
{
	try
	{
		if (this->str == nullptr || other.str == nullptr)
			throw bad_alloc();
		else if (start <0 || start > size || end < 0)
			throw out_of_range("String<T>::append");
		(*this) = (*this) + other.SubStr(start, end);
		return *this;
	}
	catch (const bad_alloc& ba)
	{
		cerr << "Allocation failed: " << ba.what() << endl;
	}
	catch (const out_of_range& oof)
	{
		cerr << "Out of range: " << oof.what() << endl;
	}
}
template<typename T>
String<T>& String<T>::append(const String<T>& str)
{
	try
	{
		if (this->str == nullptr || str.str == nullptr)
			throw bad_alloc();
	
		(*this) = (*this) + str;
		return *this;
	}
	catch (const bad_alloc ba)
	{
		cerr << "Allocation failed: " << ba.what() << endl;
	}
}
template<typename T>
String<T>& String<T>::append(size_t n, T c)
{
	try
	{
		if (n <0)
			throw invalid_argument("String<T>::append");
		String temp(str);
		for (int i = 0; i < n; i++)
			(*this).Push_back(c);
		return *this;
	}
	catch(const invalid_argument &arg)
	{ 
		cerr << "Invalid argument: " << arg.what() << endl;
	}
}
template<typename T>
template<typename T2>
//Inserting a character, string at any position in a string

String<T>& String<T>::insert(size_t num, const T2* str)
{
	try
	{
		if (str == nullptr)
			throw bad_alloc();
		 if (num > this->size || num < 0)
			throw out_of_range("String<T>::insert");
		 int tempsize = SizeStr(str);
		 if (tempsize + size > capacity)
		 {
			 while (tempsize + size > capacity)
				 capacity += 10;
			 T* buf = allocator.allocate(size+1);
			 for (int i = 0; i < size; i++)
				 buf[i] = this->str[i];
			 buf[size] = 0;
			 allocator.deallocate(this->str, size);
			 this->str = allocator.allocate(capacity);
			 for (int i = 0; i < size; i++)
				 allocator.construct(this->str + i, buf[i]);
			 this->str[size] = 0;
		 }
		String<T> t((*this).SubStr(num, tempsize));
		const T* tempstr = t.c_str();
		int i,j=0;
		size += tempsize;
		for (i = num; i < tempsize; i++)
			this->str[i] = str[i];
		for (i; j < strlen(tempstr);j++, i++)
			 this->str[i] = tempstr[j];
		this->str[size-1] = '\0';
		return *this;
	}
	catch (const bad_alloc &ba)
	{
		cerr << "Allocation failed: " << ba.what() << ": insert()" << endl;
	}
	catch (const out_of_range& oor)
	{
		cerr << "Out of range:  " << oor.what() << endl;
	}
}
//Method that capitalizes all letters
template<typename T>
String<T>& String<T>::upper(size_t start, size_t end)
{
	try
	{
		if (str == nullptr)
			throw bad_alloc();
		if (start <0 || start> size || end <0 || end >size)
			throw out_of_range("String<T>::upper");
		if (start <= 0 && end <= size)
		{
			for (int i = start; i < end; i++)
			{
				if (str[i] >= 65 && str[i] <= 90)
					continue;
				else if (str[i] != ' ')
					str[i] -= 32;
			}
			return *this;
		}
	}
	catch (const bad_alloc& baa) {
		cerr << "Allocation failed: " << baa.what() << endl;
	}
	catch (const out_of_range& oof) {
		cerr << "Out of range: " << oof.what() << endl;
	}
}
//Method that makes all letters small (lowercase)
template<typename T>
String<T>& String<T>::lower(size_t start, size_t end)
{
	try
	{
		if (str == nullptr)
			throw bad_alloc();
		if (start <0 || start> size || end <0 || end >size)
			throw out_of_range("String<T>::lower");
		if (start <= 0 && end <= size)
		{
			for (int i = start; i < end; i++)
			{
				if (str[i] >= 97 && str[i] <= 122)
					continue;
				else if (str[i] != ' ')
					str[i] += 32;
			}
			return *this;
		}
	}
	catch (const bad_alloc& baa) {
		cerr << "Allocation failed: " << baa.what() << endl;
	}
	catch (const out_of_range& oof) {
		cerr << "Out of range: " << oof.what() << endl;
	}
}
//Method for finding a character that is in a specific position

template<typename T>
size_t String<T>::find(T symbol, size_t position)
{
	try
	{
		if ((str == nullptr) &&((int)position > size || (int)position < size))
			throw bad_alloc();
		else if ((int)position > size || (int)position < size)
			throw range_error("String<T>::find");
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
	catch (const range_error &re)
	{
		cerr << "Range error: " << re.what() << endl;
	}
	catch (const bad_alloc& re)
	{
		cerr << "Allocation failed: " << re.what()<<": find()" << endl;
	}
}
template<typename T>
size_t String<T>::find(const T* const str, size_t pos)
{
	try
	{

		if (((int)pos) > size || size == 0 || this->str == nullptr)
			throw length_error( "String<T>::find");
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
	catch (length_error&exp)
	{
		cerr<< "length_error: " << exp.what()<<endl;
		return NULL;
	}
}
template<typename T>
size_t String<T>::find(const T* const str, size_t pos, size_t n)
{
	try
	{
		if (((int)pos) > size || size == 0 || this->str == nullptr)
			throw length_error("String<T>::find");
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
	catch (length_error& exp)
	{
		cerr << "length_error: " << exp.what() << endl;
		return NULL;
	}
}
/*Getter for a string, returns the string it is asking for
	user*/
template<typename T>
const String<T> String<T>::GetStr() const noexcept
{
	return this->str;
}
/*Checking if a string is empty or not
	Returns true or false as result*/
template<typename T>
inline bool String<T>::isEmpty()noexcept
{
	int L = size;
	if (L > 0)
		return 0;
	else
		return 1;
}
//Checking if a string is empty or not
template<typename T>
inline void String<T>::isClear()noexcept
{
	allocator.deallocate(str, size);
	str = allocator.allocate(1);
	str[0] = '\0';
	this->size = 0;
	this->capacity = 0;
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
	if (str.size > str.capacity)
		while (str.size > str.capacity)
			str.capacity += 10;
	str.str = new T[str.capacity + 1];
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
	if (size > capacity)
		while (size > capacity)
			capacity += 10;
	str = allocator.allocate(capacity+1);
	for (int i = 0; i < size+1; i++)
		allocator.construct(str + i, oss1.str()[i]);
	return *this;
}
template<typename T>
inline void String<T>::readfile(const char *nameF,int choose)
{
	ifstream file;
	file.exceptions(ifstream::badbit | ifstream::failbit);
	try
	{
		file.open(nameF);
		char buf[255];
		int tempsize;
		file.getline(buf, 100);
		file.seekg(0, ios_base::end);
		file.close();
		size_t strbuf = SizeStr(buf);
		if (choose == 1)
		{
			allocator.deallocate(str, size);
			if (strbuf > capacity)
				while (strbuf > capacity)
					capacity += 10;
			str = allocator.allocate(capacity + 1);
			size = strbuf;
			for (int i = 0; i < size - 1; i++)
				allocator.construct(str + i, buf[i]);
			allocator.construct(str + size - 1, '\0');
		}
		else if (choose == 2)
			cout << buf << endl;
	}
	catch (const ifstream::failure& ex)
	{
		cout << ex.what() << endl;
		cout << ex.code() << endl;
	}
}

template<typename T>
inline void String<T>::writefile(const char* nameF)
{
	
	try
	{
		ofstream file;
		file.exceptions(ofstream::badbit | ofstream::failbit);
		file.open(nameF);
		file << str;
		file.close();
	}
	catch (const ofstream::failure& exp)
	{
		cout<<exp.what()<<endl;
		cout << exp.code()<<endl;
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
inline size_t String<T>::rfind(const T* str, size_t pos)
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
template<typename T>
template<typename U>
inline String<T>::operator String<U>()
{
	return String<U>(*this);
}
template<typename T>
inline String<T>::operator char* ()
{
	try
	{
		if (str == nullptr)
			throw bad_alloc();
		char* buf = new char[size + 1];
		for (int i = 0; i < size + 1; i++)
			buf[i] = (char)str[i];
		buf[size] = 0;
		return buf;
	}
	catch (const bad_alloc& ba)
	{
		cerr << "Allocation failed: " << ba.what()<<": operator char*" << endl;
	}
}
