#include <iostream>
#include <string>
using namespace std;
typedef unsigned long size_type;

template<typename InputIterator> void distance(InputIterator first, InputIterator last, size_type& result);

template<class Elem> struct Link
{
	Link<Elem>* prev;
	Link<Elem>* succ;
	Elem val;
};
template<class Elem> class list{
	Link<Elem>* first;
	Link<Elem>* last;
public:
	
	typedef Elem value_type;
	typedef Link<Elem>* link_type;
	class iterator;
	class const_iterator;

	link_type node;

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
	Link<Elem>* curr;
public:
	iterator(Link<Elem>* p) :curr(p){}

	iterator& operator++(){ curr = curr->succ; return *this; }
	iterator& operator--(){ curr = curr->prev; return *this; }
	Elem& operator*(){ return curr->val; }
	iterator operator->(){ return &(operator*()); }
	
	bool operator==(const iterator& b)const{ return curr == b.curr; }
	bool operator!=(const iterator& b)const{ return curr != b.curr; }
};
template<class Elem> class list<Elem>::const_iterator{
	const Link<Elem>* curr;
public:
	const_iterator(const Link* p) :curr(p){}

	const_iterator& operator++(){ curr = curr->succ; return const *this; }
	const_iterator& operator--(){ curr = curr->prev; return const *this; }
	const Elem& operator*(){ return curr->val; }

	bool operator==(const const_iterator& b)const{ return curr == b.curr; }
	bool operator!=(const const_iterator& b)const{ return curr != b.curr; }
};

template<class Elem> typename list<Elem>::iterator list<Elem>::begin()
{
	return first;
}
template<class Elem> typename list<Elem>::const_iterator list<Elem>::begin() const
{
	return first;
}
template<class Elem> typename list<Elem>::iterator list<Elem>::end()
{
	return last;
}
template<class Elem> typename list<Elem>::const_iterator list<Elem>::end() const
{
	return last;
}
template<class Elem> typename size_type list<Elem>::size()
{
	size_type result = 0;
	distance(begin(), end(), result);
	return result;
}

template<class Elem> typename list<Elem>::iterator list<Elem>::insert(iterator p, const Elem& v)
{
	link_type tmp = &(Link(v));
	p->succ->prev = tmp;
	tmp->succ = p->succ;
	p->succ = tmp;
	tmp->prev = p;
	return p;
}
template<class Elem> typename list<Elem>::iterator list<Elem>::erase(iterator p)
{
	if (p == this->begin())
	{
		this->first = p->succ;
		delete p;
		return this;
	}
	p->prev->succ = p->succ;
	p->succ->prev = p->prev;
	delete p;
	return this;
}

template<class Elem> void list<Elem>::push_back(const Elem& v)
{
	link_type tmp = &(Link(v));
	this->last->prev->succ = tmp;
	tmp->prev = this->last->prev;
	tmp->succ = this->last;
	this->last->prev = tmp;
}
template<class Elem> void list<Elem>::push_front(const Elem& v)
{
	link_type tmp = &(Link(v));
	this->first->prev = tmp;
	tmp->succ = this->first;
	this->first = tmp;
}
template<class Elem> void list<Elem>::pop_front()
{
	erase(this->first);
}
template<class Elem> void list<Elem>::pop_back()
{
	erase(this->last->prev);
}

template<class Elem> Elem& list<Elem>::front()
{
	return this->begin()->val;
}
template<class Elem> Elem& list<Elem>::back()
{
	return this->end()->prev->val;
}