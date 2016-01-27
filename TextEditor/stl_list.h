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
	size_type max_size()const{ return size_type(-1); }
	reference front(){ return *begin(); }
	const_reference front()const{ return *begin(); }

	reference back(){ return *(--end()); }
	const_reference back(){ return *(--end()); }

	void swap(list<T, Alloc>& x){ __STD::swap(node, x.node); }

	iterator insert(iterator position, const T& x)
	{
		link_type tmp = create_node(x);
		tmp->next = position.node;
		tmp->prev = position.node->prev;
		(link_type(position.node->prev))->next = tmp;
		position.node->prev = tmp;
		return tmp;
	}
	iterator insert(iterator position){ return insert(position, T()); }
#ifdef __STL_MEMBER_TEMPLATES
	template<class InputIterator> void insert(iterator position,InputIterator first,InputIterator last);
#else
	void insert(iterator position, const T* first, const T* last);
	void insert(iterator position, const_iterator first, const_iterator last);
#endif
	void insert(iterator pos, size_type n, const T& x);
	void insert(iterator pos, int n, const T& x)
	{
		insert(pos, (size_type)n, x);
	}
	void insert(iterator pos, long n, const T& x)
	{
		insert(pos, (size_type)n, x);
	}

	void push_front(const T& x){ insert(begin(), x); }
	void push_back(const T& x){ insert(end(), x); }

	iterator erase(iterator position){
		link_type next_node = (link_type)position.node->next;
		link_type prev_node = (link_type)position.node->prev;
		prev_node->next = next_node;
		next_node->prev = prev_node;
		destroy_node(position.node);
		retirn iterator(next_node);
	}
	iterator erase(iterator first, iterator last);
	void resize(size_type new_size, const T& x);
	void resize(size_type new_size){ resize(new_size, T()); }
	void clear();

	void pop_front(){ erase(begin()); }
	void pop_back(){
		iterator tmp = end();
		erase(--tmp);
	}
	list(size_type n, const T& value){ fill_initialize(n, value); }
	list(int n, const T& value){ fill_initialize(n, value); }
	list(long n, const T& value){ fill_initialize(n, value); }
	explicit list(size_type n){ fill_initialize(n, T()); }

#ifdef __STL_MEMBER_TEMPLATES
#else
#endif
};