#pragma once

#include <internal/include/rbtreenodebase.h>

template <typename T>
RBTreeConstIterator<T>::RBTreeConstIterator()
    : node(nullptr)
{
}

template <typename T>
RBTreeConstIterator<T>::RBTreeConstIterator(RBTreeConstIterator<T>::LinkType link)
    : node(link)
{
}

template <typename T>
RBTreeConstIterator<T>::RBTreeConstIterator(const RBTreeIterator<T>& iterator)
    : node(iterator.node)
{
}

template <typename T>
typename RBTreeConstIterator<T>::IteratorType RBTreeConstIterator<T>::constCast() const
{
    return IteratorType(static_cast<typename IteratorType::LinkType>(const_cast<typename IteratorType::BasePointer>(node)));
}

template <typename T>
typename RBTreeConstIterator<T>::ReferenceType RBTreeConstIterator<T>::operator *() const
{
    return static_cast<RBTreeConstIterator<T>::LinkType>(node)->value;
}

template <typename T>
typename RBTreeConstIterator<T>::PointerType RBTreeConstIterator<T>::operator ->() const
{
    return &static_cast<RBTreeConstIterator<T>::LinkType>(node)->value;
}

template <typename T>
RBTreeConstIterator<T>& RBTreeConstIterator<T>::operator ++()
{
    node = RBTreeNodeBase::increment(node);
    return *this;
}

template <typename T>
RBTreeConstIterator<T> RBTreeConstIterator<T>::operator ++(int)
{
    RBTreeConstIterator<T> tmp = *this;
    node = RBTreeNodeBase::increment(node);
    return tmp;
}

template <typename T>
RBTreeConstIterator<T>& RBTreeConstIterator<T>::operator --()
{
    node = RBTreeNodeBase::decrement(node);
    return *this;
}

template <typename T>
RBTreeConstIterator<T> RBTreeConstIterator<T>::operator --(int)
{
    RBTreeConstIterator<T> tmp = *this;
    node = RBTreeNodeBase::decrement(node);
    return tmp;
}

template <typename T>
bool RBTreeConstIterator<T>::operator ==(const RBTreeConstIterator<T>& other) const
{
    return node == other.node;
}

template <typename T>
bool RBTreeConstIterator<T>::operator !=(const RBTreeConstIterator<T>& other) const
{
    return node != other.node;
}