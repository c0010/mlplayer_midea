// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:list class as std::list, board from QT
//  Author:roy
// //////////////////////////////////////////////////////////////////////////////

#ifndef __CM_LIST_H__
#define __CM_LIST_H__

#ifndef ASSERT_X
#define ASSERT_X(a, b, c)
#endif

//目前此类有个静态变量用于表示类实例数量
//对比std，缺max_size、rend、resize、splice、unique、assign、remove、remove_if、rbegin

//namespace CM 
//{

template <typename T>
class MTypeInfo
{
public:
    enum {
        isPointer = false,
        isComplex = true,
        isStatic = true,
        isLarge = (sizeof(T)>sizeof(void*)),
        isDummy = false
    };
};

template <typename T>
class MTypeInfo<T*>
{
public:
    enum {
        isPointer = true,
        isComplex = false,
        isStatic = false,
        isLarge = false,
        isDummy = false
    };
};

template <typename T>
inline const T &qMax(const T &a, const T &b) { if (a < b) return b; return a; }

struct MListData {
    struct Data {
        int ref;
        int alloc, begin, end;
        unsigned int sharable : 1;
        void *array[1];
    };
    enum { DataHeaderSize = sizeof(Data) - sizeof(void *) };

    Data *detach(); // remove in 5.0
    Data *detach2();
    void realloc(int alloc);
    static Data shared_null;
    Data *d;
    void **erase(void **xi);
    void **append();
    void **append(const MListData &l);
    void **prepend();
    void **insert(int i);
    void remove(int i);
    void remove(int i, int n);
    void move(int from, int to);
    inline int size() const { return d->end - d->begin; }
    inline bool isEmpty() const { return d->end  == d->begin; }
    inline void **at(int i) const { return d->array + d->begin + i; }
    inline void **begin() const { return d->array + d->begin; }
    inline void **end() const { return d->array + d->end; }
};

template <typename T>
class CMList
{
    struct Node { void *v;
        inline T &t()
        { return *reinterpret_cast<T*>(MTypeInfo<T>::isLarge || MTypeInfo<T>::isStatic
                                       ? v : this); }
    };

    union { MListData p; MListData::Data *d; };

public:
    inline CMList() : d(&MListData::shared_null) { d->ref++; }
    inline CMList(const CMList<T> &l) : d(l.d) { d->ref++; if (!d->sharable) detach_helper(); }
    ~CMList();
    CMList<T> &operator=(const CMList<T> &l);
    bool operator==(const CMList<T> &l) const;
    inline bool operator!=(const CMList<T> &l) const { return !(*this == l); }

    inline int size() const { return p.size(); }
    void clear();
    void insert(int i, const T &t);
    void swap(int i, int j);
    void replace(int i, const T &t);
    void removeAt(int i);
    const T &at(int i) const;
    T &at(int i);
    bool contains(const T &t) const;
    int removeAll(const T &t);
    bool removeOne(const T &t);
    int indexOf(const T &t, int from = 0) const;

    void append(const CMList<T> &t);
private:
	//一些不常用的，或者内部重复的接口，后续考虑删除
    inline void detach() { if (d->ref != 1) detach_helper(); }
    inline bool isDetached() const { return d->ref == 1; }
    inline void setSharable(bool sharable) { if (!sharable) detach(); d->sharable = sharable; }

    inline bool isEmpty() const { return p.isEmpty(); }


    const T &operator[](int i) const;
    T &operator[](int i);
    void append(const T &t);
    void prepend(const T &t);
    T takeAt(int i);
    T takeFirst();
    T takeLast();
    void move(int from, int to);
    int lastIndexOf(const T &t, int from = -1) const;
    int count(const T &t) const;

public:
    class const_iterator;

    class iterator {
    public:
        Node *i;
        //typedef std::random_access_iterator_tag  iterator_category;
        //typedef ptrdiff_t  difference_type;
        typedef T value_type;
        typedef T *pointer;
        typedef T &reference;

        inline iterator() : i(0) {}
        inline iterator(Node *n) : i(n) {}
        inline iterator(const iterator &o): i(o.i){}
        inline T &operator*() const { return i->t(); }
        inline T *operator->() const { return &i->t(); }
        inline T &operator[](int j) const { return i[j].t(); }
        inline bool operator==(const iterator &o) const { return i == o.i; }
        inline bool operator!=(const iterator &o) const { return i != o.i; }
        inline bool operator<(const iterator& other) const { return i < other.i; }
        inline bool operator<=(const iterator& other) const { return i <= other.i; }
        inline bool operator>(const iterator& other) const { return i > other.i; }
        inline bool operator>=(const iterator& other) const { return i >= other.i; }
#ifndef QT_STRICT_ITERATORS
        inline bool operator==(const const_iterator &o) const
            { return i == o.i; }
        inline bool operator!=(const const_iterator &o) const
            { return i != o.i; }
        inline bool operator<(const const_iterator& other) const
            { return i < other.i; }
        inline bool operator<=(const const_iterator& other) const
            { return i <= other.i; }
        inline bool operator>(const const_iterator& other) const
            { return i > other.i; }
        inline bool operator>=(const const_iterator& other) const
            { return i >= other.i; }
#endif
        inline iterator &operator++() { ++i; return *this; }
        inline iterator operator++(int) { Node *n = i; ++i; return n; }
        inline iterator &operator--() { i--; return *this; }
        inline iterator operator--(int) { Node *n = i; i--; return n; }
        inline iterator &operator+=(int j) { i+=j; return *this; }
        inline iterator &operator-=(int j) { i-=j; return *this; }
        inline iterator operator+(int j) const { return iterator(i+j); }
        inline iterator operator-(int j) const { return iterator(i-j); }
        inline int operator-(iterator j) const { return i - j.i; }
    };
    friend class iterator;

    class const_iterator {
    public:
        Node *i;
//        typedef std::random_access_iterator_tag  iterator_category;
        //typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef const T *pointer;
        typedef const T &reference;

        inline const_iterator() : i(0) {}
        inline const_iterator(Node *n) : i(n) {}
        inline const_iterator(const const_iterator &o): i(o.i) {}
#ifdef QT_STRICT_ITERATORS
        inline explicit const_iterator(const iterator &o): i(o.i) {}
#else
        inline const_iterator(const iterator &o): i(o.i) {}
#endif
        inline const T &operator*() const { return i->t(); }
        inline const T *operator->() const { return &i->t(); }
        inline const T &operator[](int j) const { return i[j].t(); }
        inline bool operator==(const const_iterator &o) const { return i == o.i; }
        inline bool operator!=(const const_iterator &o) const { return i != o.i; }
        inline bool operator<(const const_iterator& other) const { return i < other.i; }
        inline bool operator<=(const const_iterator& other) const { return i <= other.i; }
        inline bool operator>(const const_iterator& other) const { return i > other.i; }
        inline bool operator>=(const const_iterator& other) const { return i >= other.i; }
        inline const_iterator &operator++() { ++i; return *this; }
        inline const_iterator operator++(int) { Node *n = i; ++i; return n; }
        inline const_iterator &operator--() { i--; return *this; }
        inline const_iterator operator--(int) { Node *n = i; i--; return n; }
        inline const_iterator &operator+=(int j) { i+=j; return *this; }
        inline const_iterator &operator-=(int j) { i-=j; return *this; }
        inline const_iterator operator+(int j) const { return const_iterator(i+j); }
        inline const_iterator operator-(int j) const { return const_iterator(i-j); }
        inline int operator-(const_iterator j) const { return i - j.i; }
    };
    friend class const_iterator;

    // stl style
    inline iterator begin() { detach(); return reinterpret_cast<Node *>(p.begin()); }
    inline const_iterator begin() const { return reinterpret_cast<Node *>(p.begin()); }
    inline iterator end() { detach(); return reinterpret_cast<Node *>(p.end()); }
    inline const_iterator end() const { return reinterpret_cast<Node *>(p.end()); }
    iterator insert(iterator before, const T &t);
    iterator erase(iterator pos);
    iterator erase(iterator first, iterator last);

    // stl compatibility
    inline void push_back(const T &t) { append(t); }
    inline void push_front(const T &t) { prepend(t); }
    inline T& front() { return first(); }
    inline const T& front() const { return first(); }
    inline T& back() { return last(); }
    inline const T& back() const { return last(); }
    inline void pop_front() { removeFirst(); }
    inline void pop_back() { removeLast(); }
    inline bool empty() const { return isEmpty(); }
    typedef int size_type;
    typedef T value_type;
    typedef value_type *pointer;
    typedef const value_type *const_pointer;
    typedef value_type &reference;
    typedef const value_type &const_reference;
    //typedef ptrdiff_t difference_type;

private:
    inline const_iterator constBegin() const { return reinterpret_cast<Node *>(p.begin()); }
    inline const_iterator constEnd() const { return reinterpret_cast<Node *>(p.end()); }

    // more Qt
    typedef iterator Iterator;
    typedef const_iterator ConstIterator;
    inline int count() const { return p.size(); }
    inline int length() const { return p.size(); } // Same as count()
    inline T& first() { ASSERT(!isEmpty()); return *begin(); }
    inline const T& first() const { ASSERT(!isEmpty()); return *begin(); }
    T& last() { ASSERT(!isEmpty()); return *(--end()); }
    const T& last() const { ASSERT(!isEmpty()); return *(--end()); }
    inline void removeFirst() { ASSERT(!isEmpty()); erase(begin()); }
    inline void removeLast() { ASSERT(!isEmpty()); erase(--end()); }
    inline bool startsWith(const T &t) const { return !isEmpty() && first() == t; }
    inline bool endsWith(const T &t) const { return !isEmpty() && last() == t; }
    CMList<T> mid(int pos, int length = -1) const;

    T value(int i) const;
    T value(int i, const T &defaultValue) const;

    // comfort
    CMList<T> &operator+=(const CMList<T> &l);
    inline CMList<T> operator+(const CMList<T> &l) const
    { CMList n = *this; n += l; return n; }
    inline CMList<T> &operator+=(const T &t)
    { append(t); return *this; }
    inline CMList<T> &operator<< (const T &t)
    { append(t); return *this; }
    inline CMList<T> &operator<<(const CMList<T> &l)
    { *this += l; return *this; }

private:
    void detach_helper();
    void free(MListData::Data *d);

    void node_construct(Node *n, const T &t);
    void node_destruct(Node *n);
    void node_copy(Node *from, Node *to, Node *src);
    void node_destruct(Node *from, Node *to);
};

template <typename T>
inline void CMList<T>::node_construct(Node *n, const T &t)
{
    if (MTypeInfo<T>::isLarge || MTypeInfo<T>::isStatic) n->v = new T(t);
	else if (MTypeInfo<T>::isComplex) {T* tt = reinterpret_cast<T*>(n); tt = new T(t);}
    else *reinterpret_cast<T*>(n) = t;
}

template <typename T>
inline void CMList<T>::node_destruct(Node *n)
{
    if (MTypeInfo<T>::isLarge || MTypeInfo<T>::isStatic) delete reinterpret_cast<T*>(n->v);
    else if (MTypeInfo<T>::isComplex) reinterpret_cast<T*>(n)->~T();
}

template <typename T>
inline void CMList<T>::node_copy(Node *from, Node *to, Node *src)
{
    if (MTypeInfo<T>::isLarge || MTypeInfo<T>::isStatic)
        while(from != to)
            (from++)->v = new T(*reinterpret_cast<T*>((src++)->v));
    else if (MTypeInfo<T>::isComplex)
        while(from != to)
			{T* tt = reinterpret_cast<T*>(from++); tt = new T(*reinterpret_cast<T*>(src++));}
}

template <typename T>
inline void CMList<T>::node_destruct(Node *from, Node *to)
{
    if (MTypeInfo<T>::isLarge || MTypeInfo<T>::isStatic)
        while(from != to) --to, delete reinterpret_cast<T*>(to->v);
    else if (MTypeInfo<T>::isComplex)
        while (from != to) --to, reinterpret_cast<T*>(to)->~T();
}

template <typename T>
inline CMList<T> &CMList<T>::operator=(const CMList<T> &l)
{
    if (d != l.d) {
        l.d->ref++;
        if (!--d->ref)
            free(d);
        d = l.d;
        if (!d->sharable)
            detach_helper();
    }
    return *this;
}
template <typename T>
inline typename CMList<T>::iterator CMList<T>::insert(iterator before, const T &t)
{ Node *n = reinterpret_cast<Node *>(p.insert(before.i-reinterpret_cast<Node *>(p.begin())));
 node_construct(n,t); return n; }
template <typename T>
inline typename CMList<T>::iterator CMList<T>::erase(iterator it)
{ node_destruct(it.i);
 return reinterpret_cast<Node *>(p.erase(reinterpret_cast<void**>(it.i))); }
template <typename T>
inline const T &CMList<T>::at(int i) const
{ ASSERT_X(i >= 0 && i < p.size(), "CMList<T>::at", "index out of range");
 return reinterpret_cast<Node *>(p.at(i))->t(); }
template <typename T>
inline T &CMList<T>::at(int i)
{ ASSERT_X(i >= 0 && i < p.size(), "CMList<T>::at", "index out of range");
  detach(); return reinterpret_cast<Node *>(p.at(i))->t(); }
template <typename T>
inline const T &CMList<T>::operator[](int i) const
{ ASSERT_X(i >= 0 && i < p.size(), "CMList<T>::operator[]", "index out of range");
 return reinterpret_cast<Node *>(p.at(i))->t(); }
template <typename T>
inline T &CMList<T>::operator[](int i)
{ ASSERT_X(i >= 0 && i < p.size(), "CMList<T>::operator[]", "index out of range");
  detach(); return reinterpret_cast<Node *>(p.at(i))->t(); }
template <typename T>
inline void CMList<T>::removeAt(int i)
{ if(i >= 0 && i < p.size()) { detach();
 node_destruct(reinterpret_cast<Node *>(p.at(i))); p.remove(i); } }
template <typename T>
inline T CMList<T>::takeAt(int i)
{ ASSERT_X(i >= 0 && i < p.size(), "CMList<T>::take", "index out of range");
 detach(); Node *n = reinterpret_cast<Node *>(p.at(i)); T t = n->t(); node_destruct(n);
 p.remove(i); return t; }
template <typename T>
inline T CMList<T>::takeFirst()
{ T t = first(); removeFirst(); return t; }
template <typename T>
inline T CMList<T>::takeLast()
{ T t = last(); removeLast(); return t; }

template <typename T>
inline void CMList<T>::append(const T &t)
{
    detach();
    if (MTypeInfo<T>::isLarge || MTypeInfo<T>::isStatic) {
        node_construct(reinterpret_cast<Node *>(p.append()), t);
    } else {
        const T cpy(t);
        node_construct(reinterpret_cast<Node *>(p.append()), cpy);
    }
}

template <typename T>
inline void CMList<T>::prepend(const T &t)
{
    detach();
    if (MTypeInfo<T>::isLarge || MTypeInfo<T>::isStatic) {
        node_construct(reinterpret_cast<Node *>(p.prepend()), t);
    } else {
        const T cpy(t);
        node_construct(reinterpret_cast<Node *>(p.prepend()), cpy);
    }
}

template <typename T>
inline void CMList<T>::insert(int i, const T &t)
{
    detach();
    if (MTypeInfo<T>::isLarge || MTypeInfo<T>::isStatic) {
        node_construct(reinterpret_cast<Node *>(p.insert(i)), t);
    } else {
        const T cpy(t);
        node_construct(reinterpret_cast<Node *>(p.insert(i)), cpy);
    }
}

template <typename T>
inline void CMList<T>::replace(int i, const T &t)
{
    ASSERT_X(i >= 0 && i < p.size(), "CMList<T>::replace", "index out of range");
    detach();
    if (MTypeInfo<T>::isLarge || MTypeInfo<T>::isStatic) {
        reinterpret_cast<Node *>(p.at(i))->t() = t;
    } else {
        const T cpy(t);
        reinterpret_cast<Node *>(p.at(i))->t() = cpy;
    }
}

template <typename T>
inline void CMList<T>::swap(int i, int j)
{
    ASSERT_X(i >= 0 && i < p.size() && j >= 0 && j < p.size(),
                "CMList<T>::swap", "index out of range");
    detach();
    void *t = d->array[d->begin + i];
    d->array[d->begin + i] = d->array[d->begin + j];
    d->array[d->begin + j] = t;
}

template <typename T>
inline void CMList<T>::move(int from, int to)
{
    ASSERT_X(from >= 0 && from < p.size() && to >= 0 && to < p.size(),
               "CMList<T>::move", "index out of range");
    detach();
    p.move(from, to);
}

template<typename T>
inline CMList<T> CMList<T>::mid(int pos, int alength) const
{
    if (alength < 0)
        alength = size() - pos;
    if (pos == 0 && alength == size())
        return *this;
    CMList<T> cpy;
    if (pos + alength > size())
        alength = size() - pos;
    for (int i = pos; i < pos + alength; ++i)
        cpy += at(i);
    return cpy;
}

template<typename T>
inline T CMList<T>::value(int i) const
{
    if (i < 0 || i >= p.size()) {
        return T();
    }
    return reinterpret_cast<Node *>(p.at(i))->t();
}

template<typename T>
inline T CMList<T>::value(int i, const T& defaultValue) const
{
    return ((i < 0 || i >= p.size()) ? defaultValue : reinterpret_cast<Node *>(p.at(i))->t());
}

template <typename T>
inline void CMList<T>::detach_helper()
{
    Node *n = reinterpret_cast<Node *>(p.begin());
    MListData::Data *x = p.detach2();
    node_copy(reinterpret_cast<Node *>(p.begin()), reinterpret_cast<Node *>(p.end()), n);
    if (!--x->ref)
        free(x);
}

template <typename T>
inline CMList<T>::~CMList()
{
    if (d && !--d->ref)
        free(d);
}

template <typename T>
inline bool CMList<T>::operator==(const CMList<T> &l) const
{
    if (p.size() != l.p.size())
        return false;
    if (d == l.d)
        return true;
    Node *i = reinterpret_cast<Node *>(p.end());
    Node *b = reinterpret_cast<Node *>(p.begin());
    Node *li = reinterpret_cast<Node *>(l.p.end());
    while (i != b) {
        --i; --li;
        if (!(i->t() == li->t()))
            return false;
    }
    return true;
}

// ### Qt 5: rename freeData() to avoid confusion with std::free()
template <typename T>
inline void CMList<T>::free(MListData::Data *data)
{
    node_destruct(reinterpret_cast<Node *>(data->array + data->begin),
                  reinterpret_cast<Node *>(data->array + data->end));
    if (data->ref == 0)
		::free(data);
}


template <typename T>
inline void CMList<T>::clear()
{
	int i = 0;
	Node *n;
    while (i < p.size())
	{
		n = reinterpret_cast<Node *>(p.at(i));
        node_destruct(n);
        p.remove(i);
	}

   // *this = CMList<T>();
}

template <typename T>
inline int CMList<T>::removeAll(const T &_t)
{
    detach();
    const T t = _t;
    int removedCount=0, i=0;
    Node *n;
    while (i < p.size())
        if ((n = reinterpret_cast<Node *>(p.at(i)))->t() == t) {
            node_destruct(n);
            p.remove(i);
            ++removedCount;
        } else {
            ++i;
        }
    return removedCount;
}

template <typename T>
inline bool CMList<T>::removeOne(const T &_t)
{
    detach();
    int index = indexOf(_t);
    if (index != -1) {
        removeAt(index);
        return true;
    }
    return false;
}

template <typename T>
inline typename CMList<T>::iterator CMList<T>::erase(typename CMList<T>::iterator afirst,
                                                                 typename CMList<T>::iterator alast)
{
    for (Node *n = afirst.i; n < alast.i; ++n)
        node_destruct(n);
    int idx = afirst - begin();
    p.remove(idx, alast - afirst);
    return begin() + idx;
}

template <typename T>
inline CMList<T> &CMList<T>::operator+=(const CMList<T> &l)
{
    detach();
    Node *n = reinterpret_cast<Node *>(p.append(l.p));
    node_copy(n, reinterpret_cast<Node *>(p.end()), reinterpret_cast<Node *>(l.p.begin()));
    return *this;
}

template <typename T>
inline void CMList<T>::append(const CMList<T> &t)
{
    *this += t;
}

template <typename T>
inline int CMList<T>::indexOf(const T &t, int from) const
{
    if (from < 0)
        from = qMax(from + p.size(), 0);
    if (from < p.size()) {
        Node *n = reinterpret_cast<Node *>(p.at(from -1));
        Node *e = reinterpret_cast<Node *>(p.end());
        while (++n != e)
            if (n->t() == t)
                return n - reinterpret_cast<Node *>(p.begin());
    }
    return -1;
}

template <typename T>
inline int CMList<T>::lastIndexOf(const T &t, int from) const
{
    if (from < 0)
        from += p.size();
    else if (from >= p.size())
        from = p.size()-1;
    if (from >= 0) {
        Node *b = reinterpret_cast<Node *>(p.begin());
        Node *n = reinterpret_cast<Node *>(p.at(from + 1));
        while (n-- != b) {
            if (n->t() == t)
                return n - b;
        }
    }
    return -1;
}

template <typename T>
inline bool CMList<T>::contains(const T &t) const
{
    Node *b = reinterpret_cast<Node *>(p.begin());
    Node *i = reinterpret_cast<Node *>(p.end());
    while (i-- != b)
        if (i->t() == t)
            return true;
    return false;
}

template <typename T>
inline int CMList<T>::count(const T &t) const
{
    int c = 0;
    Node *b = reinterpret_cast<Node *>(p.begin());
    Node *i = reinterpret_cast<Node *>(p.end());
    while (i-- != b)
        if (i->t() == t)
            ++c;
    return c;
}

//}

#endif // __CM_LIST_H__
