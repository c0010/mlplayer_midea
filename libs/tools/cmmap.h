// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:map class as std::map, board from QT
//  Author:roy
// //////////////////////////////////////////////////////////////////////////////

#ifndef __CM_MAP_H__
#define __CM_MAP_H__

#include "cmlist.h"
#if defined(PLAT_SYMBIAN)
typedef UINT32* quintptr;
#endif
struct MMapData
{
    struct Node {
        Node *backward;
        Node *forward[1];
    };
    enum { LastLevel = 11, Sparseness = 3 };

    MMapData *backward;
    MMapData *forward[MMapData::LastLevel + 1];
    int ref;
    int topLevel;
    int size;
    unsigned int randomBits;
    unsigned int insertInOrder : 1;
    unsigned int sharable : 1;

    static MMapData *createData();
    void continueFreeData(int offset);
    Node *node_create(Node *update[], int offset);
    void node_delete(Node *update[], int offset, Node *node);

    static MMapData shared_null;
};


/*
    CMMap uses qMapLessThanKey() to compare keys. The default
    implementation uses operator<(). For pointer types,
    qMapLessThanKey() casts the pointers to integers before it
    compares them, because operator<() is undefined on pointers
    that come from different memory blocks. (In practice, this
    is only a problem when running a program such as
    BoundsChecker.)
*/

template <class Key> inline BOOL qMapLessThanKey(const Key &key1, const Key &key2)
{
    return key1 < key2;
}

#ifndef QT_NO_PARTIAL_TEMPLATE_SPECIALIZATION
template <class Ptr> inline BOOL qMapLessThanKey(Ptr *key1, Ptr *key2)
{
    ASSERT(sizeof(quintptr) == sizeof(Ptr *));
    return quintptr(key1) < quintptr(key2);
}

template <class Ptr> inline BOOL qMapLessThanKey(const Ptr *key1, const Ptr *key2)
{
    ASSERT(sizeof(quintptr) == sizeof(const Ptr *));
    return quintptr(key1) < quintptr(key2);
}
#endif // QT_NO_PARTIAL_TEMPLATE_SPECIALIZATION

template <class Key, class T>
struct QMapNode {
    Key key;
    T value;
    MMapData::Node *backward;
    MMapData::Node *forward[1];
};

template <class Key, class T>
struct QMapPayloadNode
{
    Key key;
    T value;
    MMapData::Node *backward;
};

template <class Key, class T>
class CMMap
{
    typedef QMapNode<Key, T> Node;
    typedef QMapPayloadNode<Key, T> PayloadNode;

    union {
        MMapData *d;
        MMapData::Node *e;
    };

    static inline int payload() { return sizeof(PayloadNode) - sizeof(MMapData::Node *); }
    static inline Node *concrete(MMapData::Node *node) {
        return reinterpret_cast<Node *>(reinterpret_cast<char *>(node) - payload());
    }

public:
    inline CMMap() : d(&MMapData::shared_null) { d->ref++; }
    inline CMMap(const CMMap<Key, T> &other) : d(other.d)
    { d->ref++; if (!d->sharable) detach(); }
    inline ~CMMap() { if (!d) return; if (!--d->ref) freeData(d); }

    CMMap<Key, T> &operator=(const CMMap<Key, T> &other);

    BOOL operator==(const CMMap<Key, T> &other) const;
    inline BOOL operator!=(const CMMap<Key, T> &other) const { return !(*this == other); }

    inline int size() const { return d->size; }

    inline BOOL isEmpty() const { return d->size == 0; }

    inline void detach() { if (d->ref != 1) detach_helper(); }
    inline BOOL isDetached() const { return d->ref == 1; }
    inline void setSharable(BOOL sharable) { if (!sharable) detach(); d->sharable = sharable; }
    inline void setInsertInOrder(BOOL ordered) { d->insertInOrder = ordered; }

    void clear();

    int remove(const Key &key);
    T take(const Key &key);

    BOOL contains(const Key &key) const;
    const Key key(const T &value) const;
    const Key key(const T &value, const Key &defaultKey) const;
    const T value(const Key &key) const;
    const T value(const Key &key, const T &defaultValue) const;
    T &operator[](const Key &key);
    const T operator[](const Key &key) const;

    CMList<Key> uniqueKeys() const;
    CMList<Key> keys() const;
    CMList<Key> keys(const T &value) const;
    CMList<T> values() const;
    CMList<T> values(const Key &key) const;
    int count(const Key &key) const;

    class const_iterator;

    class iterator
    {
        friend class const_iterator;
        MMapData::Node *i;

    public:
        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef T *pointer;
        typedef T &reference;

        // ### Qt 5: get rid of 'operator Node *'
        inline operator MMapData::Node *() const { return i; }
        inline iterator() : i(0) { }
        inline iterator(MMapData::Node *node) : i(node) { }

        inline const Key &key() const { return concrete(i)->key; }
        inline T &value() const { return concrete(i)->value; }
        inline T &operator*() const { return concrete(i)->value; }
        inline T *operator->() const { return &concrete(i)->value; }
        inline BOOL operator==(const iterator &o) const { return i == o.i; }
        inline BOOL operator!=(const iterator &o) const { return i != o.i; }

        inline iterator &operator++() {
            i = i->forward[0];
            return *this;
        }
        inline iterator operator++(int) {
            iterator r = *this;
            i = i->forward[0];
            return r;
        }
        inline iterator &operator--() {
            i = i->backward;
            return *this;
        }
        inline iterator operator--(int) {
            iterator r = *this;
            i = i->backward;
            return r;
        }
        inline iterator operator+(int j) const
        { iterator r = *this; if (j > 0) while (j--) ++r; else while (j++) --r; return r; }
        inline iterator operator-(int j) const { return operator+(-j); }
        inline iterator &operator+=(int j) { return *this = *this + j; }
        inline iterator &operator-=(int j) { return *this = *this - j; }

        // ### Qt 5: not sure this is necessary anymore
    public:
        inline BOOL operator==(const const_iterator &o) const
            { return i == o.i; }
        inline BOOL operator!=(const const_iterator &o) const
            { return i != o.i; }

    private:
        // ### Qt 5: remove
        inline operator BOOL() const { return false; }
    };
    friend class iterator;

    class const_iterator
    {
        friend class iterator;
        MMapData::Node *i;

    public:
        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef const T *pointer;
        typedef const T &reference;

        // ### Qt 5: get rid of 'operator Node *'
        inline operator MMapData::Node *() const { return i; }
        inline const_iterator() : i(0) { }
        inline const_iterator(MMapData::Node *node) : i(node) { }
        inline const_iterator(const iterator &o)
        { i = o.i; }

        inline const Key &key() const { return concrete(i)->key; }
        inline const T &value() const { return concrete(i)->value; }
        inline const T &operator*() const { return concrete(i)->value; }
        inline const T *operator->() const { return &concrete(i)->value; }
        inline BOOL operator==(const const_iterator &o) const { return i == o.i; }
        inline BOOL operator!=(const const_iterator &o) const { return i != o.i; }

        inline const_iterator &operator++() {
            i = i->forward[0];
            return *this;
        }
        inline const_iterator operator++(int) {
            const_iterator r = *this;
            i = i->forward[0];
            return r;
        }
        inline const_iterator &operator--() {
            i = i->backward;
            return *this;
        }
        inline const_iterator operator--(int) {
            const_iterator r = *this;
            i = i->backward;
            return r;
        }
        inline const_iterator operator+(int j) const
        { const_iterator r = *this; if (j > 0) while (j--) ++r; else while (j++) --r; return r; }
        inline const_iterator operator-(int j) const { return operator+(-j); }
        inline const_iterator &operator+=(int j) { return *this = *this + j; }
        inline const_iterator &operator-=(int j) { return *this = *this - j; }

        // ### Qt 5: not sure this is necessary anymore
    private:
        // ### Qt 5: remove
        inline operator BOOL() const { return false; }
    };
    friend class const_iterator;

    // STL style
    inline iterator begin() { detach(); return iterator(e->forward[0]); }
    inline const_iterator begin() const { return const_iterator(e->forward[0]); }
    inline const_iterator constBegin() const { return const_iterator(e->forward[0]); }
    inline iterator end() {
        detach();
        return iterator(e);
    }
    inline const_iterator end() const { return const_iterator(e); }
    inline const_iterator constEnd() const { return const_iterator(e); }
    iterator erase(iterator it);

    // more Qt
    typedef iterator Iterator;
    typedef const_iterator ConstIterator;
    inline int count() const { return d->size; }
    iterator find(const Key &key);
    const_iterator find(const Key &key) const;
    const_iterator constFind(const Key &key) const;
    iterator lowerBound(const Key &key);
    const_iterator lowerBound(const Key &key) const;
    iterator upperBound(const Key &key);
    const_iterator upperBound(const Key &key) const;
    iterator insert(const Key &key, const T &value);
    iterator insertMulti(const Key &key, const T &value);
    CMMap<Key, T> &unite(const CMMap<Key, T> &other);

    // STL compatibility
    typedef Key key_type;
    typedef T mapped_type;
    typedef ptrdiff_t difference_type;
    typedef int size_type;
    inline BOOL empty() const { return isEmpty(); }

#ifdef QT_QMAP_DEBUG
    inline void dump() const { d->dump(); }
#endif

private:
    void detach_helper();
    void freeData(MMapData *d);
    MMapData::Node *findNode(const Key &key) const;
    MMapData::Node *mutableFindNode(MMapData::Node *update[], const Key &key) const;
    MMapData::Node *node_create(MMapData *d, MMapData::Node *update[], const Key &key,
                                const T &value);
};

template <class Key, class T>
inline CMMap<Key, T> &CMMap<Key, T>::operator=(const CMMap<Key, T> &other)
{
    if (d != other.d) {
        other.d->ref++;
        if (!--d->ref)
            freeData(d);
        d = other.d;
        if (!d->sharable)
            detach_helper();
    }
    return *this;
}

template <class Key, class T>
inline void CMMap<Key, T>::clear()
{
    *this = CMMap<Key, T>();
}

template <class Key, class T>
inline typename MMapData::Node *
CMMap<Key, T>::node_create(MMapData *adt, MMapData::Node *aupdate[], const Key &akey, const T &avalue)
{
    MMapData::Node *abstractNode = adt->node_create(aupdate, payload());
    Node *concreteNode = concrete(abstractNode);
#if defined(PLAT_WINCE) || defined(PLAT_IOS) || defined(PLAT_AND)
    concreteNode->key = akey;
    concreteNode->value = avalue;
#else
    new (&concreteNode->key) Key(akey);
    new (&concreteNode->value) T(avalue);
#endif
    return abstractNode;
}

template <class Key, class T>
inline MMapData::Node *CMMap<Key, T>::findNode(const Key &akey) const
{
    MMapData::Node *cur = e;
    MMapData::Node *next = e;

    for (int i = d->topLevel; i >= 0; i--) {
        while ((next = cur->forward[i]) != e && qMapLessThanKey<Key>(concrete(next)->key, akey))
            cur = next;
    }

    if (next != e && !qMapLessThanKey<Key>(akey, concrete(next)->key)) {
        return next;
    } else {
        return e;
    }
}

template <class Key, class T>
inline const T CMMap<Key, T>::value(const Key &akey) const
{
    MMapData::Node *node;
    if (d->size == 0 || (node = findNode(akey)) == e) {
        return T();
    } else {
        return concrete(node)->value;
    }
}

template <class Key, class T>
inline const T CMMap<Key, T>::value(const Key &akey, const T &adefaultValue) const
{
    MMapData::Node *node;
    if (d->size == 0 || (node = findNode(akey)) == e) {
        return adefaultValue;
    } else {
        return concrete(node)->value;
    }
}

template <class Key, class T>
inline const T CMMap<Key, T>::operator[](const Key &akey) const
{
    return value(akey);
}

template <class Key, class T>
inline T &CMMap<Key, T>::operator[](const Key &akey)
{
    detach();

    MMapData::Node *update[MMapData::LastLevel + 1];
    MMapData::Node *node = mutableFindNode(update, akey);
    if (node == e)
        node = node_create(d, update, akey, T());
    return concrete(node)->value;
}

template <class Key, class T>
inline int CMMap<Key, T>::count(const Key &akey) const
{
    int cnt = 0;
    MMapData::Node *node = findNode(akey);
    if (node != e) {
        do {
            ++cnt;
            node = node->forward[0];
        } while (node != e && !qMapLessThanKey<Key>(akey, concrete(node)->key));
    }
    return cnt;
}

template <class Key, class T>
inline BOOL CMMap<Key, T>::contains(const Key &akey) const
{
    return findNode(akey) != e;
}

template <class Key, class T>
inline typename CMMap<Key, T>::iterator CMMap<Key, T>::insert(const Key &akey,
                                                                       const T &avalue)
{
    detach();

    MMapData::Node *update[MMapData::LastLevel + 1];
    MMapData::Node *node = mutableFindNode(update, akey);
    if (node == e) {
        node = node_create(d, update, akey, avalue);
    } else {
        concrete(node)->value = avalue;
    }
    return iterator(node);
}

#ifdef QT3_SUPPORT
template <class Key, class T>
inline typename CMMap<Key, T>::iterator CMMap<Key, T>::insert(const Key &akey,
                                                                       const T &avalue,
                                                                       BOOL aoverwrite)
{
    detach();

    MMapData::Node *update[MMapData::LastLevel + 1];
    MMapData::Node *node = mutableFindNode(update, akey);
    if (node == e) {
        node = node_create(d, update, akey, avalue);
    } else {
        if (aoverwrite)
            concrete(node)->value = avalue;
    }
    return iterator(node);
}
#endif

template <class Key, class T>
inline typename CMMap<Key, T>::iterator CMMap<Key, T>::insertMulti(const Key &akey,
                                                                            const T &avalue)
{
    detach();

    MMapData::Node *update[MMapData::LastLevel + 1];
    mutableFindNode(update, akey);
    return iterator(node_create(d, update, akey, avalue));
}

template <class Key, class T>
inline typename CMMap<Key, T>::const_iterator CMMap<Key, T>::find(const Key &akey) const
{
    return const_iterator(findNode(akey));
}

template <class Key, class T>
inline typename CMMap<Key, T>::const_iterator CMMap<Key, T>::constFind(const Key &akey) const
{
    return const_iterator(findNode(akey));
}

template <class Key, class T>
inline typename CMMap<Key, T>::iterator CMMap<Key, T>::find(const Key &akey)
{
    detach();
    return iterator(findNode(akey));
}

template <class Key, class T>
inline CMMap<Key, T> &CMMap<Key, T>::unite(const CMMap<Key, T> &other)
{
    CMMap<Key, T> copy(other);
    const_iterator it = copy.constEnd();
    const const_iterator b = copy.constBegin();
    while (it != b) {
        --it;
        insertMulti(it.key(), it.value());
    }
    return *this;
}

template <class Key, class T>
void CMMap<Key, T>::freeData(MMapData *x)
{
    if (MTypeInfo<Key>::isComplex || MTypeInfo<T>::isComplex) {
        MMapData::Node *y = reinterpret_cast<MMapData::Node *>(x);
        MMapData::Node *cur = y;
        MMapData::Node *next = cur->forward[0];
        while (next != y) {
            cur = next;
            next = cur->forward[0];
#if defined(_MSC_VER) && (_MSC_VER >= 1300)
#pragma warning(disable:4189)
#endif
            Node *concreteNode = concrete(cur);
            concreteNode->key.~Key();
            concreteNode->value.~T();
#if defined(_MSC_VER) && (_MSC_VER >= 1300)
#pragma warning(default:4189)
#endif
        }
    }
    x->continueFreeData(payload());
}

template <class Key, class T>
int CMMap<Key, T>::remove(const Key &akey)
{
    detach();

    MMapData::Node *update[MMapData::LastLevel + 1];
    MMapData::Node *cur = e;
    MMapData::Node *next = e;
    int oldSize = d->size;

    for (int i = d->topLevel; i >= 0; i--) {
        while ((next = cur->forward[i]) != e && qMapLessThanKey<Key>(concrete(next)->key, akey))
            cur = next;
        update[i] = cur;
    }

    if (next != e && !qMapLessThanKey<Key>(akey, concrete(next)->key)) {
        BOOL deleteNext = true;
        do {
            cur = next;
            next = cur->forward[0];
            deleteNext = (next != e && !qMapLessThanKey<Key>(concrete(cur)->key, concrete(next)->key));
            concrete(cur)->key.~Key();
            concrete(cur)->value.~T();
            d->node_delete(update, payload(), cur);
        } while (deleteNext);
    }
    return oldSize - d->size;
}

template <class Key, class T>
T CMMap<Key, T>::take(const Key &akey)
{
    detach();

    MMapData::Node *update[MMapData::LastLevel + 1];
    MMapData::Node *cur = e;
    MMapData::Node *next = e;

    for (int i = d->topLevel; i >= 0; i--) {
        while ((next = cur->forward[i]) != e && qMapLessThanKey<Key>(concrete(next)->key, akey))
            cur = next;
        update[i] = cur;
    }

    if (next != e && !qMapLessThanKey<Key>(akey, concrete(next)->key)) {
        T t = concrete(next)->value;
        concrete(next)->key.~Key();
        concrete(next)->value.~T();
        d->node_delete(update, payload(), next);
        return t;
    }
    return T();
}

template <class Key, class T>
typename CMMap<Key, T>::iterator CMMap<Key, T>::erase(iterator it)
{
    MMapData::Node *update[MMapData::LastLevel + 1];
    MMapData::Node *cur = e;
    MMapData::Node *next = e;

    if (it == iterator(e))
        return it;

    for (int i = d->topLevel; i >= 0; i--) {
        while ((next = cur->forward[i]) != e && qMapLessThanKey<Key>(concrete(next)->key, it.key()))
            cur = next;
        update[i] = cur;
    }

    while (next != e) {
        cur = next;
        next = cur->forward[0];
        if (cur == it) {
            concrete(cur)->key.~Key();
            concrete(cur)->value.~T();
            d->node_delete(update, payload(), cur);
            return iterator(next);
        }

        for (int i = 0; i <= d->topLevel; ++i) {
            if (update[i]->forward[i] != cur)
                break;
            update[i] = cur;
        }
    }
    return end();
}

template <class Key, class T>
void CMMap<Key, T>::detach_helper()
{
    union { MMapData *d; MMapData::Node *e; } x;
    x.d = MMapData::createData();
    if (d->size) {
        x.d->insertInOrder = true;
        MMapData::Node *update[MMapData::LastLevel + 1];
        MMapData::Node *cur = e->forward[0];
        update[0] = x.e;
        while (cur != e) {
            Node *concreteNode = concrete(cur);
            node_create(x.d, update, concreteNode->key, concreteNode->value);
            cur = cur->forward[0];
        }
        x.d->insertInOrder = false;
    }
    if (!--d->ref)
        freeData(d);
    d = x.d;
}

template <class Key, class T>
MMapData::Node *CMMap<Key, T>::mutableFindNode(MMapData::Node *aupdate[],
                                                                   const Key &akey) const
{
    MMapData::Node *cur = e;
    MMapData::Node *next = e;

    for (int i = d->topLevel; i >= 0; i--) {
        while ((next = cur->forward[i]) != e && qMapLessThanKey<Key>(concrete(next)->key, akey))
            cur = next;
        aupdate[i] = cur;
    }
    if (next != e && !qMapLessThanKey<Key>(akey, concrete(next)->key)) {
        return next;
    } else {
        return e;
    }
}

template <class Key, class T>
CMList<Key> CMMap<Key, T>::uniqueKeys() const
{
    CMList<Key> res;
    const_iterator i = begin();
    if (i != end()) {
        for (;;) {
            const Key &aKey = i.key();
            res.append(aKey);
            do {
                if (++i == end())
                    goto break_out_of_outer_loop;
            } while (!(aKey < i.key()));   // loop while (key == i.key())
        }
    }
break_out_of_outer_loop:
    return res;
}

template <class Key, class T>
CMList<Key> CMMap<Key, T>::keys() const
{
    CMList<Key> res;
    const_iterator i = begin();
    while (i != end()) {
        res.append(i.key());
        ++i;
    }
    return res;
}

template <class Key, class T>
CMList<Key> CMMap<Key, T>::keys(const T &avalue) const
{
    CMList<Key> res;
    const_iterator i = begin();
    while (i != end()) {
        if (i.value() == avalue)
            res.append(i.key());
        ++i;
    }
    return res;
}

template <class Key, class T>
const Key CMMap<Key, T>::key(const T &avalue) const
{
    return key(avalue, Key());
}

template <class Key, class T>
const Key CMMap<Key, T>::key(const T &avalue, const Key &defaultKey) const
{
    const_iterator i = begin();
    while (i != end()) {
        if (i.value() == avalue)
            return i.key();
        ++i;
    }

    return defaultKey;
}

template <class Key, class T>
CMList<T> CMMap<Key, T>::values() const
{
    CMList<T> res;
    const_iterator i = begin();
    while (i != end()) {
        res.append(i.value());
        ++i;
    }
    return res;
}

template <class Key, class T>
CMList<T> CMMap<Key, T>::values(const Key &akey) const
{
    CMList<T> res;
    MMapData::Node *node = findNode(akey);
    if (node != e) {
        do {
            res.append(concrete(node)->value);
            node = node->forward[0];
        } while (node != e && !qMapLessThanKey<Key>(akey, concrete(node)->key));
    }
    return res;
}

template <class Key, class T>
inline typename CMMap<Key, T>::const_iterator
CMMap<Key, T>::lowerBound(const Key &akey) const
{
    MMapData::Node *update[MMapData::LastLevel + 1];
    mutableFindNode(update, akey);
    return const_iterator(update[0]->forward[0]);
}

template <class Key, class T>
inline typename CMMap<Key, T>::iterator CMMap<Key, T>::lowerBound(const Key &akey)
{
    detach();
    return static_cast<MMapData::Node *>(const_cast<const CMMap *>(this)->lowerBound(akey));
}

template <class Key, class T>
inline typename CMMap<Key, T>::const_iterator
CMMap<Key, T>::upperBound(const Key &akey) const
{
    MMapData::Node *update[MMapData::LastLevel + 1];
    mutableFindNode(update, akey);
    MMapData::Node *node = update[0]->forward[0];
    while (node != e && !qMapLessThanKey<Key>(akey, concrete(node)->key))
        node = node->forward[0];
    return const_iterator(node);
}

template <class Key, class T>
inline typename CMMap<Key, T>::iterator CMMap<Key, T>::upperBound(const Key &akey)
{
    detach();
    return static_cast<MMapData::Node *>(const_cast<const CMMap *>(this)->upperBound(akey));
}

template <class Key, class T>
BOOL CMMap<Key, T>::operator==(const CMMap<Key, T> &other) const
{
    if (size() != other.size())
        return false;
    if (d == other.d)
        return true;

    const_iterator it1 = begin();
    const_iterator it2 = other.begin();

    while (it1 != end()) {
        if (!(it1.value() == it2.value()) || qMapLessThanKey(it1.key(), it2.key()) || qMapLessThanKey(it2.key(), it1.key()))
            return false;
        ++it2;
        ++it1;
    }
    return true;
}

template <class Key, class T>
class QMultiMap : public CMMap<Key, T>
{
public:
    QMultiMap() {}
    QMultiMap(const CMMap<Key, T> &other) : CMMap<Key, T>(other) {}

    inline typename CMMap<Key, T>::iterator replace(const Key &key, const T &value)
    { return CMMap<Key, T>::insert(key, value); }
    inline typename CMMap<Key, T>::iterator insert(const Key &key, const T &value)
    { return CMMap<Key, T>::insertMulti(key, value); }

    inline QMultiMap &operator+=(const QMultiMap &other)
    { unite(other); return *this; }
    inline QMultiMap operator+(const QMultiMap &other) const
    { QMultiMap result = *this; result += other; return result; }

#if !defined(Q_NO_USING_KEYWORD) && !defined(Q_CC_RVCT)
    // RVCT compiler doesn't handle using-keyword right when used functions are overloaded in child class
    using CMMap<Key, T>::contains;
    using CMMap<Key, T>::remove;
    using CMMap<Key, T>::count;
    using CMMap<Key, T>::find;
    using CMMap<Key, T>::constFind;
#else
    inline BOOL contains(const Key &key) const
    { return CMMap<Key, T>::contains(key); }
    inline int remove(const Key &key)
    { return CMMap<Key, T>::remove(key); }
    inline int count(const Key &key) const
    { return CMMap<Key, T>::count(key); }
    inline int count() const
    { return CMMap<Key, T>::count(); }
    inline typename CMMap<Key, T>::iterator find(const Key &key)
    { return CMMap<Key, T>::find(key); }
    inline typename CMMap<Key, T>::const_iterator find(const Key &key) const
    { return CMMap<Key, T>::find(key); }
    inline typename CMMap<Key, T>::const_iterator constFind(const Key &key) const
    { return CMMap<Key, T>::constFind(key); }
#endif

    BOOL contains(const Key &key, const T &value) const;

    int remove(const Key &key, const T &value);

    int count(const Key &key, const T &value) const;

    typename CMMap<Key, T>::iterator find(const Key &key, const T &value) {
        typename CMMap<Key, T>::iterator i(find(key));
        typename CMMap<Key, T>::iterator end(this->end());
        while (i != end && !qMapLessThanKey<Key>(key, i.key())) {
            if (i.value() == value)
                return i;
            ++i;
        }
        return end;
    }
    typename CMMap<Key, T>::const_iterator find(const Key &key, const T &value) const {
        typename CMMap<Key, T>::const_iterator i(constFind(key));
        typename CMMap<Key, T>::const_iterator end(CMMap<Key, T>::constEnd());
        while (i != end && !qMapLessThanKey<Key>(key, i.key())) {
            if (i.value() == value)
                return i;
            ++i;
        }
        return end;
    }
    typename CMMap<Key, T>::const_iterator constFind(const Key &key, const T &value) const
        { return find(key, value); }
private:
    T &operator[](const Key &key);
    const T operator[](const Key &key) const;
};

template <class Key, class T>
inline BOOL QMultiMap<Key, T>::contains(const Key &key, const T &value) const
{
    return constFind(key, value) != CMMap<Key, T>::constEnd();
}

template <class Key, class T>
inline int QMultiMap<Key, T>::remove(const Key &key, const T &value)
{
    int n = 0;
    typename CMMap<Key, T>::iterator i(find(key));
    typename CMMap<Key, T>::const_iterator end(CMMap<Key, T>::constEnd());
    while (i != end && !qMapLessThanKey<Key>(key, i.key())) {
        if (i.value() == value) {
#if defined(Q_CC_RVCT)  
            // RVCT has problems with scoping, apparently.      
            i = CMMap<Key, T>::erase(i);
#else
            i = erase(i);
#endif            
            ++n;
        } else {
            ++i;
        }
    }
    return n;
}

template <class Key, class T>
inline int QMultiMap<Key, T>::count(const Key &key, const T &value) const
{
    int n = 0;
    typename CMMap<Key, T>::const_iterator i(constFind(key));
    typename CMMap<Key, T>::const_iterator end(CMMap<Key, T>::constEnd());
    while (i != end && !qMapLessThanKey<Key>(key, i.key())) {
        if (i.value() == value)
            ++n;
        ++i;
    }
    return n;
}

#endif
