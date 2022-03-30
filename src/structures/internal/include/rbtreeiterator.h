#pragma once

template <typename T>
struct RBTreeIterator
{
public:
    typedef T                             ValueType;
    typedef T&                            ReferenceType;
    typedef T                             * PointerType;


    typedef ValueType                   value_type;
    typedef ReferenceType               reference_type;
    typedef PointerType                 pointer_type;
    typedef ptrdiff_t                   difference_type;

    typedef RBTreeIterator<T>           Self;
    typedef RBTreeNodeBase::BasePointer BasePointer;
    typedef RBTreeNode<T>*              LinkType;


public:
    /**
     * @brief Construct a new RBTreeIterator object
     *
     */
    RBTreeIterator();

    /**
     * @brief Construct a new RBTreeIterator object using a link
     *
     * @param link Link to use when constructing the iterator
     */
    RBTreeIterator( LinkType link );

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
    Self&                               operator ++();

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
    Self&                               operator --();

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
     * @brief Get the base pointer of the node
     */
    BasePointer node;
};

#include <internal/src/rbtreeiterator.inl>