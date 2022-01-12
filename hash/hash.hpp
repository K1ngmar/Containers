/* ************************************************************************** */
/*                                                                            */
/*                    (`-').-> (`-')  _  (`-').-> (`-').->                    */
/*                    (OO )__  (OO ).-/  ( OO)_   (OO )__                     */
/*                   ,--. ,'-' / ,---.  (_)--\_) ,--. ,'-'                    */
/*                   |  | |  | | \ /`.\ /    _ / |  | |  |                    */
/*                   |  `-'  | '-'|_.' |\_..`--. |  `-'  |                    */
/*                   |  .-.  |(|  .-.  |.-._)   \|  .-.  |                    */
/*                   |  | |  | |  | |  |\       /|  | |  |                    */
/*                   `--' `--' `--' `--' `-----' `--' `--'                    */
/*                                                                            */
/*                   Kingmar  |  https://github.com/K1ngmar                   */
/*                                                                            */
/* ************************************************************************** */

#ifndef NOT_THE_KIND_OF_HASH_YOU_THINK_IT_IS_HPP
# define NOT_THE_KIND_OF_HASH_YOU_THINK_IT_IS_HPP

# include <cstddef>
# include <is_integral.hpp>
# include <string>
# include <sfinae.hpp>

namespace ft
{

////////////////////////////////////
// Hash function based on murmur2 //
////////////////////////////////////

	/*
	** This hash function is not incremental
	**
	** It won't work on every machine:
	** -------------------------------
	** assumes sizeof(int) == 4
	** assumes it can read 4byte values,
	** from any address without crashing :p
	*/
	template < class T >
		std::size_t funky_hash(T* key, int len, unsigned int seed = 1337)
	{
		const std::size_t	multiplier	= 420 * 69 * (unsigned int)80085;
		const std::size_t	rotate		= 21;
		std::size_t			hash		= seed ^ len;
		const unsigned char *data		= (const unsigned char *)key;
		unsigned int		byte		= *((unsigned int *)data);

		/* hash data per 4 bytes */
		while (len >= 4)
		{
			byte = *((unsigned int *)data);

			byte *= multiplier;
			byte ^= byte >> rotate;
			byte *= multiplier;

			hash ^= multiplier;
			hash ^= byte;

			data += 4;
			len -= 4;
		}

		/* mix in the last few left over bytes */
		switch (len)
		{
			case 3: hash ^= data[2] << 16;
			case 2: hash ^= data[1] << 8;
			case 1: hash ^= data[0];
					hash *= multiplier;
		}

		/* final scramble */
		hash ^= len * byte;

		hash ^= (hash >> 16);
		hash *= multiplier;
		hash ^= (hash >> 13);
		hash *= multiplier;
		hash ^= (hash >> 16);

		return (hash);
	}

/////////////
// Default //
/////////////

	/* non constructable */
	template < class T, bool >
		struct hash_impl
	{
		private:
			hash_impl();
	};

//////////////////////////////////
// integral type specialization //
//////////////////////////////////

	template < class T > 
		struct hash_impl< T, true >
	{
		typedef	T			argument_type;
		typedef std::size_t	result_type;

		result_type operator () (const argument_type& key)
		{
			return (result_type)key;
		}
	}; /* end of integral specialization */

/////////
// ugh //
/////////

	template < class T >
		struct hash : ft::hash_impl<T, ft::is_integral<T>::value>
	{};

///////////////////////////
// String specialization //
///////////////////////////

/*
** Works for everything that inherits from std::basic_string
*/
	template < class T >
		struct hash< std::basic_string<T> >
	{
		typedef	std::basic_string<T>	argument_type;
		typedef std::size_t				result_type;

		result_type operator () (argument_type& key)
		{
			return funky_hash(key.c_str(), key.length(), 42069);
		}

	}; /* end of string specialization */

////////////////////////////
// Pointer specialization //
////////////////////////////

	template< class T >
		struct hash<T*>
	{
		typedef	T*			argument_type;
		typedef std::size_t	result_type;

		/* will hash the address */
		result_type operator () (argument_type key)
		{
			return funky_hash(&key, sizeof(key));
		}

		/* will hash the underlying data not the address itself */
		result_type operator () (argument_type key, int len)
		{
			return funky_hash(key, len);
		}

	}; /* end of pointer specialization */

} /* end of namespace */

#endif