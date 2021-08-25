/* ************************************************************************** */
/*	      __   __   ______     ______     ______   ______     ______		  */
/*	     /\ \ / /  /\  ___\   /\  ___\   /\__  _\ /\  __ \   /\  == \		  */
/*	     \ \ \'/   \ \  __\   \ \ \____  \/_/\ \/ \ \ \/\ \  \ \  __<		  */
/*	      \ \__|    \ \_____\  \ \_____\    \ \_\  \ \_____\  \ \_\ \_\ 	  */
/*	       \/_/      \/_____/   \/_____/     \/_/   \/_____/   \/_/ /_/ 	  */
/*																			  */
/*                   Kingmar  |  https://github.com/K1ngmar                   */
/*																			  */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <exception>
# include <string>
# include <iterator.hpp>
# include <iostream>
# include <sfinae.hpp>

/*
**	Exception defines
*/
# define COLOR_RED		"\033[31m"
# define COLOR_GREEN	"\033[32m"
# define COLOR_RESET	"\033[0m"
# define COLOR_YELLOW	"\033[33m"

# define SYSCALL_FAIL	"system call failed"
# define ALLOC_FAIL		"failed to allocate region"
# define LENGTH_ERROR	"length error"
# define OUT_OF_RANGE	"index is out of range"

namespace ft {

//////////////////
// vector class //
//////////////////

	template < class T, class Alloc = std::allocator<T> >
		class vector {
		
		///////////////
		// type defs //
		///////////////
		public:

			typedef T																					value_type;
			typedef Alloc																				allocator_type;
			typedef std::size_t																			size_type;
			typedef std::ptrdiff_t																		difference_type;
			typedef value_type&																			reference;
			typedef const value_type&																	const_reference;
			typedef value_type*																			pointer;
			typedef const value_type*																	const_pointer;
			typedef ft::iterator<ft::random_access_iterator_tag, T>										iterator;
			typedef ft::iterator<ft::random_access_iterator_tag, T, std::ptrdiff_t, const T*, const T&>	const_iterator;
			typedef ft::reverse_iterator< iterator >													reverse_iterator;
			typedef ft::reverse_iterator< const_iterator >												const_reverse_iterator;

		//////////////////////
		// Member variables //
		//////////////////////
		private:

			value_type*		_arr;
			size_type		_size;
			size_type		_capacity;
			allocator_type	_alloc;

		/////////////
		// CoPlIeN //
		/////////////
		public:

			explicit vector(const allocator_type& alloc = allocator_type()) 
				: _arr(NULL), _size(0), _capacity(0), _alloc(alloc)  {}

			explicit vector(size_type n, const value_type& val = value_type(), 
				const allocator_type& alloc = allocator_type())
				: _arr(NULL), _size(0), _capacity(0), _alloc(alloc)  
			{
				assign(n, val);
			}

			template <class InputIterator>
				vector(InputIterator first, InputIterator last,
					const allocator_type& alloc = allocator_type())
					: _arr(NULL), _size(0), _capacity(0), _alloc(alloc)
			{
				assign(first, last);
			}

			vector(const vector& x) : _arr(NULL)
			{
				*this = x;
			}

			virtual ~vector()
			{
				_alloc.deallocate(this->_arr, this->_capacity);
			}

			vector&	operator = (const vector &x)
			{
				if (this->_arr)
					this->clear();
				this->_size = x._size;
				this->_capacity = x._capacity;
				this->_alloc = x._alloc;
				this->_arr = this->_alloc.allocate(sizeof(T) * x._capacity);
				for (size_type i = 0; i < x._size; i++)
					this->_alloc.construct(&this->_arr[i], x._arr[i]);
				return (*this);
			}
		
		//////////////////////////////
		// Private member functions //
		//////////////////////////////
		private:
	
			void	_destruction(void)
			{
				for (int i = this->_size; i > 0; i--)
					this->pop_back();
				this->_alloc.deallocate(this->_arr, this->_capacity);
			}

			void	_resize(size_type n)
			{
				if (n <= 0)
					n = 1;
				else if (n < (_capacity + (_capacity >> 1)))
					n = (_capacity + (_capacity >> 1));
				_realloc(n);
			}

			void	_realloc(size_type n)
			{
				pointer	tmp;

				if (n > max_size())
					throw veception(LENGTH_ERROR, "reserve", std::to_string(n));
				tmp = _alloc.allocate(sizeof(T) * n);
				size_type i = 0;
				for (; i < _size && i < n; i++)
					this->_alloc.construct(&tmp[i], _arr[i]);
				if (this->_arr)
					this->_destruction();
				_arr = tmp;
				_size = i;
				_capacity = n;
			}

			void	_erase_elem(size_type idx)
			{
				this->_alloc.destroy(&this->_arr[idx]);
				_size--;
			}

			void	_move_elem_back(iterator pos)
			{
				for (; pos != end(); pos++)
					*pos = *(pos + 1);
			}
	
		///////////////
		// ITERATORS //
		///////////////
		public:

			iterator				begin() {
				return (iterator(this->_arr));
			}

			const_iterator			begin() const {
				return (const_iterator(this->_arr));
			}
	
			iterator				end() {
				return (iterator(&this->_arr[this->_size]));
			}

			const_iterator			end() const {
				return (const_iterator(&this->_arr[this->_size]));
			}

			reverse_iterator		rbegin() {
				return (reverse_iterator(&this->_arr[this->_size]));
			}

			const_reverse_iterator	rbegin() const {
				return (const_reverse_iterator(&this->_arr[this->_size]));
			}

			reverse_iterator		rend() {
				return (reverse_iterator(this->_arr));
			}

			const_reverse_iterator	rend() const {
				return (const_reverse_iterator(this->_arr));
			}

		//////////////
		// CAPACITY //
		//////////////
		public:

			size_type	size() const
			{
				return (_size);
			}

			size_type	max_size() const
			{
				return (_alloc.max_size());
			}

			void		resize(size_type n, value_type val = value_type())
			{
				_realloc(n);
				for (size_type i = _size; i < _capacity; i++)
					_arr[i] = val;
			}

			size_type	capacity() const
			{
				return (this->_capacity);
			}

			bool		empty() const
			{
				return (this->_size == 0);
			}

			void		reserve(size_type n)
			{
				if (_capacity < n)
					_realloc(n);
			}

		////////////////////
		// ELEMENT ACCESS //
		////////////////////
		public:

			reference		operator[](size_type n)
			{
				return (_arr[n]);
			}

			const_reference	operator[](size_type n) const
			{
				return (_arr[n]);
			}

			reference		at(size_type n)
			{
				if (n < 0 || n > _size)
					throw veception(OUT_OF_RANGE, "at()", std::to_string(n));
				return (_arr[n]);
			}

			const_reference	at(size_type n) const
			{
				if (n < 0 || n > _size)
					throw veception(OUT_OF_RANGE, "at() const", std::to_string(n));
				return (_arr[n]);
			}

			reference		front()
			{
				return (_arr[0]);
			}

			const_reference	front() const
			{
				return (_arr[0]);
			}

			reference		back()
			{
				return (_arr[_size - 1]);
			}

			const_reference	back() const
			{
				return (_arr[_size - 1]);
			}


		///////////////
		// MODIFIERS //
		///////////////
		public:

			template	<class InputIterator, typename ft::iterator_traits<InputIterator>::iterator_category>
				void		assign(InputIterator first, InputIterator last)
				{
					if (ft::distance(first, last) > _capacity)
						_realloc(ft::distance(first, last) + _capacity);
					size_type i = 0;
					for (; first != last && i < _capacity; first++ && i++)
						_arr[i] = *first;
					_size = i;
				}

			void		assign(size_type n, const value_type& val)
			{
				if (n > _capacity)
					_realloc(n + _capacity);
				size_type i = 0;
				for (; i < n; i++)
					this->_alloc.construct(&_arr[i], val);
				_size = i;
			}

			void		push_back(const value_type& val)
			{
				if (_size + 1 >= _capacity)
					_resize(_size + 1);
				this->_alloc.construct(&_arr[_size], val);
				_size++;
			}

			void		pop_back()
			{
				if (this->_size <= 0)
					return ;
				_size--;
				this->_alloc.destroy(&this->_arr[_size]);
			}

			iterator	insert(iterator position, const value_type& val)
			{
				size_type distance = ft::distance(begin(), position);
				insert (position, 1, val);
				return (begin() + distance);
			}	

			void 		insert(iterator position, size_type n, const value_type& val)
			{
				if (_size + n >= _capacity)
					_realloc(n + _size);
				for (iterator i = end() + n; i > position && i > begin(); i--)
					_arr[i] = i - n;
				for (size_type i = 0; i < n; i++)
					position + i = val;
				_size += n;
			}

			template	<class InputIterator>
				void 		insert(iterator position, InputIterator first, InputIterator last)
				{
					size_type	dist = ft::distance(first, last);
			
					if (_size + dist > _capacity)
						_realloc(_size + dist);
					for (iterator i = end() + dist; i > position && i > begin(); i--)
						_arr[i] = i - dist;
					for (size_type i = 0; i < dist; i++)
						position + i = first + i;
					_size += dist;
				}

			iterator	erase(iterator position)
			{
				difference_type	idx = ft::distance(this->begin(), position);

				this->_erase_elem(idx);
				this->_move_elem_back(position);
				return (position);
			}

			iterator	erase(iterator first, iterator last)
			{
				difference_type	idx		= ft::distance(this->begin(), first);
				difference_type	lidx	= ft::distance(this->begin, last);

				while (idx != lidx) {
					this->_erase_elem(idx);
					idx++;
					_size--;
				}
				// shits broken af! gotta push remainder back yo
				return (first);
			}

			void		swap(vector& x)
			{
				_size = 0;
				this->insert(this->begin(), x.begin(), x.end());
			}

			void		clear()
			{
				_destruction();
				_arr = NULL;
				_size = 0;
				_capacity = 0;
			}

		///////////////
		// ALLOCATOR //
		///////////////
		public:

			allocator_type	get_allocator() const
			{
				return (_alloc);
			}

		////////////////
		// EXCEPTIONS //
		////////////////
		public:

		class veception : public std::exception
		{
			private:
				std::string _msg;

			public:
				veception(std::string msg, std::string type, std::string val)
				{
					_msg = std::string("[") + COLOR_GREEN + type + COLOR_RESET + std::string("] ") + 
						COLOR_RED + std::string("Error: ") + COLOR_RESET + msg + 
						std::string(" <") + COLOR_YELLOW + val + COLOR_RESET + std::string(">"); 
				}
				const char* what() const throw()
				{
					return (_msg.c_str());
				}
				~veception() throw() {};
		};
	};
}

#endif
