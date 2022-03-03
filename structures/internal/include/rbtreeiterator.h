#pragma once

template <typename T>
struct RBTreeIterator
{
public:
    typedef T                           ValueType;
    typedef T&                          ReferenceType;
    typedef T*                          PointerType;

    typedef RBTreeIterator<T>           Self;
    typedef RBTreeNodeBase::BasePointer BasePointer;
    typedef RBTreeNode<T>*              LinkType;

public:
                                        RBTreeIterator();
                                        RBTreeIterator(LinkType link);

    ReferenceType                       operator *() const;
    PointerType                         operator ->() const;

    Self&                               operator ++();
    Self                                operator ++(int);
    
    Self&                               operator --();
    Self                                operator --(int);

    bool                                operator ==(const Self& other) const;
    bool                                operator !=(const Self& other) const;

public:
    BasePointer                         node;
};

#include "internal/src/rbtreeiterator.inl"