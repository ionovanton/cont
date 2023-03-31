
#ifndef FT_REVERSE_ITERATOR_HPP
#define FT_REVERSE_ITERATOR_HPP

#include "iterator_base.hpp"
#include "iterator_traits.hpp"

namespace ft {

template <typename Iterator>
class reverse_iterator : public iterator<typename iterator_traits<Iterator>::iterator_category,
                                         typename iterator_traits<Iterator>::value_type,
                                         typename iterator_traits<Iterator>::difference_type,
                                         typename iterator_traits<Iterator>::pointer,
                                         typename iterator_traits<Iterator>::reference> {
    public:
        typedef Iterator                                              iterator_type;
        typedef typename iterator_traits<Iterator>::value_type        value_type;
        typedef typename iterator_traits<Iterator>::pointer           pointer;
        typedef typename iterator_traits<Iterator>::reference         reference;
        typedef typename iterator_traits<Iterator>::difference_type   difference_type;
        typedef typename iterator_traits<Iterator>::iterator_category iterator_category;

        reverse_iterator(void);
        explicit reverse_iterator(iterator_type const &x);
        reverse_iterator(reverse_iterator const &src);
        template <typename T> reverse_iterator(reverse_iterator<T> const &src);
        ~reverse_iterator(void);
        reverse_iterator &operator=(reverse_iterator const &src);

        reverse_iterator &operator++(void); /* prefixed */
        reverse_iterator  operator++(int);  /* postfixed */
        reverse_iterator &operator+=(difference_type n);
        reverse_iterator  operator+(difference_type n) const;

        reverse_iterator &operator--(void); /* prefixed */
        reverse_iterator  operator--(int);  /* postfixed */
        reverse_iterator &operator-=(difference_type n);
        reverse_iterator  operator-(difference_type n) const;

        reference operator*(void) const;
        pointer   operator->(void) const;

        reference operator[](difference_type n) const;

        iterator_type base(void) const;

    private:
        Iterator _ptr;
};

template <typename L, typename R>
bool operator==(reverse_iterator<L> const &rhs, reverse_iterator<R> const &lhs)
{
    return (rhs.base() == lhs.base());
}

template <typename L, typename R>
bool operator!=(reverse_iterator<L> const &rhs, reverse_iterator<R> const &lhs)
{
    return (rhs.base() != lhs.base());
}

template <typename L, typename R>
bool operator<(reverse_iterator<L> const &rhs, reverse_iterator<R> const &lhs)
{
    return (rhs.base() > lhs.base());
}

template <typename L, typename R>
bool operator<=(reverse_iterator<L> const &rhs, reverse_iterator<R> const &lhs)
{
    return (rhs.base() >= lhs.base());
}

template <typename L, typename R>
bool operator>(reverse_iterator<L> const &rhs, reverse_iterator<R> const &lhs)
{
    return (rhs.base() < lhs.base());
}

template <typename L, typename R>
bool operator>=(reverse_iterator<L> const &rhs, reverse_iterator<R> const &lhs)
{
    return (rhs.base() <= lhs.base());
}

template <typename L, typename R>
typename reverse_iterator<L>::difference_type operator+(reverse_iterator<L> const &rhs,
                                                        reverse_iterator<R> const &lhs)
{
    return (rhs.base() - lhs.base());
}

template <typename L, typename R>
typename reverse_iterator<L>::difference_type operator-(reverse_iterator<L> const &rhs,
                                                        reverse_iterator<R> const &lhs)
{
    return (rhs.base() + lhs.base());
}

} /* namespace ft */

#include "reverse_iterator.tpp"

#endif /* FT_REVERSE_ITERATOR_HPP */
