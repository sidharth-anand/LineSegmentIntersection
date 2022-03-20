#pragma once

#include <internal/include/rbtreenodebase.h>

template <typename T>
RBTreeIterator<T>::RBTreeIterator()
    : node(nullptr)
{
}

template <typename T>
RBTreeIterator<T>::RBTreeIterator(RBTreeIterator<T>::LinkType link)
    : node(link)
{
}

template <typename T>
typename RBTreeIterator<T>::ReferenceType RBTreeIterator<T>::operator *() const
{
    return static_cast<typename RBTreeIterator<T>::LinkType>(node)->value;
}

template <typename T>
typename RBTreeIterator<T>::PointerType RBTreeIterator<T>::operator ->() const
{
    return &static_cast<typename RBTreeIterator<T>::LinkType>(node)->value;
}

template <typename T>
RBTreeIterator<T>& RBTreeIterator<T>::operator ++()
{
    node = RBTreeNodeBase::increment(node);
    return *this;
}

template <typename T>
RBTreeIterator<T> RBTreeIterator<T>::operator ++(int)
{
    RBTreeIterator<T> tmp = *this;
    node = RBTreeNodeBase::increment(node);
    return tmp;
}

template <typename T>
RBTreeIterator<T>& RBTreeIterator<T>::operator --()
{
    node = RBTreeNodeBase::decrement(node);
    return *this;
}

template <typename T>
RBTreeIterator<T> RBTreeIterator<T>::operator --(int)
{
    RBTreeIterator<T> tmp = *this;
    node = RBTreeNodeBase::decrement(node);
    return tmp;
}

template <typename T>
bool RBTreeIterator<T>::operator ==(const RBTreeIterator<T>& other) const
{
    return node == other.node;
}

template <typename T>
bool RBTreeIterator<T>::operator !=(const RBTreeIterator<T>& other) const
{
    return node != other.node;
}