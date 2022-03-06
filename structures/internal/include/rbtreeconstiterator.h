#pragma once

#include <internal/include/rbtreeiterator.h>

template <typename T>
struct RBTreeConstIterator
{
public:
    typedef T                                   ValueType;
    typedef const T&                            ReferenceType;
    typedef const T*                            PointerType;

    typedef RBTreeConstIterator<T>              Self;
    typedef RBTreeNodeBase::ConstBasePointer    BasePointer;
    typedef const RBTreeNode<T>*                LinkType;

    typedef RBTreeIterator<T>                   IteratorType;

public:
                                                RBTreeConstIterator();
    explicit                                    RBTreeConstIterator(LinkType link);
                                                RBTreeConstIterator(const IteratorType& other);

    IteratorType                                constCast() const;

    ReferenceType                               operator *() const;
    PointerType                                 operator ->() const;

    Self&                                       operator ++();
    Self                                        operator ++(int);
    
    Self&                                       operator --();
    Self                                        operator --(int);

    bool                                        operator ==(const Self& other) const;
    bool                                        operator !=(const Self& other) const;

public:
    BasePointer                                 node;
};

#include <internal/src/rbtreeconstiterator.inl>