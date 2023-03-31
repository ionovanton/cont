
#ifndef FT_PAIR_TPP
#define FT_PAIR_TPP

#include "pair.hpp"

namespace ft {

template <typename T1, typename T2>
pair<T1, T2>::pair(void) : first(), second()
{
}

template <typename T1, typename T2>
template <typename U, typename V>
pair<T1, T2>::pair(pair<U, V> const &src) : first(src.first), second(src.second)
{
}

template <typename T1, typename T2>
pair<T1, T2>::pair(first_type const &x, second_type const &y) : first(x), second(y)
{
}

template <typename T1, typename T2>
pair<T1, T2>::~pair(void)
{
}

template <typename T1, typename T2>
pair<T1, T2> &pair<T1, T2>::operator=(pair const &rhs)
{
    first  = rhs.first;
    second = rhs.second;
    return (*this);
}

} /* namespace ft */

#endif /* FT_PAIR_TPP */
