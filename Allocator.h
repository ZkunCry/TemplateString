#pragma once
#include <limits>
#include "String.h"
template<typename T>
class Allocator
{
public:

	typedef T   value_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef std::size_t    size_type;
	typedef std::ptrdiff_t difference_type;

	template<class T2>
	struct rebind {
		typedef Allocator<T2> other;
	};

	pointer address(reference value) const;
	const_pointer address(const_reference value) const;
	Allocator()throw();
	Allocator(const Allocator&)throw();
	template <class U>
	Allocator(const Allocator<U>&)throw();
	~Allocator() noexcept;
	size_type max_size() const;
	pointer allocate(size_type num, const void* = 0);
	void construct(pointer p, const T& value);
	void destroy(pointer p);
	void deallocate(pointer p, size_type num);
	template<typename T2>
	friend bool operator ==(const Allocator<T>& lhs, const Allocator<T2>rhs)throw();
	template<typename T2>
	friend bool operator !=(const Allocator<T>& lhs, const Allocator<T2>rhs)throw();

	Allocator<T>& operator = (const Allocator<T>& right) = default;
};

template<typename T>
inline Allocator<T>::pointer Allocator<T>::address(reference value) const
{
	return &value;
}

template<typename T>
inline  Allocator<T>::const_pointer Allocator<T>::address(const_reference value) const
{
	return &value;
}

template<typename T>
inline Allocator<T>::Allocator(const Allocator&)throw()
{
}

template<typename T>
inline Allocator<T>::Allocator()throw()
{

}

template<typename T>
template<class U>
inline Allocator<T>::Allocator(const Allocator<U>&)throw()
{
}

template<typename T>
inline Allocator<T>::~Allocator() noexcept
{
}

template<typename T>
inline Allocator<T>::size_type Allocator<T>::max_size() const
{
	return std::numeric_limits<std::size_t>::max() / sizeof(T);
}

template<typename T>
inline Allocator<T>::pointer Allocator<T>::allocate(size_type num, 
	                                                const void*)
{
	 pointer ret = (pointer)(::operator new(num * sizeof(T)));
	 return ret;
}

template<typename T>
inline void Allocator<T>::construct(pointer p, const T& value)
{
	new((void*)p)T(value);
}

template<typename T>
inline void Allocator<T>::destroy(pointer  p)
{
	((T*)p)->~T();
}

template<typename T>
inline void Allocator<T>::deallocate(pointer p, size_type num)
{
	::operator delete((void*)p);
}
template<typename T,typename T2>
inline bool operator ==(const Allocator<T>& lhs, const Allocator<T2>rhs)throw() {
	return lhs == rhs;
}
template<typename T, typename T2>
inline bool operator !=(const Allocator<T>& lhs, const Allocator<T2>rhs)throw() {
	return !(lhs ==rhs);
}