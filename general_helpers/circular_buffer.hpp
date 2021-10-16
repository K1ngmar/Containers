
/* ************************************************************************** */
/*                                                                            */
/*     ▄▀▀▄ ▄▄   ▄▀▀█▄▄▄▄  ▄▀▀▀▀▄     ▄▀▀▄▀▀▀▄  ▄▀▀█▄▄▄▄  ▄▀▀▄▀▀▀▄  ▄▀▀▀▀▄    */ 
/*    █  █   ▄▀ ▐  ▄▀   ▐ █    █     █   █   █ ▐  ▄▀   ▐ █   █   █ █ █   ▐    */ 
/*    ▐  █▄▄▄█    █▄▄▄▄▄  ▐    █     ▐  █▀▀▀▀    █▄▄▄▄▄  ▐  █▀▀█▀     ▀▄      */ 
/*       █   █    █    ▌      █         █        █    ▌   ▄▀    █  ▀▄   █     */ 
/*      ▄▀  ▄▀   ▄▀▄▄▄▄     ▄▀▄▄▄▄▄▄▀ ▄▀        ▄▀▄▄▄▄   █     █    █▀▀▀      */ 
/*     █   █     █    ▐     █        █          █    ▐   ▐     ▐    ▐         */ 
/*     ▐   ▐     ▐          ▐        ▐          ▐                             */ 
/*																			  */
/*                   Kingmar  |  https://github.com/K1ngmar                   */
/*																			  */
/* ************************************************************************** */

#ifndef CIRCULAR_BUFFER_HPP
# define CIRCULAR_BUFFER_HPP

# include <memory>

namespace ft {

	/////////////////////
	// CIRCULAR BUFFER //
	/////////////////////

	template < class T, class Alloc = std::allocator<T> >
		struct circular_buffer
	{
	
	#define CAPACITY 1024

	///////////////
	// type defs //
	///////////////
	public:

		typedef T					value_type;
		typedef	Alloc				allocator_type;
		typedef std::size_t			size_type;
		typedef std::ptrdiff_t		difference_type;
		typedef value_type&			reference;
		typedef const value_type&	const_reference;
		typedef value_type*			pointer;
		typedef const value_type*	const_pointer;

	//////////////////////
	// member variables //
	//////////////////////
	public:

		pointer			_arr;
		size_type		_head;
		size_type		_tail;
		size_type		_capacity;
		size_type		_size;
		allocator_type	_alloc;

	/////////////
	// CoPlIeN //
	/////////////
	public:

		circular_buffer(allocator_type alloc = allocator_type())
			: _capacity(CAPACITY), _size(0), _alloc(alloc)
		{
			_arr = _alloc.allocate(_capacity);
			_head = 0;
			_tail = 0;
		}

		~circular_buffer()
		{
			this->clear();
		}

		circular_buffer(const circular_buffer &x)
			: _size(0)
		{
			_arr = _alloc.allocate(_capacity);
			*this = x;
		}

		circular_buffer&	operator = (const circular_buffer &x)
		{
			if (this->_size > 0)
				this->clear();
			this->_head		= 0;
			this->_tail		= 0;
			for (size_type i = 0; i < this->_capacity; i++)
				this->_construct_element(i, x._arr[i]);
			this->_arr		= x._arr;		/* make a deep copy you imbelic */
			return (*this);
		}

	//////////////////////////////
	// private member functions //
	//////////////////////////////
	private:

		void	_construct_element(size_type& idx, reference val)
		{
			_alloc.construct(&_arr[idx], val);
		}

		void	_destroy_elements()
		{
			for (; _head != _tail; _head++)
				_alloc.destroy(&_arr[_head]);
		}

	///////////////
	// MODIFIERS //
	///////////////
	public:

		void	emplace_back(const reference	val)
		{
			_tail++;
			if (_tail == _capacity)
				_tail = 0;
			this->_construct_element(_tail, val);
			_size++;
		}

		void	emplace_front(reference	val)
		{
			_head--;
			if (_head < 0)
				_head = _capacity - 1;
			this->_construct_element(_head, val);
			_size++;
		}

		void	dequeue_back()
		{
			this->_alloc.destroy(&_arr[_tail]);
			_tail--;
			if (_tail == 0)
				_tail = _capacity - 1;
			_size--;
		}

		void	dequeue_front()
		{
			this->_alloc.destroy(&_arr[_head]);
			_head++;
			if (_head == _capacity)
				_head = 0;
			_size--;
		}

		void	clear()
		{
			this->_destroy_elements();
			_alloc.deallocate(_arr, _capacity);
			_head		= 0;
			_tail		= 0;
			_capacity	= 0;
			_arr		= NULL;
		}

	//////////////
	// CAPACITY //
	//////////////
	public:
	
		bool		is_full()
		{
			return (_head == _tail);
		}

		bool	empty()
		{
			return (_size == 0);
		}

		size_type	size()
		{
			return (_size);
		}

	////////////////////
	// ELEMENT ACCESS //
	////////////////////
	public:

		reference operator[](const size_type& n)
		{
			return (_arr[(_head + n) % _capacity]);
		}

		reference operator[](const size_type& n) const
		{
			return (_arr[(_head + n) % _capacity]);
		}

	}; /* end of circular buffer */

}

#endif
