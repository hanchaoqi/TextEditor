template<class T> struct __list_node{
	typedef void* void_pointer;
	void_pointer next;
	void_pointer prev;
	T data;
};

template<class T, class Ref, class Ptr> struct __list_iterator{
	typedef __list_iterator<T, T&, T*> iterator;
	typedef __list_iterator<T, const T&, const T*> const_iterator;
	typedef __list_iterator<T, Ref, Ptr> self;

	typedef bidirectional_iterator_tag iterator_category;
	typedef T value_type;
	typedef Ref reference;
	typedef Ptr pointer;
	typedef __list_node<T>* link_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

	link_type node;

	__list_iterator(link_type x) :node(x){}
	__list_iterator(){}
	__list_iterator(const iterator& x) :node(x.node){}

	bool operator==(const self& x)const{ return node == x.node; }
	bool operator!=(const self& x)const{ return node != x.node; }

	reference operator*()const{ return (*node).data; }

	pointer operator->()const{ return &(operator*()); }

	self& operator++(){
		node = (link_type)((*node).next);
		return *this;
	}
	self& operator++(int){
		self tmp = *this;
		++*this;
		return tmp;
	}
	self& operator--(){
		node = (link_type)((*node).prev);
		return *this;
	}
	self& operator--(int){
		self tmp = *this;
		--*this;
		return tmp;
	}
};
#ifndef __STL_CLASS_PARTIAL_SPECIALIZATION
template<class T, class Ref, class Ptr> inline bidirectional_iterator_tag 
iterator_category(const __list_iterator<T, Ref, Ptr>&)
{
	return bidirectional_iterator_tag();
}

template<class T, class Ref, class Ptr> inline T* 
value_type(const __list_iterator<T, Ref, Ptr>&){
	return 0;
}

template<class T, class Ref, class Ptr> inline ptrdiff_t*
distance_type(const __list_iterator<T, Ref, Ptr>&){
	return 0;
}
#endif /*__STL_CLASS_PARTIAL_SPECIALIZATION*/

template<class T, class Alloc = alloc> class list{
protected:
	typedef void* void_pointer;
	typedef  __list_node<T> list_node;
	typedef simple_alloc<list_node, Alloc> list_node_allocator;
public:
	typedef T value_type;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef list_node* link_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

public:
	typedef __list_iterator<T, T&, T*>	iterator;
	typedef __list_iterator<T, const T&, const T*> const_iterator;

#ifdef __STL_CLASS_PARTIAL_SPECIALIZATION
	typedef reverse_iterator<const_iterator> const_reverse_iterator;
	typedef reverse_iterator<iterator> reverse_iterator;
#else
	typedef reverse_bidirectional_iterator<const_iterator, value_type, 
		const_reference, difference_type> const_reverse_iterator;
	typedef reverse_bidirectional_iterator<iterator, value_type, 
		reference, difference_type> reverse_iterator;
#endif /*__STL_CLASS_PARTIAL_SPECIALIZATION*/
protected:
	link_type node;
	link_type get_node(){ return list_node_allocator::allocate(); }
	void put_node(link_type p){ list_node_allocator::deallocate(p); }

	link_type create_node(const T& x){
		link_type p = get_node();
		__STL_TRY{
			construct(&p->data, x);
		}
		__STL_UNWIND(put_node(p));
		return p;
	}
	void destroy_node(link_type p){
		destroy(&p->data);
		put_node(p);
	}

	void empty_initialize(){
		node = get_node();
		node->prev = node;
		node->next = node;
	}
	void fill_initialize(size_type n, const T& value)
	{
		empty_initialize();
		__STL_TRY{
			insert(begin(), n, value);
		}
		__STL_UNWIND(clear(); put_node(node));
	}
#ifdef __STL_MEMBER_TEMPLATES  
	template<class InputIterator>
	void range_initialize(InputIterator first, InputIterator last)
	{
		empty_initialize();
		__STL_TRY{
			insert(begin(), first, last);
		}
		__STL_UNWIND(clear(); put_node(node));
	}
#else
	void range_initialzie(const T* first, const T* last)
	{
		empty_initialize();
		__STL_TRY{
			insert(begin(), first, last);
		}
		__STL_UNWIND(clear(); put_node(node));
	}
	void range_initialize(const_iterator first, const_iterator last)
	{
		empty_initialize();
		__STL_TRY{
			insert(begin(), first, last);
		}
		__STL_UNWIND(clear(); put_node(node));
	}
#endif

public:
	list(){ empty_initialize(); }
	iterator begin(){ return (link_type)((*node).next); }
	const_iterator begin()const { return (link_type)((*node).next); }

	iterator end(){ return node; }
	const_iterator end()const{ return node; }

	reverse_iterator rbegin(){ return reverse_iterator(begin()); }
	const_reverse_iterator rbegin()const{ return reverse_iterator(begin()); }

	bool empty()const{ return node->next == node; }
	size_type size() const{
		size_type result = 0;
		distance(begin(), end(), result);
		return result;
	}
};