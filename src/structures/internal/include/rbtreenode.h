#pragma once

#include <internal/include/rbtreenodebase.h>

template <typename Value>
struct RBTreeNode : public RBTreeNodeBase
{
public:
    typedef RBTreeNode<Value>*  LinkType;

public:
    template <typename... Args>
                                RBTreeNode(Args&&... args);

public:
    Value                       value;

};

#include <internal/src/rbtreenode.inl>