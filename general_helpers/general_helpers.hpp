
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

#ifndef GENERAL_HELPERS_HPP
# define GENERAL_HELPERS_HPP

namespace ft
{

	template < class T >
		void	value_swap(T &a, T &b)
	{
		T tmp;

		tmp = b;
		b = a;
		a = tmp;
	}

} /* end of namespace */

#endif