#pragma once
//Class iterators

template<typename T>
class Iterator // Base Class
{
public:
	using iterator_category = std::forward_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = T;
	using pointer = T*;
	using reference = T&;
	using const_reference = const T&;
	using const_pointer = T*;
	//Constructors
	Iterator(pointer current) :current(current) {}
	Iterator(const Iterator& other);
	//
	reference operator *();
	const_reference operator *()const;
	Iterator& operator = (const Iterator& other);
	Iterator operator+(int n);
	Iterator operator-(int n);
	virtual Iterator& operator++();
	virtual Iterator& operator--();
	virtual Iterator operator--(int i);
	virtual Iterator operator++(int i);
	bool operator ==(const Iterator& other)const;
	bool operator !=(const Iterator& other)const;
	bool operator>(const Iterator& other)const;
	bool operator<(const Iterator& other)const;
	bool operator>=(const Iterator& other)const;
	bool operator<=(const Iterator& other)const;
protected:
	T* current;
};
template<typename T>
class Reverse_Iterator :public Iterator<T> //Inherited class
{
public:

	using iterator_category = std::forward_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = T;
	using pointer = T*;
	using reference = T&;

	Reverse_Iterator(pointer current) :Iterator<T>(current) {}
	Reverse_Iterator(const Reverse_Iterator& other) :Iterator<T>(other.Iterator<T>::current) {};
	Reverse_Iterator& operator = (const Reverse_Iterator& other);
	Iterator<T> operator++(int i)override;
	Iterator<T>& operator++()override;
	Iterator<T> operator--(int i)override;
	Iterator<T>& operator--();
};
template<typename T>
inline Reverse_Iterator<T>& Reverse_Iterator<T>::operator=(const Reverse_Iterator<T>& other)
{
	if (this != &other)
		Iterator<T>::current = other.Iterator<T>::current;
	return *this;
}
template<typename T>
inline Iterator<T>& Reverse_Iterator<T>::operator--()
{
	(++Iterator<T>::current);
	return *this;
}
template<typename T>
inline Iterator<T> Reverse_Iterator<T>::operator--(int i)
{
	Iterator temp = *this;
	++(*this);
	return *this;
}
template<typename T>
inline Iterator<T>& Reverse_Iterator<T>::operator++()
{
	(--Iterator<T>::current);
	return *this;
}
template<typename T>
inline Iterator<T> Reverse_Iterator<T>::operator++(int i)
{
	Iterator temp = *this;
	++(*this);
	return temp;
}
template<typename T>
inline Iterator<T>::Iterator(const Iterator<T>& other) :current(other.current) {}
template<typename T>
inline Iterator<T>::reference Iterator<T>::operator*()
{
	return *current;
}
template<typename T>
inline Iterator<T>::const_reference Iterator<T>::operator*()const
{
	return *current;
}

template<typename T>
inline Iterator<T>& Iterator<T>::operator=(const Iterator<T>& other)
{
	if (this != &other)
		current = other.current;
	return *this;
}

template<typename T>
inline Iterator<T> Iterator<T>::operator+(int n)
{
	current += n;
	return current;
}
template<typename T>
inline Iterator<T> Iterator<T>::operator-(int n)
{
	current -= n;
	return current;
}
template<typename T>
inline Iterator<T>& Iterator<T>::operator++()
{
	++current;
	return *this;
}
template<typename T>
inline Iterator<T>& Iterator<T>::operator--()
{
	--current;
	return *this;
}
template<typename T>
inline Iterator<T> Iterator<T>::operator--(int i)
{
	Iterator temp(current);
	--current;
	return  temp;
}
template<typename T>
inline  Iterator<T> Iterator<T>::operator++(int i)
{
	Iterator temp(*this);
	++current;
	return temp;
}
template<typename T>
bool Iterator<T>::operator==(const Iterator<T>& other)const
{
	return (current == other.current);
}
template<typename T>
bool Iterator<T>::operator!=(const Iterator<T>& other)const
{
	return !(current == other.current);
}
template<typename T>
inline bool Iterator<T>::operator>(const Iterator& other) const
{
	return current > other.current;
}
template<typename T>
inline bool Iterator<T>::operator<(const Iterator& other) const
{
	return !(current > other.current);
}
template<typename T>
inline bool Iterator<T>::operator>=(const Iterator& other) const
{
	return current >= other.current;
}
template<typename T>
inline bool Iterator<T>::operator<=(const Iterator& other) const
{
	return (current >= other.current);
}

