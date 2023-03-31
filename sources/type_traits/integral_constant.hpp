
#ifndef FT_INTEGRAL_CONSTANT_HPP
#define FT_INTEGRAL_CONSTANT_HPP

namespace ft {

template <typename T, T v>
struct integral_constant {
        static const T                  value = v;
        typedef T                       value_type;
        typedef integral_constant<T, v> type;

        operator value_type() { return (value); }
};

typedef integral_constant<bool, true>  true_type;
typedef integral_constant<bool, false> false_type;

} /* namespace ft */

#endif /* FT_INTEGRAL_CONSTANT_HPP */
