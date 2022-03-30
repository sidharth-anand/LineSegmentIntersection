#pragma once

#include <internal/include/rbtreeiterator.h>

/**
 * @brief Structure to define a constant iterator for the red-black tree
 *
 * @tparam T Generic paramter to denote the type of the values in the tree
 */
template <typename T>
struct RBTreeConstIterator
{
public:
    typedef T                                  ValueType;
    typedef const T&                           ReferenceType;
    typedef const T                            * PointerType;

    typedef RBTreeConstIterator<T>             Self;
    typedef RBTreeNodeBase::ConstBasePointer   BasePointer;
    typedef const RBTreeNode<T>                * LinkType;

    typedef RBTreeIterator<T>                  IteratorType;

public:
    /**
     * @brief Construct a blank RBTreeConstIterator object
     *
     */
    RBTreeConstIterator();

    /**
     * @brief Construct a new RBTreeConstIterator object using a link
     *
     * @param link Link to use when constructing the iterator
     */
    explicit RBTreeConstIterator( LinkType link );

    /**
     * @brief Construct a new RBTreeConstIterator object of a particular type
     *
     * @param other Type of iterator to construct
     */
    RBTreeConstIterator( const IteratorType& other );

    /**
     * @brief Constant cast operator
     *
     * @return IteratorType Type of the iterator
     */
    IteratorType                                constCast() const;

    /**
     * @brief Dereference operator
     *
     * @return ReferenceType Reference to the value of the node
     */
    ReferenceType operator *() const;

    /**
     * @brief Dereference operator
     *
     * @return PointerType Pointer to the value of the node
     */
    PointerType operator ->() const;

    /**
     * @brief Prefix increment operator
     *
     * @return Self Reference to the iterator after incrementing
     */
    Self&                                       operator ++();

    /**
     * @brief Postfix increment operator
     *
     * @return Self Reference to the iterator before incrementing
     */
    Self operator ++( int );

    /**
     * @brief Prefix decrement operator
     *
     * @return Self Reference to the iterator after decrementing
     */
    Self&                                       operator --();

    /**
     * @brief Postfix decrement operator
     *
     * @return Self Reference to the iterator before decrementing
     */
    Self operator --( int );

    /**
     * @brief Equality operator
     *
     * @param other Other iterator to compare to
     * @return true The iterators are equal
     * @return false The iterators are not equal
     */
    bool operator ==( const Self& other ) const;

    /**
     * @brief Inequality operator
     *
     * @param other Other iterator to compare to
     * @return true The iterators are not equal
     * @return false The iterators are equal
     */
    bool operator !=( const Self& other ) const;

public:

    /**
     * @brief Base pointer to the node
     *
     */
    BasePointer node;
};

#include <internal/src/rbtreeconstiterator.inl>