// //////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009,
//  All rights reserved.
//  
//  FileName:
//  Description:map class as std::map, board from QT
//  Author:roy
// //////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <string.h>
#include "cmmap.h"

MMapData MMapData::shared_null = {
    &shared_null,
    { &shared_null, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    1, 0, 0, 0, false, true
};

MMapData *MMapData::createData()
{
    MMapData *d = new MMapData;
    Node *e = reinterpret_cast<Node *>(d);
    e->backward = e;
    e->forward[0] = e;
    d->ref = 1;
    d->topLevel = 0;
    d->size = 0;
    d->randomBits = 0;
    d->insertInOrder = false;
    d->sharable = true;
    return d;
}

void MMapData::continueFreeData(int offset)
{
    Node *e = reinterpret_cast<Node *>(this);
    Node *cur = e->forward[0];
    Node *prev;
    while (cur != e) {
        prev = cur;
        cur = cur->forward[0];
        ::free(reinterpret_cast<char *>(prev) - offset);
    }
    delete this;
}

MMapData::Node *MMapData::node_create(Node *update[], int offset)
{
    int level = 0;
    unsigned int mask = (1 << Sparseness) - 1;

    while ((randomBits & mask) == mask && level < LastLevel) {
        ++level;
        mask <<= Sparseness;
    }

    ++randomBits;
    if (level == 3 && !insertInOrder)
        randomBits = ::rand();

    if (level > topLevel) {
        Node *e = reinterpret_cast<Node *>(this);
        level = ++topLevel;
        e->forward[level] = e;
        update[level] = e;
    }

    void *concreteNode = ::malloc(offset + sizeof(Node) + level * sizeof(Node *));
    memset(concreteNode, 0, offset + sizeof(Node) + level * sizeof(Node *));
    Node *abstractNode = reinterpret_cast<Node *>(reinterpret_cast<char *>(concreteNode) + offset);

    abstractNode->backward = update[0];
    update[0]->forward[0]->backward = abstractNode;

    for (int i = level; i >= 0; i--) {
        abstractNode->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = abstractNode;
        update[i] = abstractNode;
    }
    ++size;
    return abstractNode;
}

void MMapData::node_delete(Node *update[], int offset, Node *node)
{
    node->forward[0]->backward = node->backward;

    for (int i = 0; i <= topLevel; ++i) {
        if (update[i]->forward[i] != node)
            break;
        update[i]->forward[i] = node->forward[i];
    }
    --size;
    ::free(reinterpret_cast<char *>(node) - offset);
}
