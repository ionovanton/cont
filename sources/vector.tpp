/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:01:01 by maolivei          #+#    #+#             */
/*   Updated: 2023/02/21 19:37:14 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_TPP
#define FT_VECTOR_TPP

#include "vector.hpp"

namespace ft {

/********************** CONSTRUCTORS, DESTRUCTOR AND ASSIGN OPERATOR **********************/

template <typename T, typename Alloc>
vector<T, Alloc>::vector(vector const &src) :
    _data(NULL),
    _capacity(0),
    _size(0),
    _allocator(src._allocator)
{
    *this = src;
}

template <typename T, typename Alloc>
vector<T, Alloc>::vector(Alloc const &alloc) :
    _data(NULL),
    _capacity(0),
    _size(0),
    _allocator(alloc)
{
}

template <typename T, typename Alloc>
vector<T, Alloc>::vector(size_type n, T const &value, Alloc const &alloc) :
    _data(NULL),
    _capacity(n),
    _size(n),
    _allocator(alloc)
{
    if (_size > max_size())
        throw std::length_error("vector ctor");
    _data = _allocator.allocate(_size);
    if (!_data)
        throw std::bad_alloc();
    for (size_type i = 0; i < _size; ++i)
        _allocator.construct((_data + i), value);
}

template <typename T, typename Alloc>
template <typename Iter>
vector<T, Alloc>::vector(Iter         first,
                         Iter         last,
                         Alloc const &alloc,
                         typename enable_if<!is_integral<Iter>::value>::type *) :
    _data(NULL),
    _capacity(ft::distance(first, last)),
    _size(ft::distance(first, last)),
    _allocator(alloc)
{
    if (_size > max_size())
        throw std::length_error("vector ctor");
    _data = _allocator.allocate(_size);
    if (!_data)
        throw std::bad_alloc();
    for (size_type i = 0; i < _size; ++i)
        _allocator.construct((_data + i), *(first + i));
}

template <typename T, typename Alloc>
vector<T, Alloc>::~vector(void)
{
    clear();
    _allocator.deallocate(_data, _capacity);
}

template <typename T, typename Alloc>
vector<T, Alloc> &vector<T, Alloc>::operator=(vector const &src)
{
    if (this == &src)
        return (*this);
    clear();
    if (_capacity > 0)
        _allocator.deallocate(_data, _capacity);
    _allocator = src._allocator;
    _size      = src._size;
    _capacity  = src._capacity;
    _data      = _allocator.allocate(_capacity);
    if (!_data)
        throw std::bad_alloc();
    for (size_type i = 0; i < _size; ++i)
        _allocator.construct((_data + i), *(src._data + i));
    return (*this);
}

/**************************************** ITERATORS ***************************************/

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::begin(void)
{
    return (iterator(_data));
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_iterator vector<T, Alloc>::begin(void) const
{
    return (const_iterator(_data));
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::end(void)
{
    return (iterator(_data + _size));
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_iterator vector<T, Alloc>::end(void) const
{
    return (const_iterator(_data + _size));
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rbegin(void)
{
    return (reverse_iterator(end()));
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rbegin(void) const
{
    return (const_reverse_iterator(end()));
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rend(void)
{
    return (reverse_iterator(begin()));
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rend(void) const
{
    return (const_reverse_iterator(begin()));
}

/**************************************** CAPACITY ****************************************/

template <typename T, typename Alloc>
bool vector<T, Alloc>::empty(void) const
{
    return (!_size);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::size(void) const
{
    return (_size);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::max_size(void) const
{
    return (_allocator.max_size());
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::capacity(void) const
{
    return (_capacity);
}

template <typename T, typename Alloc>
void vector<T, Alloc>::reserve(size_type new_cap)
{
    pointer   tmp;
    size_type i;

    if (new_cap <= _capacity)
        return;
    if (new_cap > max_size())
        throw std::length_error("vector::reserve()");
    tmp = _allocator.allocate(new_cap);
    if (!tmp)
        throw std::bad_alloc();
    for (i = 0; i < _size; ++i)
        _allocator.construct((tmp + i), *(_data + i));
    clear();
    _allocator.deallocate(_data, _capacity);
    _data     = tmp;
    _size     = i;
    _capacity = new_cap;
}

/************************************* ELEMENT ACCESS *************************************/

template <typename T, typename Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::at(size_type pos)
{
    if (pos >= _size)
        throw std::out_of_range("vector::at()");
    return (*(begin() + pos));
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::at(size_type pos) const
{
    if (pos >= _size)
        throw std::out_of_range("vector::at() const");
    return (*(begin() + pos));
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::operator[](size_type pos)
{
    return (*(begin() + pos));
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::operator[](size_type pos) const
{
    return (*(begin() + pos));
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::front(void)
{
    return (*begin());
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::front(void) const
{
    return (*begin());
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::back(void)
{
    return (*(end() - 1));
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::back(void) const
{
    return (*(end() - 1));
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::pointer vector<T, Alloc>::data(void)
{
    return (_data);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_pointer vector<T, Alloc>::data(void) const
{
    return (_data);
}

/**************************************** MODIFIERS ***************************************/

template <typename T, typename Alloc>
void vector<T, Alloc>::assign(size_type n, T const &value)
{
    if (n > max_size())
        throw std::length_error("vector::assign()");
    clear();
    reserve(n);
    if (is_integral<value_type>::value) {
        for (size_type i = 0; i < n; ++i)
            *(_data + i) = value;
    } else {
        for (size_type i = 0; i < n; ++i)
            _allocator.construct((_data + i), value);
    }
    _size = n;
}

template <typename T, typename Alloc>
template <typename Iter>
void vector<T, Alloc>::assign(Iter first,
                              Iter last,
                              typename enable_if<!is_integral<Iter>::value>::type *)
{
    size_type n = ft::distance(first, last);

    if (n > max_size())
        throw std::length_error("vector::assign()");
    clear();
    reserve(n);
    if (is_integral<value_type>::value) {
        for (size_type i = 0; i < n; ++i)
            *(_data + i) = *(first + i);
    } else {
        for (size_type i = 0; i < n; ++i)
            _allocator.construct((_data + i), *(first + i));
    }
    _size = n;
}

template <typename T, typename Alloc>
void vector<T, Alloc>::push_back(T const &value)
{
    if (_size == _capacity)
        reserve(_size ? (_size * 2) : 1);
    _allocator.construct((_data + _size), value);
    ++_size;
}

template <typename T, typename Alloc>
void vector<T, Alloc>::pop_back(void)
{
    if (!_size)
        return;
    if (!is_integral<value_type>::value)
        _allocator.destroy(_data + (_size - 1));
    --_size;
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(iterator pos, T const &value)
{
    difference_type distance;

    distance = pos - begin();
    if (_size == _capacity)
        reserve(_size ? (_size * 2) : 1);
    if (is_integral<value_type>::value) {
        std::copy_backward((_data + distance), (_data + _size), (_data + _size + 1));
    } else {
        for (difference_type i = _size; i > distance; --i) {
            _allocator.construct((_data + i), *(_data + i - 1));
            _allocator.destroy(_data + i - 1);
        }
    }
    _allocator.construct((_data + distance), value);
    ++_size;
    return (iterator(_data + distance));
}

template <typename T, typename Alloc>
void vector<T, Alloc>::insert(iterator pos, size_type n, T const &value)
{
    difference_type distance;

    if (!n)
        return;
    distance = pos - begin();
    if ((_size + n) > _capacity)
        reserve(((_size * 2) >= (_size + n)) ? (_size * 2) : (_size + n));
    if (is_integral<value_type>::value) {
        std::copy_backward((_data + distance), (_data + _size), (_data + _size + n));
        for (difference_type i = (distance + n - 1); i >= distance; --i)
            *(_data + i) = value;
    } else {
        for (difference_type i = _size; i > distance; --i) {
            _allocator.construct((_data + i + n - 1), *(_data + i - 1));
            _allocator.destroy(_data + i - 1);
        }
        for (difference_type i = (distance + n - 1); i >= distance; --i)
            _allocator.construct((_data + i), value);
    }
    _size += n;
}

template <typename T, typename Alloc>
template <typename Iter>
void vector<T, Alloc>::insert(iterator pos,
                              Iter     first,
                              Iter     last,
                              typename enable_if<!is_integral<Iter>::value>::type *)
{
    difference_type distance, n_elem, n = ft::distance(first, last);

    if (!n)
        return;
    distance = pos - begin();
    if ((_size + n) > _capacity)
        reserve(((_size * 2) >= (_size + n)) ? (_size * 2) : (_size + n));
    n_elem = n;
    if (is_integral<value_type>::value) {
        std::copy_backward((_data + distance), (_data + _size), (_data + _size + n));
        for (difference_type i = (distance + n - 1); n_elem--; --i)
            *(_data + i) = *(first + n_elem);
    } else {
        for (difference_type i = _size; i > distance; --i) {
            _allocator.construct((_data + i + n - 1), *(_data + i - 1));
            _allocator.destroy(_data + i - 1);
        }
        for (difference_type i = (distance + n - 1); n_elem--; --i)
            _allocator.construct((_data + i), *(first + n_elem));
    }
    _size += n;
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator position)
{
    size_type distance = position - begin();

    if ((position + 1) != end())
        std::copy((_data + distance + 1), (_data + _size), (_data + distance));
    --_size;
    if (!is_integral<value_type>::value)
        _allocator.destroy(_data + _size);
    return (iterator(_data + distance));
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator first, iterator last)
{
    iterator        it(std::copy(last.base(), end().base(), first.base()));
    difference_type distance = first - begin();

    if (!is_integral<value_type>::value) {
        while (it != end()) {
            _allocator.destroy(it.base());
            ++it;
        }
    }
    _size -= last - first;
    return (iterator(_data + distance));
}

template <typename T, typename Alloc>
void vector<T, Alloc>::resize(size_type n, value_type value)
{
    if (n < _size && !is_integral<value_type>::value) {
        for (size_type i = n; i < _size; ++i)
            _allocator.destroy(_data + i);
    } else {
        if (n > _capacity)
            reserve(n);
        for (size_type i = _size; i < n; ++i)
            _allocator.construct((_data + i), value);
    }
    _size = n;
}

template <typename T, typename Alloc>
void vector<T, Alloc>::swap(vector &src)
{
    pointer   tmp_data     = src._data;
    size_type tmp_size     = src._size;
    size_type tmp_capacity = src._capacity;

    src._data     = _data;
    src._size     = _size;
    src._capacity = _capacity;
    _data         = tmp_data;
    _size         = tmp_size;
    _capacity     = tmp_capacity;
}

template <typename T, typename Alloc>
void vector<T, Alloc>::clear(void)
{
    if (!is_integral<value_type>::value) {
        for (size_type i = 0; i < _size; ++i)
            _allocator.destroy(_data + i);
    }
    _size = 0;
}

/**************************************** ALLOCATOR ***************************************/

template <typename T, typename Alloc>
typename vector<T, Alloc>::allocator_type vector<T, Alloc>::get_allocator(void) const
{
    return (_allocator);
}

} /* namespace ft */

#endif /* FT_VECTOR_TPP */
