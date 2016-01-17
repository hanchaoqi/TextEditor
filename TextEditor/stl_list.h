#include <iostream>
#include <string>
using namespace std;
struct Out_of_range{};

template<class Elem> struct Link
{
	Link* prev;
	Link* succ;
	Elem val;
};
template<class Elem> class list{
	Link<Elem>* first;
	Link<Elem>* last;
public:
	typedef unsigned long size_type;
	typedef Elem value_type;
	class iterator;
	class const_iterator;

	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;

	size_type size();

	iterator insert(iterator p, const Elem& v);
	iterator erase(iterator p);

	void push_back(const Elem& v);
	void push_front(const Elem& v);
	void pop_front();
	void pop_back();

	Elem& front();
	Elem& back();
};

template<class Elem> class list<Elem>::iterator{
	Link<Elem>* cur;
public:
	iterator(Link<Elem>* p) :curr(p){}

	iterator& operator++(){ curr = curr->succ; return *this; }
	iterator& operator--(){ curr = curr->prev; return *this; }
	Elem& operator*(){ return curr->val; }

	bool operator==(const iterator& b)const{ return curr == b.curr; }
	bool operator!=(const iterator& b)const{ return curr != b.curr; }
};
template<class Elem> class list<Elem>::const_iterator{
	const Link<Elem>* cur;
public:
	const_iterator(const Link* p) :curr(p){}

	const_iterator& operator++(){ curr = curr->succ; return const *this; }
	const_iterator& operator--(){ curr = curr->prev; return const *this; }
	const Elem& operator*(){ return curr->val; }

	bool operator==(const const_iterator& b)const{ return curr == b.curr; }
	bool operator!=(const const_iterator& b)const{ return curr != b.curr; }
};
template<class Elem> list<Elem>::iterator list<Elem>::begin()
{
	return iterator(first);
}
template<class Elem> list<Elem>::const_iterator list<Elem>::begin() const
{
	return iterator(first);
}
template<class Elem> list<Elem>::iterator list<Elem>::end()
{
	return iterator(last);
}
template<class Elem> list<Elem>::const_iterator list<Elem>::end() const
{
	return iterator(last);
}
template<class Elem> list<Elem>::size_type list<Elem>::size()
{
	return last - first;
}

iterator insert(iterator p, const Elem& v);
iterator erase(iterator p);

void push_back(const Elem& v);
void push_front(const Elem& v);
void pop_front();
void pop_back();

Elem& front();
Elem& back();
