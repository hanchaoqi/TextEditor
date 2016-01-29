#include <iostream>
#include <string>
//using namespace std;
struct Out_of_range{};

template<class T, class A = std::allocator<T>> class vector{
	int sz, space;
	T* elem;
	A alloc;
	void copy(const vector& arg);
public:
	typedef unsigned long size_type;
	typedef T value_type;
	typedef T* iterator;
	typedef const T* const_iterator;

	vector(const vector&);
	explicit vector(int s)
		:sz(s), space(s), elem(new T[s])
	{
		for (int i = 0; i < s; i++)
			elem[i] = 0;
	}
	vector()
		:sz(0), space(0), elem(0){}
	~vector(){ delete[] elem; }
	int size() const{ return sz; }
	int capacity() const{ return space; }

	vector<T, A>& operator=(const vector&);
	T& operator[](int n);
	const T& operator[](int n) const;

	void resize(int newsize, T val = T());
	void push_back(const T& d);
	void reserve(int newalloc);
	void at(int i);
	void print();

	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;
	size_type size();
};

template<class T, class A> T& vector<T, A>::operator[](int n)
{
	return elem[n];
}
template<class T, class A> const T& vector<T, A>::operator[](int n) const
{
	return elem[n];
}
template<class T, class A> void vector<T, A>::copy(const vector& arg)
{
	for (int i = 0; i < arg.sz; i++)
		elem[i] = arg.elem[i];
}
template<class T, class A> vector<T, A>::vector(const vector& arg)
:sz(arg.sz), space(arg.space), elem(new T[arg.sz])
{
	copy(arg);
}
template<class T, class A> vector<T, A>& vector<T, A>::operator=(const vector& arg)
{
	if (this == &arg)	return *this;

	if (space >= arg.size())
	{
		copy(arg);
		sz = arg.size();
		return *this;
	}

	T* p = new T[arg.size()];
	for (int i = 0; i < arg.size(); i++)
		p[i] = arg.elem[i];
	delete[] elem;
	elem = p;
	space = sz = arg.size();
	return *this;
}
template<class T, class A> void vector<T, A>::resize(int newsize, T val = T())
{
	reserve(newsize);
	for (int i = sz; i < newsize; i++)
		alloc.construct(&elem[i], val);
	for (int i = newsize; i < sz; i++)
		alloc.destroy(&elem[i]);
	sz = newsize;
}
template<class T, class A> void vector<T, A>::push_back(const T& d)
{
	if (space == 0)
		reserve(8);
	else if (sz == space)
		reserve(2 * space);
	alloc.construct(&elem[sz], d);
	sz++;
}
template<class T, class A> void vector<T, A>::reserve(int newalloc)
{
	if (newalloc <= space)
		return;
	T* p = alloc.allocate(newalloc);
	for (int i = 0; i < sz; i++)
		alloc.construct(&p[i], elem[i]);
	for (int i = 0; i < sz; i++)
		alloc.destroy(&elem[i]);
	alloc.deallocate(elem, space);
	elem = p;
	space = newalloc;
}
template<class T, class A> void vector<T, A>::at(int i)
{
	if (i >= 0 && i < sz)
		return elem[i];
	else
		throw Out_of_range();
}
template<class T, class A> void vector<T, A>::print()
{
	for (int i = 0; i < sz; i++)
	{
		std::cout << elem[i] << "\t";
	}
}
template<class T, class A> typename vector<T, A>::iterator vector<T, A>::begin()
{
	return &elem[0];
}
template<class T, class A> typename vector<T, A>::const_iterator vector<T, A>::begin() const
{
	return &elem[0];
}
template<class T, class A> typename vector<T, A>::iterator vector<T, A>::end()
{
	return &elem[sz];
}
template<class T, class A> typename vector<T, A>::const_iterator vector<T, A>::end() const
{
	return &elem[sz];
}
template<class T, class A> typename vector<T, A>::size_type vector<T, A>::size()
{
	return sz;
}
