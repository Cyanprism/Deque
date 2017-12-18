//

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

template <class TElem>
class Deque  {
private:
    template <typename T, bool reversed>
    class _templated_iterator;

public:
    Deque ();
    Deque (const Deque <TElem> &Obj);

    void push_back (TElem elem);
    void push_front (TElem elem);
    void pop_back ();
    void pop_front ();
    TElem &operator[] (int index) const;

    TElem &back () { return const_cast<TElem &>(static_cast<const Deque <TElem>*>(this)->back()); }
    const TElem &back () const;
    TElem &front () { return const_cast<TElem &>(static_cast<const Deque <TElem>*>(this)->front()); }
    const TElem &front () const;

    bool empty () const;
    int size () const;

    typedef _templated_iterator<TElem, false> iterator;
    typedef _templated_iterator<const TElem, false> const_iterator;
    typedef _templated_iterator<TElem, true> reverse_iterator;
    typedef _templated_iterator<const TElem, true> const_reverse_iterator;

    iterator begin () { return iterator(this, _front); }
    const_iterator begin () const { return const_iterator(const_cast<Deque<TElem>*>(this), _front); }
    iterator end () { return iterator(this, _back); }
    const_iterator end () const { return const_iterator(const_cast<Deque<TElem>*>(this), _back); }
    const_iterator cbegin () const { return const_iterator(const_cast<Deque<TElem>*>(this), _front); }
    const_iterator cend () const { return const_iterator(const_cast<Deque<TElem>*>(this), _back); }
    reverse_iterator rbegin () {  return reverse_iterator(this, _back - 1); }
    const_reverse_iterator rbegin () const { return const_reverse_iterator(const_cast<Deque<TElem>*>(this), _back - 1); }
    reverse_iterator rend () { return reverse_iterator(this, _front - 1); }
    const_reverse_iterator rend () const { return const_reverse_iterator(const_cast<Deque<TElem>*>(this), _front - 1); }
    const_reverse_iterator crbegin () const { return const_reverse_iterator(const_cast<Deque<TElem>*>(this), _back - 1); }
    const_reverse_iterator crend () const { return const_reverse_iterator(const_cast<Deque<TElem>*>(this), _front - 1); }

private:
    TElem *_array;
    int _front;
    int _back;
    int _size;
    int _array_size;
    bool _is_empty;
    static const int _min_array_size = 4;

    int _abs (int index) const;

    void _expand ();
    void _reduce ();

    template <typename T, bool reverse>
    class _templated_iterator : public std::iterator<std::random_access_iterator_tag, TElem> {
    protected:
        Deque<TElem> *_deque;
        int _index;
    public:
        _templated_iterator (Deque<TElem> *deque, int index) : _deque(deque), _index(index) {};
        _templated_iterator (const _templated_iterator &it) : _deque(it._deque), _index(it._index) {}
        _templated_iterator &operator= (const _templated_iterator &it) {
            _deque = it._deque;
            _index = it._index;
            return *this;
        }
        T &operator* () { return _deque->_array[_deque->_abs(_index)]; }

        T *operator-> () { return &_deque->_array[_deque->_abs(_index)]; }

        _templated_iterator &operator++ () {
            if (!reverse) {
                ++_index;
            } else {
                --_index;
            }
            return *this;
        }
        _templated_iterator operator++ (int) {
            _templated_iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        _templated_iterator &operator-- () {
            if (!reverse) {
                --_index;
            } else {
                ++_index;
            }
            return *this;
        }
        _templated_iterator operator-- (int) {
            _templated_iterator tmp = *this;
            --(*this);
            return tmp;
        }
        bool operator== (_templated_iterator it) { return _deque == it._deque && _index == it._index; }
        bool operator!= (_templated_iterator it) { return !(*this == it); }
        _templated_iterator &operator += (int k) {
            if (!reverse) {
                _index += k;
            } else {
                _index -= k;
            }

            return *this;
        }
        _templated_iterator &operator -= (int k) {
            if (!reverse) {
                _index -= k;
            } else {
                _index += k;
            }

            return *this;
        }
        _templated_iterator operator+ (int k) {
            _templated_iterator tmp = *this;
            tmp += k;
            return tmp;
        }
        _templated_iterator operator- (int k) {
            _templated_iterator tmp = *this;
            tmp -= k;
            return tmp;
        }
        int operator- (const _templated_iterator &it) {
            if (!reverse) {
                return this->_index - it._index;
            } else {
                return it._index - this->_index;
            }
        }
        bool operator < (const _templated_iterator &it) {
            return this->_index < it._index;
        }
        bool operator > (const _templated_iterator &it) { return !(*this <= it); }
        bool operator <= (const _templated_iterator &it) { return *this < it || *this == it; }
        bool operator >= (const _templated_iterator &it) { return !(*this < it); }
    };
};

template <class TElem>
Deque <TElem>::Deque  () {
    _array_size = _min_array_size;
    _array = new TElem[_array_size];
    _front = 0;
    _back = 0;
    _size = 0;
    _is_empty = true;
}

template<class TElem>
Deque <TElem>::Deque  (const Deque <TElem> &obj) {
    _array_size = obj._array_size;
    _front = obj._front;
    _back = obj._back;
    _size = obj._size;
    _is_empty = obj._is_empty;

    _array = new TElem[_array_size];
    std::copy(obj._array, obj._array + _array_size, _array);
}

template <class TElem>
void Deque <TElem>::_expand () {
    auto *new_array = new TElem[_array_size * 2];

    int index = _abs(_front);

    int new_index = _front;
    while (new_index < 0) {
        new_index += 2 * _array_size;
    }
    new_index %= 2 * _array_size;

    for (int i = 0; i < _array_size; ++i) {
        new_array[(new_index + i) % (2 * _array_size)] = _array[(index + i) % _array_size];
    }

    std::swap(_array, new_array);
    delete[] new_array;

    _array_size *= 2;
}

template <class TElem>
void Deque <TElem>::_reduce () {
    auto *new_array = new TElem[_array_size / 2];

    int index = _abs(_front);
    int new_index = index % (_array_size / 2);
    for (int i = 0; i < _array_size / 4; ++i) {
        new_array[(new_index + i) % (_array_size / 2)] = _array[(index + i) % _array_size];
    }

    std::swap(_array, new_array);
    delete[] new_array;

    _array_size /= 2;
}

template<class TElem>
int Deque <TElem>::_abs (int index) const {
    while (index >= _array_size) {
        index -= _array_size;
    }
    while (index < 0) {
        index += _array_size;
    }
    return index;
}

template <class TElem>
void Deque <TElem>::push_back (TElem elem) {
    if (_size == _array_size) {
        _expand();
    }
    _is_empty = false;

    _array[_abs(_back)] = elem;
    ++_back;
    ++_size;
}

template <class TElem>
void Deque <TElem>::push_front (TElem elem) {
    if (_size == _array_size) {
        _expand();
    }
    _is_empty = false;

    --_front;
    _array[_abs(_front)] = elem;
    ++_size;
}

template <class TElem>
void Deque <TElem>::pop_back () {
    --_back;
    --_size;

    if (_size == 0) {
        _is_empty = true;
    }

    if (_array_size >= _min_array_size * 2 && _size <= _array_size / 4) {
        _reduce();
    }
}

template <class TElem>
void Deque <TElem>::pop_front () {
    ++_front;
    --_size;

    if (_size == 0) {
        _is_empty = true;
    }

    if (_array_size >= _min_array_size * 2 && _size <= _array_size / 4) {
        _reduce();
    }
}

template <class TElem>
TElem &Deque <TElem>::operator[] (int index) const {
    return _array[_abs(_front + index)];
}

template <class TElem>
const TElem &Deque <TElem>::back () const {
    return _array[_abs(_back - 1)];
}

template <class TElem>
const TElem &Deque <TElem>::front () const {
    return _array[_abs(_front)];
}

template <class TElem>
bool Deque <TElem>::empty () const {
    return _is_empty;
}

template <class TElem>
int Deque <TElem>::size () const {
    return _size;
}

