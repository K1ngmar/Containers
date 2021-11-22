/* ************************************************************************** */
/*                                                                            */
/*                              o   o   O   o--o                              */
/*                              |\ /|  / \  |   |                             */
/*                              | O | o---o O--o                              */
/*                              |   | |   | |                                 */
/*                              o   o o   o o                                 */
/*																			  */
/*                   Kingmar  |  https://github.com/K1ngmar                   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_SUPER_EPIC_MAP_HPP
# define MY_SUPER_EPIC_MAP_HPP

# include <memory>
# include <pair.hpp>
# include <rnb_tree.hpp>
# include <utility.hpp>
# include <map_iterator.hpp>
# include <rotareti.hpp>

namespace ft
{

////////////
// MAPPIE //
////////////

	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
		class map
	{

	///////////////
	// type defs //
	///////////////
	public:
			
		typedef Key																	key_type;
		typedef T																	mapped_type;
		typedef ft::pair<key_type, mapped_type>										value_type;
		typedef Compare																key_compare;
		typedef Alloc																allocator_type;
		typedef typename allocator_type::reference									reference;
		typedef typename allocator_type::const_reference							const_reference;
		typedef typename allocator_type::pointer									pointer;
		typedef typename allocator_type::const_pointer								const_pointer;
		typedef ft::rnb_tree<key_type, mapped_type, key_compare, allocator_type>	tree_type;
		typedef typename tree_type::node											node;
		typedef typename tree_type::difference_type									difference_type;
		typedef typename tree_type::size_type										size_type;

		/* iterators fkdjfkjdskfjdksjf */

		typedef ft::map_iterator< value_type, node, difference_type, ft::bidirectional_iterator_tag >										iterator;
		typedef ft::map_iterator< value_type, node, difference_type, ft::bidirectional_iterator_tag, const value_type*, const value_type& >	const_iterator;
		typedef ft::reverse_iterator< iterator >																							reverse_iterator;
		typedef ft::reverse_iterator< const_iterator >																						const_reverse_iterator;

	//////////////////////
	// Member variables //
	//////////////////////
	private:

		tree_type	_tree;

	/////////////
	// CoPlIeN //
	/////////////
	public:
	
		/* default constructor */
		explicit map (const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type())
				: _tree(tree_type(comp, alloc))
		{
		}

		/* range constructor */
		template <class InputIterator>
			map (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
					: _tree(tree_type(comp, alloc))
		{
			for (; first != last; first++)
				_tree.insert(*first);
		}

		~map()
		{
			this->clear();
		}

		map (const map& x)
		{
			*this = x;
		}

		map& operator = (const map &x)
		{
			this->_tree = x._tree;
			return (*this);
		}
	
	//////////////////////
	// Helper functions //
	//////////////////////
	private:

		iterator	_lower_bound(const key_type& k) const
		{
			iterator ret = this->find(k);

			if (ret != this->end())
				return (ret);
			ret = this->begin();
			while (ret != this->end() && _tree.comp(k, (*ret).first) == false)
				++ret;
			return (ret);
		}

		iterator	_upper_bound(const key_type& k) const
		{
			iterator ret;
			for (ret = this->begin(); ret != this->end(); ++ret) {
				if (_tree.comp(k, (*ret).first) == true) {
					if (_tree.comp((*ret).first, k) == true)
						continue ;
					break ;
				}
			}
			return (ret);
		}

	//////////////////
	// Iterators 🤮 //
	//////////////////
	public:

		iterator begin()
		{
			return (iterator(_tree.begin->parent));
		}

		const_iterator begin() const
		{
			return (iterator(_tree.begin->parent));
		}

		iterator end()
		{
			return (iterator(_tree.end));
		}

		const_iterator end() const
		{
			return (iterator(_tree.end));
		}

		reverse_iterator rbegin()
		{
			return (reverse_iterator(_tree.end));
		}

		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(_tree.end));
		}

		reverse_iterator rend()
		{
			return (reverse_iterator(_tree.begin));
		}

		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(_tree.begin));
		}

	//////////////
	// Capacity //
	//////////////
	public:

		bool empty() const
		{
			return (_tree.empty());
		}

		size_type size() const
		{
			return (_tree.size);
		}

		size_type max_size() const
		{
			return (_tree.max_size());
		}

	////////////////////
	// Element access //
	////////////////////
	public:

		mapped_type& operator[] (const key_type& k)
		{
			return (*((this->insert(ft::make_pair(k, mapped_type()))).first)).second;
		}

	///////////////
	// Modifiers //
	///////////////
	public:

		/* single element */
		// node*	insert(const value_type& val)
		ft::pair<iterator, bool> insert(const value_type& val)
		{
			ft::pair<node*, bool> inserted = _tree.insert(val);
			return (ft::make_pair(iterator(inserted.first), inserted.second));
		}

		/* with hint */
		// iterator insert(iterator position, const value_type& val)
		// {

		// }
	
		// /* range */
		// template <class InputIterator>
		// 	void insert(InputIterator first, InputIterator last)
		// {
			
		// }

		/* itr erase */
		void erase(iterator position)
		{
			_tree.erase(position.get_ptr());
		}

		/* value erase */
		// size_type erase(const key_type& k)
		// {

		// }

		/* range erase */
		void erase(iterator first, iterator last)
		{
			for (; first != last; first++)
				this->_tree.erase(first.get_ptr());
		}

		void swap(map& x)
		{
			this->_tree.swap(x._tree);
		}

		void clear()
		{
			this->_tree.clear();
		}
	
	///////////////
	// Observers //
	///////////////
	public:

		key_compare key_comp() const
		{
			return (_tree.key_comp());
		}

		// value_compare value_comp() const
		// {

		// }
	
	////////////////
	// Operations //
	////////////////
	public:

		iterator find(const key_type& k)
		{
			return (iterator(_tree.find(k)));
		}

		const_iterator find(const key_type& k) const
		{
			return (const_iterator(_tree.find(k)));
		}

		size_type count(const key_type& k) const
		{
			if (_tree.find(k) == _tree.end)
				return (false);
			return (true);
		}

		iterator lower_bound(const key_type& k)
		{
			return (this->_lower_bound(k));
		}

		const_iterator lower_bound(const key_type& k) const
		{
			return (this->lower_bound(k));
		}

		iterator upper_bound(const key_type& k)
		{
			return (_upper_bound(k));
		}

		const_iterator upper_bound(const key_type& k) const
		{
			return (_upper_bound(k));
		}

		ft::pair<iterator, iterator> equal_range(const key_type& k)
		{
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		}

		ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const
		{
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		}

	}; /* end of map */

} /* end of namespace */

#endif
