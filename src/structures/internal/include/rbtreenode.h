#pragma once

#include <internal/include/rbtreenodebase.h>

/**
 * @brief Structure to define a node in the red-black tree
 *
 * @tparam Value Generic paramter to denote the type of the values of the nodes
 */
template <typename Value>
struct RBTreeNode : public RBTreeNodeBase
{
public:
    typedef RBTreeNode<Value> * LinkType;

public:
    /**
     * @brief Construct a new RBTreeNode object
     *
     */
    template <typename ... Args>
    RBTreeNode( Args&&... args );

public:
    /**
     * @brief Get the value of the node
     *
     * @return Value Value of the node
     */
    Value value;
};

#include <internal/src/rbtreenode.inl>