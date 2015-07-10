// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:
//  Author:
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <stdlib.h>
#include <string.h>
#include "cmlist.h"

MListData::Data MListData::shared_null = { 1, 0, 0, 0, true, { 0 } };

int allocmore(int alloc, int extra)
{
    if (alloc == 0 && extra == 0)
        return 0;
    const int page = 1 << 12;
    int nalloc;
    alloc += extra;
    if (alloc < 1<<6) {
        nalloc = (1<<3) + ((alloc >>3) << 3);
    } else  {
        // don't do anything if the loop will overflow signed int.
        if (alloc >= INT_MAX/2)
            return INT_MAX;
        nalloc = (alloc < page) ? 1 << 3 : page;
        while (nalloc < alloc) {
            if (nalloc <= 0)
                return INT_MAX;
            nalloc *= 2;
        }
    }
    return nalloc - extra;
}

static int grow(int size)
{
    // dear compiler: don't optimize me out.
    volatile int x = allocmore(size * sizeof(void *), MListData::DataHeaderSize) / sizeof(void *);
    return x;
}

//MListData::Data *MListData::detach()
//{
//    Data *x = static_cast<Data *>(::malloc(DataHeaderSize + d->alloc * sizeof(void *)));
//    if (!x)
//        qFatal("CMList: Out of memory");
//
//    ::memcpy(x, d, DataHeaderSize + d->alloc * sizeof(void *));
//    x->alloc = d->alloc;
//    x->ref = 1;
//    x->sharable = true;
//    if (!x->alloc)
//        x->begin = x->end = 0;
//
//    qSwap(d, x);
//    if (!x->ref.deref())
//        return x;
//    return 0;
//}

// Returns the old (shared) data, it is up to the caller to deref() and free()
MListData::Data *MListData::detach2()
{
    Data *x = d;
    d = static_cast<Data *>(::malloc(DataHeaderSize + x->alloc * sizeof(void *)));
    //if (!d)
    //    qFatal("CMList: Out of memory");

    memcpy(d, x, DataHeaderSize + x->alloc * sizeof(void *));
    d->alloc = x->alloc;
    d->ref = 1;
    d->sharable = true;
    if (!d->alloc)
        d->begin = d->end = 0;

    return x;
}

void MListData::realloc(int alloc)
{
    ASSERT(d->ref == 1);
    Data *x = static_cast<Data *>(::realloc(d, DataHeaderSize + alloc * sizeof(void *)));
    //if (!x)
    //    qFatal("CMList: Out of memory");

    d = x;
    d->alloc = alloc;
    if (!alloc)
        d->begin = d->end = 0;
}

void **MListData::append()
{
    ASSERT(d->ref == 1);
    if (d->end == d->alloc) {
        int n = d->end - d->begin;
        if (d->begin > 2 * d->alloc / 3) {
            ::memcpy(d->array + n, d->array + d->begin, n * sizeof(void *));
            d->begin = n;
            d->end = n * 2;
        } else {
            realloc(grow(d->alloc + 1));
        }
    }
    return d->array + d->end++;
}

void **MListData::append(const MListData& l)
{
    ASSERT(d->ref == 1);
    int e = d->end;
    int n = l.d->end - l.d->begin;
    if (n) {
        if (e + n > d->alloc)
            realloc(grow(e + l.d->end - l.d->begin));
        ::memcpy(d->array + d->end, l.d->array + l.d->begin, n * sizeof(void*));
        d->end += n;
    }
    return d->array + e;
}

void **MListData::prepend()
{
    ASSERT(d->ref == 1);
    if (d->begin == 0) {
        if (d->end >= d->alloc / 3)
            realloc(grow(d->alloc + 1));

        if (d->end < d->alloc / 3)
            d->begin = d->alloc - 2 * d->end;
        else
            d->begin = d->alloc - d->end;

        ::memmove(d->array + d->begin, d->array, d->end * sizeof(void *));
        d->end += d->begin;
    }
    return d->array + --d->begin;
}

void **MListData::insert(int i)
{
    ASSERT(d->ref == 1);
    if (i <= 0)
        return prepend();
    if (i >= d->end - d->begin)
        return append();

    bool leftward = false;
    int size = d->end - d->begin;

    if (d->begin == 0) {
        if (d->end == d->alloc) {
            // If the array is full, we expand it and move some items rightward
            realloc(grow(d->alloc + 1));
        } else {
            // If there is free space at the end of the array, we move some items rightward
        }
    } else {
        if (d->end == d->alloc) {
            // If there is free space at the beginning of the array, we move some items leftward
            leftward = true;
        } else {
            // If there is free space at both ends, we move as few items as possible
            leftward = (i < size - i);
        }
    }

    if (leftward) {
        --d->begin;
        ::memmove(d->array + d->begin, d->array + d->begin + 1, i * sizeof(void *));
    } else {
        ::memmove(d->array + d->begin + i + 1, d->array + d->begin + i,
                  (size - i) * sizeof(void *));
        ++d->end;
    }
    return d->array + d->begin + i;
}

void MListData::remove(int i)
{
    ASSERT(d->ref == 1);
    i += d->begin;
    if (i - d->begin < d->end - i) {
        if (int offset = i - d->begin)
            ::memmove(d->array + d->begin + 1, d->array + d->begin, offset * sizeof(void *));
        d->begin++;
    } else {
        if (int offset = d->end - i - 1)
            ::memmove(d->array + i, d->array + i + 1, offset * sizeof(void *));
        d->end--;
    }
}

void MListData::remove(int i, int n)
{
    ASSERT(d->ref == 1);
    i += d->begin;
    int middle = i + n/2;
    if (middle - d->begin < d->end - middle) {
        ::memmove(d->array + d->begin + n, d->array + d->begin,
                   (i - d->begin) * sizeof(void*));
        d->begin += n;
    } else {
        ::memmove(d->array + i, d->array + i + n,
                   (d->end - i - n) * sizeof(void*));
        d->end -= n;
    }
}

void MListData::move(int from, int to)
{
    ASSERT(d->ref == 1);
    if (from == to)
        return;

    from += d->begin;
    to += d->begin;
    void *t = d->array[from];

    if (from < to) {
        if (d->end == d->alloc || 3 * (to - from) < 2 * (d->end - d->begin)) {
            ::memmove(d->array + from, d->array + from + 1, (to - from) * sizeof(void *));
        } else {
            // optimization
            if (int offset = from - d->begin)
                ::memmove(d->array + d->begin + 1, d->array + d->begin, offset * sizeof(void *));
            if (int offset = d->end - (to + 1))
                ::memmove(d->array + to + 2, d->array + to + 1, offset * sizeof(void *));
            ++d->begin;
            ++d->end;
            ++to;
        }
    } else {
        if (d->begin == 0 || 3 * (from - to) < 2 * (d->end - d->begin)) {
            ::memmove(d->array + to + 1, d->array + to, (from - to) * sizeof(void *));
        } else {
            // optimization
            if (int offset = to - d->begin)
                ::memmove(d->array + d->begin - 1, d->array + d->begin, offset * sizeof(void *));
            if (int offset = d->end - (from + 1))
                ::memmove(d->array + from, d->array + from + 1, offset * sizeof(void *));
            --d->begin;
            --d->end;
            --to;
        }
    }
    d->array[to] = t;
}

void **MListData::erase(void **xi)
{
    ASSERT(d->ref == 1);
    int i = xi - (d->array + d->begin);
    remove(i);
    return d->array + d->begin + i;
}
