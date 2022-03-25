#pragma once

#include <memory>

#include <internal/include/rbtreecolor.h>
#include <internal/include/rbtreenodebase.h>
#include <internal/include/rbtreenode.h>
#include <internal/include/rbtreeiterator.h>
#include <internal/include/rbtreeconstiterator.h>
#include <internal/include/rbtreeutils.h>

// TODO: Add concepts for each type here
template <typename KeyType, typename MappedType, typename Comparison = std::less<KeyType>, typename ValueType = std::pair<const KeyType, MappedType>, typename Allocator = std::allocator<ValueType>, typename KeySelector = Select1<ValueType> >
class RBTree
{
private:
    typedef typename std::allocator_traits<Allocator>::template rebind_alloc<RBTreeNode<ValueType> >   NodeAllocator;

protected:
    typedef RBTreeNodeBase                                                                             * BasePointer;
    typedef const RBTreeNodeBase                                                                       * ConstBasePointer;

public:
    typedef ValueType                                                                                  * Pointer;
    typedef const ValueType                                                                            * ConstPointer;
    typedef ValueType&                                                                                 Reference;
    typedef const ValueType&                                                                           ConstReference;

    typedef RBTreeNode<ValueType>                                                                      * LinkType;
    typedef const RBTreeNode<ValueType>                                                                * ConstLinkType;

    typedef std::size_t                                                                                SizeType;
    typedef Allocator                                                                                  AllocatorType;

    typedef RBTreeIterator<ValueType>                                                                  Iterator;
    typedef RBTreeConstIterator<ValueType>                                                             ConstIterator;
    typedef RBTreeIterator<ValueType>                                                                  ReverseIterator; // TODO: Fix reverse iterator types
    typedef RBTreeConstIterator<ValueType>                                                             ConstReverseIterator;

public:
    /**
     * @brief Constructs an empty RBTree
     */
    RBTree();

    /**
     * @brief Constructs an RBTree with a given comparison and allocator
     *
     * @param comparison The comparison function
     * @param allocator The allocator to use
     */
    explicit RBTree( const Comparison& comparison, const AllocatorType& allocator = AllocatorType() );

    /**
     * @brief Construct a new RBTree object using another RBTree
     *
     * @param other RBTree to use to copy values and structure from to construct this RBTree
     */
    RBTree( const RBTree& other );

    /**
     * @brief Construct a new RBTree object using another RBTree
     *
     * @param other RBTree to use to copy values and structure from to construct this RBTree
     */
    RBTree( RBTree&& other );

    /**
     * @brief Construct a new RBTree object using a list of values to be inserted
     *
     * The RBTree is first created empty, then the values are inserted into the RBTree sequentially
     *
     * @param values List of values to insert into the RBTree in the sequence of their required insertion
     */
    RBTree( std::initializer_list<ValueType> values );

    template <typename InputIterator> // TOOD: Add concept

    /**
     * @brief Construct a new RBTree object using input iterators that point to the beginning and ending nodes
     *
     * @param first input iterator pointing to the beginning node
     * @param last input iterator pointing to the ending node
     */
    RBTree( InputIterator first, InputIterator last );

    /**
     * @brief Generic type to use InputIterator
     *
     * @tparam InputIterator
     */
    template <typename InputIterator> // Todo: Add concept

    /**
     * @brief Construct a new RBTree object using input iterators pointing to the the beginning and ending nodes, a given comparison, and allocator
     *
     * @param first Input iterator for the first nodes
     * @param last Input iterator for the last nodes
     * @param comparison The comparison function
     * @param allocator The allocator to use
     */
    RBTree( InputIterator first, InputIterator last, const Comparison& comparison, const AllocatorType& allocator = AllocatorType() );

    /**
     * @brief Destructor for RBTree
     */
    ~RBTree();

    /**
     * @brief Get the Node Allocator object
     *
     * @return NodeAllocator The node allocator
     */
    NodeAllocator &getNodeAllocator();

    /**
     * @brief Get the Node Allocator object
     *
     * @return const NodeAllocator& The node allocator
     */
    const NodeAllocator &getNodeAllocator() const;

    /**
     * @brief Get the type of the node allocator
     *
     * @return AllocatorType Type of the node allocator
     */
    AllocatorType getAllocator() const;

    /**
     * @brief Assignment operator for RBTree
     *
     * @param other RBTree to assign
     */
    RBTree &operator=( const RBTree& other );

    /**
     * @brief Assignment operator for RBTree
     *
     * @param other Pointer to pointer of RBTree to assign
     */
    RBTree &operator=( RBTree&& other );

    /**
     * @brief Assignment operator for RBTree with list of values
     *
     * @param values List of values to assign and construct RB tree from
     */
    RBTree &operator=( std::initializer_list<ValueType> values );

    /**
     * @brief Get an iterator pointing to the beginning of the RBTree
     *
     * @return Iterator pointing to the beginning of the RBTree
     */
    Iterator begin();

    /**
     * @brief Get a constant iterator pointing to the beginning of the RBTree
     *
     * @return ConstIterator pointing to the beginning of the RBTree
     */
    ConstIterator begin() const;

    /**
     * @brief Get an iterator pointing to the end of the RBTree
     *
     * @return Iterator pointing to the end of the RBTree
     */
    Iterator end();

    /**
     * @brief Get a constant iterator pointing to the end of the RBTree
     *
     * @return ConstIterator pointing to the end of the RBTree
     */
    ConstIterator end() const;

    /**
     * @brief Get a reverse iterator pointing to the beginning of the reversed RBTree
     *
     * @return ReverseIterator pointing to the beginning of the reversed RBTree
     */
    ReverseIterator rbegin();

    /**
     * @brief Get a constant reverse iterator pointing to the beginning of the reversed RBTree
     *
     * @return ConstReverseIterator pointing to the beginning of the reversed RBTree
     */
    ConstReverseIterator rbegin() const;

    /**
     * @brief Get a reverse iterator pointing to the end of the reversed RBTree
     *
     * @return ReverseIterator pointing to the end of the reversed RBTree
     */
    ReverseIterator rend();

    /**
     * @brief Get a constant reverse iterator pointing to the end of the reversed RBTree
     *
     * @return ConstReverseIterator pointing to the end of the reversed RBTree
     */
    ConstReverseIterator rend() const;

    /**
     * @brief Get a constant interator pointing to the beginning of the RBTree
     *
     * @return ConstIterator pointing to the beginning of the RBTree
     */
    ConstIterator cbegin() const;

    /**
     * @brief Get a constant interator pointing to the end of the RBTree
     *
     * @return ConstIterator pointing to the end of the RBTree
     */
    ConstIterator cend() const;

    /**
     * @brief Get a constant reverse iterator pointing to the beginning of the reversed RBTree
     *
     * @return ConstReverseIterator pointing to the beginning of the reversed RBTree
     */
    ConstReverseIterator crbegin() const;

    /**
     * @brief Get a constant reverse iterator pointing to the end of the reversed RBTree
     *
     * @return ConstReverseIterator pointing to the end of the reversed RBTree
     */
    ConstReverseIterator crend() const;

    /**
     * @brief Check if the RBTree is empty
     *
     * @return true if empty
     * @return false if not empty
     */
    bool empty() const;

    /**
     * @brief Get the number of elements stored in the RBTree
     *
     * @return SizeType The number of elements
     */
    SizeType size() const;

    /**
     * @brief Get the maximum number of elements the RBTree can store
     *
     * @return SizeType The maximum number of elements
     */
    SizeType maxSize() const;

    MappedType &operator[]( const KeyType& key );
    MappedType &operator[]( KeyType&& key );
    MappedType &at( const KeyType& key );
    const MappedType &at( const KeyType& key ) const;

    /**
     * @brief Insert the value in the RBTree
     *
     * @param value Value to insert
     * @return Pair of iterator and boolean. Iterator points to the inserted value, boolean is true if the value was inserted, false otherwise
     */
    std::pair<Iterator, bool> insert( const ValueType& value );

    /**
     * @brief Insert a list of values into the RBTree
     *
     * @param values List of values to insert
     */
    void insert( std::initializer_list<ValueType> values );

    /**
     * @brief Insert the value in the RBTree at the given position
     *
     * @param position Position to insert value at
     * @param value Value to insert
     * @return Iterator that points to the inserted value
     */
    Iterator insert( ConstIterator position, const ValueType& value );

    /**
     * @brief Erases the value in the RBTree pointed to by the given position
     *
     * @param position Position to erase value at
     * @return Iterator that points to the value before the erased value
     */
    Iterator erase( ConstIterator position );

    /**
     * @brief Erases all the elements in the RBTree with the given key
     *
     * @param key Key of elements to erase
     * @return SizeType Number of elements erased
     */
    SizeType erase( const KeyType& key );

    /**
     * @brief Erases elements in the RBTree pointed to by the range of the given iterators
     *
     * @param first Iterator that points to the start of the range of elements to delete
     * @param last Iterator that points to the end of the range of elements to delete
     * @return Iterator invalidated with the erased elements.
     */
    Iterator erase( ConstIterator first, ConstIterator last );

    /**
     * @brief Erases all the elements in the RBTree with the given keys
     *
     * @param first First key of values to delete
     * @param last Second key of values to delete
     */
    void erase( const KeyType& first, const KeyType& last );

    /**
     * @brief Swaps the contents of two tree
     *
     * @param tree Tree to swap with
     */
    void swap( RBTree& tree );

    /**
     * @brief Erases all the elements in the RBTree
     */
    void clear();

    /**
     * @brief Get the key comparison function used by the RBTree
     *
     * @return Comparison function
     */
    Comparison compareKeys() const;
    // TODO: Look into adding a value comparison mechanism that uses KeyFromValue to determine order

    /**
     * @brief Finds an iterator to the first value in the RBTree with the given key, or to the end if not found
     *
     * @param key Key to find value for
     * @return Iterator to the found value, or the end if not found
     */
    Iterator find( const KeyType& key );

    /**
     * @brief Finds an iterator to the first value in the RBTree with the given key, or to the end if not found
     *
     * @param key Key to find value for
     * @return ConstIterator to the found value, or the end if not found
     */
    ConstIterator find( const KeyType& key ) const;

    /**
     * @brief Get the number of contained elements with the given value in the RBTree
     *
     * @param key Value to check
     * @return SizeType Count of the number of elements with the given key
     */
    SizeType count( const KeyType& key ) const;

    /**
     * @brief Get an iterator to the first element whose key is not less than the given key, or to the end if not found.
     *
     * @param key Key to check
     * @return Iterator to the first element whose key is not less than the given key, or to the end if not found.
     */
    Iterator lowerBound( const KeyType& key );

    /**
     * @brief Get an iterator to the first element whose key is not less than the given key, or to the end if not found.
     *
     * @param key Key to check
     * @return ConstIterator to the first element whose key is not less than the given key, or to the end if not found.
     */
    ConstIterator lowerBound( const KeyType& key ) const;

    /**
     * @brief Get an iterator to the first element whose key is greater than the given key, or to the end if not found.
     *
     * @param key Key to check
     * @return Iterator to the first element whose key is greater than the given key, or to the end if not found.
     */
    Iterator upperBound( const KeyType& key );

    /**
     * @brief Get an iterator to the first element whose key is greater than the given key, or to the end if not found.
     *
     * @param key Key to check
     * @return ConstIterator to the first element whose key is greater than the given key, or to the end if not found.
     */
    ConstIterator upperBound( const KeyType& key ) const;

    /**
     * @brief Get range containing all elements whose key is the given key and an empty range that indicates the position where those elements would be if there are no elements found.
     *
     * @param key Key to find range containing all elements
     * @return Pair of iterators to the range
     */
    std::pair<Iterator, Iterator> equalRange( const KeyType& key );

    /**
     * @brief Get range containing all elements whose key is the given key and an empty range that indicates the position where those elements would be if there are no elements found.
     *
     * @param key Key to find range containing all elements
     * @return Pair of constant iterators to the range
     */
    std::pair<ConstIterator, ConstIterator> equalRange( const KeyType& key ) const;

protected:
    /**
     * @brief Get the root node of the RBTree
     *
     * @return LinkType Root node
     */
    LinkType getNode();

    /**
     * @brief Put a node in the RBTree
     *
     * @return LinkType Pointer to the node to insert
     */
    void putNode( LinkType node );

    /**
     * @brief Create a Node object
     *
     * @tparam Args generic arguments
     * @param args pointer to the arguments
     * @return LinkType of the created node
     */
    template <typename ... Args>
    LinkType createNode( Args && ... args );

    /**
     * @brief Destroys the given node
     *
     * @param node to destroy
     */
    void destroyNode( LinkType node );

    /**
     * @brief Create a deep copy of the given node
     *
     * @param node to create a deep copy of
     * @return LinkType of the created node
     */
    LinkType cloneNode( ConstLinkType node );

    /**
     * @brief Get the pointer to the root of the RBTree
     *
     * @return BasePointer& Pointer to the root of the RBTree
     */
    BasePointer &root();

    /**
     * @brief Get the pointer to the root of the RBTree
     *
     * @return ConstBasePointer& Pointer to the root of the RBTree
     */
    ConstBasePointer root() const;

    /**
     * @brief Get the pointer to the leftmost child of the RBTree
     *
     * @return BasePointer Pointer to the leftmost child of the RBTree
     */
    BasePointer &leftmost();

    /**
     * @brief Get the pointer to the leftmost child of the RBTree
     *
     * @return ConstBasePointer Pointer to the leftmost child of the RBTree
     */
    ConstBasePointer leftmost() const;

    /**
     * @brief Get the pointer to the rightmost child of the RBTree
     *
     * @return BasePointer Pointer to the rightmost child of the RBTree
     */
    BasePointer &rightmost();

    /**
     * @brief Get the pointer to the rightmost child of the RBTree
     *
     * @return ConstBasePointer Pointer to the rightmost child of the RBTree
     */
    ConstBasePointer rightmost() const;

    /**
     * @brief Begin the link
     *
     * @return LinkType
     */
    LinkType linkBegin();

    /**
     * @brief Begin the link
     *
     * @return ConstLinkType
     */
    ConstLinkType linkBegin() const;

    /**
     * @brief End the link
     *
     * @return LinkType
     */
    LinkType linkEnd();

    /**
     * @brief End the link
     *
     * @return ConstLinkType
     */
    ConstLinkType linkEnd() const;

    /**
     * @brief Get the value at a given node
     *
     * @param node Node to get the value of
     * @return ConstReference Value of the given node
     */
    static ConstReference value( ConstLinkType node );

    /**
     * @brief Get the key at a given node
     *
     * @param node Node to get the key of
     * @return ConstKeyReference Key of the given node
     */
    static const KeyType &key( ConstLinkType node );

    /**
     * @brief Get the node on the left (left child) of the given node
     *
     * @param node Node to get the left child of
     * @return LinkType Linked node
     */
    static LinkType left( BasePointer node );

    /**
     * @brief Get the node on the left (left child) of the given node
     *
     * @param node Node to get the left child of
     * @return ConstLinkType Linked node
     */
    static ConstLinkType left( ConstBasePointer node );

    /**
     * @brief Get the node on the right (right child) of the given node
     *
     * @param node Node to get the right child of
     * @return LinkType Linked node
     */
    static LinkType right( BasePointer node );

    /**
     * @brief Get the node on the right (right child) of the given node
     *
     * @param node Node to get the right child of
     * @return ConstLinkType Linked node
     */
    static ConstLinkType right( ConstBasePointer node );

    /**
     * @brief Get the value at a given node
     *
     * @param node Node to get the value of
     * @return ConstReference Value of the given node
     */
    static ConstReference value( ConstBasePointer node );

    /**
     * @brief Get the key at a given node
     *
     * @param node Node to get the key of
     * @return ConstKeyReference Key of the given node
     */
    static const KeyType &key( ConstBasePointer node );

    /**
     * @brief Get the minimum valued node in the sub tree of a given node
     *
     * @param node Node to get the minimum valued node in its sub tree
     * @return BasePointer Pointer to the minimum valued node
     */
    static BasePointer minimum( BasePointer node );

    /**
     * @brief Get the minimum valued node in the sub tree of a given node
     *
     * @param node Node to get the minimum valued node in its sub tree
     * @return ConstBasePointer Pointer to the minimum valued node
     */
    static ConstBasePointer minimum( ConstBasePointer node );

    /**
     * @brief Get the maximum valued node in the sub tree of a given node
     *
     * @param node Node to get the maximum valued node in its sub tree
     * @return BasePointer Pointer to the maximum valued node
     */
    static BasePointer maximum( BasePointer node );

    /**
     * @brief Get the maximum valued node in the sub tree of a given node
     *
     * @param node Node to get the maximum valued node in its sub tree
     * @return ConstBasePointer Pointer to the maximum valued node
     */
    static ConstBasePointer maximum( ConstBasePointer node );

    /**
     * @brief Insert a unique value in the tree
     *
     * @tparam T Generic type to denote the type of value
     * @param value Value to insert
     * @return std::pair<Iterator, bool> Iterator to the inserted value and a boolean to indicate if the value was inserted
     */
    template <typename T>
    std::pair<Iterator, bool> insertUnique( T&& value );

    /**
     * @brief Insert a unique value in the tree at a given position
     *
     * @tparam T Generic type to denote the type of value
     * @param value Value to insert
     * @param position Position to insert the value at
     * @return Iterator to the inserted value
     */
    template <typename T>
    Iterator insertUnique( ConstIterator position, T&& value );

    /**
     * @brief Deletes the value in the RBTree with iterators
     *
     * @param first Iterator that points to the first value
     * @param last Iterator that points to the last value
     * @return Iterator that points to the deleted value
     */
    template <typename InputIterator> // TODO: add concept for input iterator
    void insertUnique( InputIterator first, InputIterator last );

    /**
     * @brief Inserts value into the tree before the upper bound
     *
     * @tparam T Generic type to denote the type of value
     * @param value Value to insert
     * @return Iterator to the inserted value
     */
    template <typename T>
    Iterator insertEqual( T&& value );

    /**
     * @brief Inserts value into the tree using an iterator as a hint as to where to insert the value
     *
     * @tparam T Generic type to denote the type of value
     * @param position Hint iterator
     * @param value Value to insert
     * @return Iterator to the inserted value
     */
    template <typename T>
    Iterator insertEqual( ConstIterator position, T&& value );

    /**
     * @brief Inserts each element of a range before the upper bound of the key of each element
     *
     * @tparam T Generic type to denote the type of value
     * @param first Iterator that points to the first value
     * @param last Iterator that points to the last value
     */
    template <typename InputIterator> // TODO: add concept for input iterator
    void insertEqual( InputIterator first, InputIterator last );

private:
    /**
     * @brief Initialize the RBTree
     *
     */
    void initialize();

    /**
     * @brief Insert a value and a given position
     *
     * @tparam T Generic type to denote the type of value
     * @param x X coordinate to insert value at
     * @param y Y coordinate to insert value at
     * @param value Value to insert
     * @return Iterator to the value inserted
     */
    template <typename T>
    Iterator insert( ConstBasePointer x, ConstBasePointer y, T&& value );

    /**
     * @brief Insert value at a position before the given position
     *
     * @tparam T Generic type to denote the type of value
     * @param x X coordinate to insert value before
     * @param y Y coordinate to insert value before
     * @param value Value to insert
     * @return Iterator to the value inserted
     */
    template <typename T>
    Iterator insertLower( BasePointer x, BasePointer y, T&& value );

    /**
     * @brief Insert value at or before a given position
     *
     * @tparam T Generic type to denote the type of value
     * @param x X coordinate of the position
     * @param y Y coordinate of the position
     * @param value Value to insert
     * @return Iterator to the value inserted
     */
    template <typename T>
    Iterator insertEqualLower( T&& value );

    /**
     * @brief Create a copy of the RBTree
     *
     * @param x X coordinate of the position to take the subtree from
     * @param y Y coordinate of the position to take the subtree from
     * @return LinkType Link to the copied subtree
     */
    LinkType copy( ConstLinkType x, LinkType y );

    /**
     * @brief Erases the value using a given link
     *
     * @param x Link to the value to erase
     */
    void erase( LinkType x );

    /**
     * @brief Erases the element pointed to by an iterator.
     *
     * @param position Iterator that points to the position of the value to erase
     */
    void auxilliaryErase( ConstIterator position );

    /**
     * @brief Erases the element pointed to by two iterators
     *
     * @param first Beginning range
     * @param last Ending range
     */
    void auxilliaryErase( ConstIterator first, ConstIterator last );

    /**
     * @brief Returns an iterator to the first element whose key is not less than key or end, if that element does not exist.
     *
     * @param x Link to the node to search from
     * @param y Link to the node to search to
     * @param key Key to search for
     * @return Iterator Iterator till the first element whose key is not less than key or end.
     */
    Iterator lowerBound( LinkType x, LinkType y, const KeyType& key );

    /**
     * @brief Returns an iterator to the first element whose key is not less than key or end, if that element does not exist.
     *
     * @param x Link to the node to search from
     * @param y Link to the node to search to
     * @param key Key to search for
     * @return ConstIterator Iterator till the first element whose key is not less than key or end.
     */
    ConstIterator lowerBound( ConstLinkType x, ConstLinkType y, const KeyType& key );

    /**
     * @brief Returns an iterator to the first element whose key is greater than key according to comp or end, if that element does not exist.
     *
     * @param x Link to the node to search from
     * @param y Link to the node to search to
     * @param key Key to search for
     * @return Iterator Iterator till the first element whose key is greater than key according to comp or end.
     */
    Iterator upperBound( LinkType x, LinkType y, const KeyType& key );

    /**
     * @brief Returns an iterator to the first element whose key is greater than key according to comp or end, if that element does not exist.
     *
     * @param x Link to the node to search from
     * @param y Link to the node to search to
     * @param key Key to search for
     * @return ConstIterator Iterator till the first element whose key is greater than key according to comp or end.
     */
    ConstIterator upperBound( ConstLinkType x, ConstLinkType y, const KeyType& key );

    /**
     * @brief Perform a left rotation on the given node
     *
     * @param node Node to perform left rotation on
     * @param root Root of the tree
     */
    static void rotateLeft( BasePointer const node, BasePointer& root );

    /**
     * @brief Perform a right rotation on the given node
     *
     * @param node Node to perform right rotation on
     * @param root Root of the tree
     */
    static void rotateRight( BasePointer const node, BasePointer& root );

    /**
     * @brief Insert a value into the tree and balance the tree after insertion.
     *
     * @param insertLeft True to insert in the left subtree, false for the right subtree
     * @param node Node to insert value into subtree of
     * @param parent Parent of the node to isnert value into
     * @param header Header of the tree
     */
    static void insertAndRebalance( const bool insertLeft, BasePointer node, BasePointer parent, RBTreeNodeBase& header );

    /**
     * @brief Balance the tree
     *
     * @param node Node to balance
     * @param header Header of node to balance
     * @return BasePointer Pointer to the root of the balanced tree
     */
    static BasePointer rebalanceForErase( BasePointer const node, RBTreeNodeBase& header );

private:
    /**
     * @brief Reference for the comparison function
     *
     */
    Comparison mComparison;

    /**
     * @brief Header of the tree
     *
     */
    RBTreeNodeBase mHeader;

    /**
     * @brief Size of the tree
     *
     */
    SizeType mNodeCount;

    /**
     * @brief Function to allocate nodes
     *
     */
    NodeAllocator mNodeAllocator;
};

#include <internal/src/rbtree.inl>