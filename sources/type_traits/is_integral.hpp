
#ifndef FT_IS_INTEGRAL_HPP
#define FT_IS_INTEGRAL_HPP

#include "integral_constant.hpp"

namespace ft {

template <typename T>
struct is_integral : public false_type {};

template <typename T>
struct is_integral<T const> : is_integral<T> {};

template <typename T>
struct is_integral<T volatile> : is_integral<T> {};

template <typename T>
struct is_integral<const volatile T> : is_integral<T> {};

template <>
struct is_integral<bool> : public true_type {};

template <>
struct is_integral<wchar_t> : public true_type {};

template <>
struct is_integral<signed char> : public true_type {};

template <>
struct is_integral<char> : public true_type {};

template <>
struct is_integral<short> : public true_type {};

template <>
struct is_integral<int> : public true_type {};

template <>
struct is_integral<long> : public true_type {};

template <>
struct is_integral<long long> : public true_type {};

template <>
struct is_integral<unsigned char> : public true_type {};

template <>
struct is_integral<unsigned short> : public true_type {};

template <>
struct is_integral<unsigned int> : public true_type {};

template <>
struct is_integral<unsigned long> : public true_type {};

template <>
struct is_integral<unsigned long long> : public true_type {};

} /* namespace ft */

#endif /* FT_IS_INTEGRAL_HPP */
