#pragma once

#include <internal/include/rbtreecolor.h>

struct RBTreeNodeBase
{
public:
    typedef RBTreeNodeBase         * BasePointer;
    typedef const RBTreeNodeBase   * ConstBasePointer;

public:
    /**
     * @brief Get the pointer to the node containing the least value in the subtree
     *
     * @param node Node whose subtree to check
     * @return BasePointer to the node containing the least value
     */
    static BasePointer          minimum( BasePointer node );

    /**
     * @brief Get the pointer to the node containing the least value in the subtree
     *
     * @param node Node whose subtree to check
     * @return ConstBasePointer to the node containing the least value
     */
    static ConstBasePointer     minimum( ConstBasePointer node );

    /**
     * @brief Get the pointer to the node containing the greatest value in the subtree
     *
     * @param node Node whose subtree to check
     * @return BasePointer to the node containing the greatest value
     */
    static BasePointer          maximum( BasePointer node );

    /**
     * @brief Get the pointer to the node containing the greatest value in the subtree
     *
     * @param node Node whose subtree to check
     * @return ConstBasePointer to the node containing the greatest value
     */
    static ConstBasePointer     maximum( ConstBasePointer node );

    /**
     * @brief Increment the node's value by 1
     *
     * @param node Node whose value to increment
     * @return BasePointer to the incremented node
     */
    static BasePointer          increment( BasePointer node );

    /**
     * @brief Decrement the node's value by 1
     *
     * @param node Node whose value to decrement
     * @return BasePointer to the decremented node
     */
    static ConstBasePointer     increment( ConstBasePointer node );

    /**
     * @brief Decrement the node's value by 1
     *
     * @param node Node whose value to decrement
     * @return BasePointer to the decremented node
     */
    static BasePointer          decrement( BasePointer node );

    /**
     * @brief Decrement the node's value by 1
     *
     * @param node Node whose value to decrement
     * @return ConstBasePointer to the decremented node
     */
    static ConstBasePointer     decrement( ConstBasePointer node );

public:
    RBTreeColor color;
    BasePointer parent;
    BasePointer left;
    BasePointer right;
};