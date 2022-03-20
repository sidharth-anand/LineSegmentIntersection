#pragma once

template <typename Value>
template <typename... Args>
RBTreeNode<Value>::RBTreeNode(Args&&... args)
    : RBTreeNodeBase()
    , value(std::forward<Args>(args)...)
{
}