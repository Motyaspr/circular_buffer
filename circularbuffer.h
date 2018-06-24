//
// Created by motyaspr on 23.06.18.
//

#ifndef CIRCULAR_BUFFER_CIRCULARBUFFER_H
#define CIRCULAR_BUFFER_CIRCULARBUFFER_H


#include <cstddef>
#include <algorithm>

template <typename T>
class buffer{
private:
    size_t capacity, start, sz, last;
    T* data;
    size_t next(size_t ind);
    size_t prev(size_t ind);
    void ensure_capacity(size_t nsz);
public:
    ~buffer();
    void swap(buffer& other);
    buffer();
    buffer(size_t nsz);
    buffer(buffer const& other);
    buffer& operator=(buffer const& other);
    bool empty() const;
    size_t size() const;
    void clear();
    void push_back(T const &a);
    void push_front(T const& a);
    void pop_back();
    void pop_front();
    T const& front() const;
    T& front();
    T const& back() const;
    T& back();
    T const& operator[](size_t i) const;
    T& operator[](size_t i);

    //template<typename T>
    template<typename V>
    struct my_iterator{
    private:
        T* data;
        size_t ind, cap, st;
        friend struct buffer;
        my_iterator(T* data, size_t ind, size_t cap, size_t st) : data(data), ind(ind), cap(cap), st(st){};
    public:
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = V;
        using pointer = V *;
        using reference = V &;

        size_t get_ind(){
            return ind;
        }
        my_iterator& operator++(){
            ++ind;
            return *this;
        }
        my_iterator& operator--(){
            --ind;
            return *this;
        }
        my_iterator operator++(int){
            my_iterator cur = *this;
            ++(*this);
            return cur;
        }
        my_iterator operator--(int){
            my_iterator cur = (*this);
            --(*this);
            return cur;
        }
        V&operator*() const{
            return data[((st + ind) % cap)];
        }
        V*operator->() const;

        friend bool operator==(my_iterator const& a, my_iterator const &b){
            return a.ind == b.ind;
        }
        friend bool operator!=(my_iterator const& a, my_iterator const &b){
            return a.ind != b.ind;
        }
        bool operator<(my_iterator const &b){
            return ind < b.ind;
        }
        bool operator<=(my_iterator const &b){
            return ind <= b.ind;
        }
        bool operator>(my_iterator const &b){
            return ind > b.ind;
        }
        bool operator>=(my_iterator const &b){
            return ind >= b.ind;
        }
        my_iterator operator-(size_t k){
            return my_iterator<V>(data, (ind - k), cap, st);
        }
        my_iterator operator+(size_t k){
            return my_iterator<V>(data, (ind + k), cap, st);
        }
        my_iterator &operator+=(size_t k){
            *this = *this + k;
            return *this;
        }
        my_iterator &operator-=(size_t k){
            *this = *this - k;
            return *this;
        }
        template <typename V2>
        my_iterator(const my_iterator<V2> &other,
                         typename std::enable_if<std::is_same<V, const V2>::value>::type * = nullptr)
                : st(other.st)
                , ind(other.ind)
                , data(other.data)
                , cap(other.cap)
        {}

    };
    using iterator =  my_iterator<T>;
    using const_iterator = my_iterator<const T>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    iterator begin(){
        return iterator(data, 0, capacity, start);
    }

    const_iterator begin() const{
        return const_iterator(data, 0, capacity, start);
    }

    iterator end(){
        return iterator(data, sz, capacity, start);
    }

    const_iterator end() const{
        return const_iterator(data, sz, capacity, start);
    }

    reverse_iterator rbegin(){
        return reverse_iterator(end());
    }

    const_reverse_iterator rbegin() const{
        return const_reverse_iterator(end());
    }

    reverse_iterator rend(){
        return reverse_iterator(begin());
    }

    const_reverse_iterator rend() const{
        return const_reverse_iterator(begin());
    }

    iterator insert(const_iterator pos_iter, T const &value){
        if (empty()){
            push_back(value);
            return begin();
        }

        size_t ind = pos_iter.ind;
        if (ind <= sz / 2){
            push_front(value);
            for (size_t i = 0; i < ind; i++) {
                std::swap(data[i], data[next(i)]);
            }
        }else{
            push_back(value);
            for (size_t i = sz - 1; i > ind; i--){
                std::swap(data[i], data[prev(i)]);
            }
        }
        return iterator(data, ind - 1, capacity, start);
    }

    iterator erase(const_iterator pos_iter){
        int ind = pos_iter.ind;
        if (ind <= sz / 2){
            for (size_t i = ind; i > 0; i--)
                std::swap(data[i], data[prev(i)]);
            pop_front();
        }
        else{
            for (size_t i = ind + 1; i < sz; i++)
                std::swap(data[i], data[i - 1]);
            pop_back();
        }
        return iterator(data, ind, capacity, start);
    }
};

template<typename T>
size_t buffer<T>::next(size_t ind) {
    ind++;
    if (ind == capacity)
        ind = 0;
    return ind;
}

template<typename T>
size_t buffer<T>::prev(size_t ind) {
    if (ind == 0)
        ind = capacity;
    ind--;
    return ind;
}

template<typename T>
buffer<T>::buffer() : data(nullptr), sz(0), capacity(0), start(0), last(0){
}

template<typename T>
bool buffer<T>::empty() const {
    return sz == 0;
}

template<typename T>
size_t buffer<T>::size() const {
    return sz;
}

template<typename T>
void buffer<T>::swap(buffer& other) {
    std::swap(other.data, data);
    std::swap(start, other.start);
    std::swap(last, other.last);
    std::swap(sz, other.sz);
    std::swap(capacity, other.capacity);
}


template<typename T>
buffer<T>::buffer(size_t nsz) : sz(0), capacity(nsz), start(0), last(0),
                                data(static_cast<T*>(operator new (capacity * sizeof(T)))) {}

template<typename T>
void buffer<T>::ensure_capacity(size_t nsz) {
    if (nsz + 1 < capacity)
        return;
    buffer<T> cop = buffer(capacity * 2 + 2);
    cop.start = 0;
    cop.last = 0;
    cop.sz = 0;
    for (size_t i = start, ind = 0; i != last; i = next(i), ind++)
         cop.push_back(data[i]);
    swap(cop);
}

template<typename T>
buffer<T> &buffer<T>::operator=(buffer const &other) {
    buffer cop(other);
    swap(cop);
    return *this;
}

template<typename T>
buffer<T>::buffer(buffer const &other) : capacity(other.capacity), sz(other.sz), start(other.start),
                                         last(other.last), data(nullptr) {
    if (capacity == 0)
        return;
    data = static_cast<T*>(operator new (capacity * sizeof(T)));
    for (size_t i = start; i != last; i = next(i))
        new(&data[i]) T(other.data[i]);

}

template<typename T>
void buffer<T>::push_back(const T &a) {
    ensure_capacity(sz);
    new (&data[last]) T(a);
    last = next(last);
    sz++;
}

template<typename T>
void buffer<T>::push_front(const T &a) {
    ensure_capacity(sz);
    start = prev(start);
    new(&data[start]) T(a);
    sz++;
}

template<typename T>
void buffer<T>::pop_back() {
    sz--;
    last = prev(last);
    data[last].~T();
}

template<typename T>
void buffer<T>::pop_front() {
    sz--;
    data[start].~T();
    start = next(start);
}

template<typename T>
T const &buffer<T>::front() const {
    return data[start];
}

template<typename T>
T &buffer<T>::front() {
    return data[start
    ];
}

template<typename T>
T const &buffer<T>::back() const {
    size_t i = (last - 1 + capacity) % capacity;
    return data[i];
}

template<typename T>
T &buffer<T>::back() {
    return data[prev(last)];
}

template<typename T>
T const &buffer<T>::operator[](size_t i) const {
    return data[(start + i) % capacity];
}

template<typename T>
T &buffer<T>::operator[](size_t i) {
    return data[(start + i) % capacity];
}

template<typename T>
void buffer<T>::clear() {
    while(sz > 0)
        pop_back();
}

template<typename T>
buffer<T>::~buffer() {
    clear();
    operator delete(data);

}

template<typename T>
void swap(buffer<T>& l, buffer<T>& r)
{
    l.swap(r);
}


#endif //CIRCULAR_BUFFER_CIRCULARBUFFER_H
