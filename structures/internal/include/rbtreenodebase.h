#pragma once

#include "internal/include/rbtreecolor.h"

struct RBTreeNodeBase
{
public:
    typedef RBTreeNodeBase*         BasePointer;
    typedef const RBTreeNodeBase*   ConstBasePointer;

public:
    static BasePointer          minimum(BasePointer node);
    static ConstBasePointer     minimum(ConstBasePointer node);

    static BasePointer          maximum(BasePointer node);
    static ConstBasePointer     maximum(ConstBasePointer node);

    static BasePointer          increment(BasePointer node);
    static ConstBasePointer     increment(ConstBasePointer node);

    static BasePointer          decrement(BasePointer node);
    static ConstBasePointer     decrement(ConstBasePointer node);

public:
    RBTreeColor color;
    BasePointer parent;
    BasePointer left;
    BasePointer right;
};