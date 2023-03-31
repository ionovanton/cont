
#ifndef FT_EQUAL_HPP
#define FT_EQUAL_HPP

namespace ft {

template <typename Iter1, typename Iter2>
bool equal(Iter1 first1, Iter1 last1, Iter2 first2)
{
    while (first1 != last1) {
        if (*first1 != *first2)
            return (false);
        ++first1;
        ++first2;
    }
    return (true);
}

template <typename Iter1, typename Iter2, typename BinaryPredicate>
bool equal(Iter1 first1, Iter1 last1, Iter2 first2, BinaryPredicate is_equal)
{
    while (first1 != last1) {
        if (!is_equal(*first1, *first2))
            return (false);
        ++first1;
        ++first2;
    }
    return (true);
}

} /* namespace ft */

#endif /* FT_EQUAL_HPP */
