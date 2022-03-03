#include "internal/include/rbtreenodebase.h"

RBTreeNodeBase::BasePointer RBTreeNodeBase::minimum(RBTreeNodeBase::BasePointer node)
{
    while (node->left)
        node = node->left;
    return node;
}

RBTreeNodeBase::ConstBasePointer RBTreeNodeBase::minimum(RBTreeNodeBase::ConstBasePointer node)
{
    while (node->left)
        node = node->left;
    return node;
}

RBTreeNodeBase::BasePointer RBTreeNodeBase::maximum(RBTreeNodeBase::BasePointer node)
{
    while (node->right)
        node = node->right;
    return node;
}

RBTreeNodeBase::ConstBasePointer RBTreeNodeBase::maximum(RBTreeNodeBase::ConstBasePointer node)
{
    while (node->right)
        node = node->right;
    return node;
}

RBTreeNodeBase* RBTreeNodeBase::increment(RBTreeNodeBase* node)
{
    if (node->right)
    {
        node = node->right;
        while (node->left != 0)
            node = node->left;
    }
    else
    {
        RBTreeNodeBase* parent = node->parent;
        while(node == parent->right)
        {
            node = parent;
            parent = parent->parent;
        }

        if(node->right != parent)
            node = parent;
    }

    return node;
}

const RBTreeNodeBase* RBTreeNodeBase::increment(const RBTreeNodeBase* node)
{
    return RBTreeNodeBase::increment(const_cast<RBTreeNodeBase*>(node));
}

RBTreeNodeBase* RBTreeNodeBase::decrement(RBTreeNodeBase* node)
{
    if(node->color == RBTreeColor::Red && node->parent->parent == node)
    {
        node = node->right;
    }
    else if (node->left)
    {
        RBTreeNodeBase* left = node->left;
        while (left->right != 0)
            left = left->right;
        node = left;
    }
    else
    {
        RBTreeNodeBase* parent = node->parent;
        while(node == parent->left)
        {
            node = parent;
            parent = parent->parent;
        }

        node = parent;
    }

    return node;
}

const RBTreeNodeBase* RBTreeNodeBase::decrement(const RBTreeNodeBase* node)
{
    return RBTreeNodeBase::decrement(const_cast<RBTreeNodeBase*>(node));
}