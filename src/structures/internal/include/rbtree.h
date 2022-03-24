#pragma once

#include <memory>

#include <internal/include/rbtreecolor.h>
#include <internal/include/rbtreenodebase.h>
#include <internal/include/rbtreenode.h>
#include <internal/include/rbtreeiterator.h>
#include <internal/include/rbtreeconstiterator.h>
#include <internal/include/rbtreeutils.h>

//TODO: Add concepts for each type here
template <typename KeyType, typename MappedType, typename Comparison = std::less<KeyType>, typename ValueType = std::pair<const KeyType, MappedType>, typename Allocator = std::allocator<ValueType>, typename KeySelector = Select1<ValueType>>
class RBTree
{
private:
    typedef typename std::allocator_traits<Allocator>::template rebind_alloc<RBTreeNode<ValueType>>  NodeAllocator;

protected:
    typedef RBTreeNodeBase*                 BasePointer;
    typedef const RBTreeNodeBase*           ConstBasePointer;

public:
    typedef ValueType*                      Pointer;
    typedef const ValueType*                ConstPointer;
    typedef ValueType&                      Reference;
    typedef const ValueType&                ConstReference;

    typedef RBTreeNode<ValueType>*          LinkType;
    typedef const RBTreeNode<ValueType>*    ConstLinkType;

    typedef std::size_t                     SizeType;
    typedef Allocator                       AllocatorType;

    typedef RBTreeIterator<ValueType>       Iterator;
    typedef RBTreeConstIterator<ValueType>  ConstIterator;
    typedef RBTreeIterator<ValueType>       ReverseIterator; //TODO: Fix reverse iterator types
    typedef RBTreeConstIterator<ValueType>  ConstReverseIterator;

public:
                                            RBTree(); 
    explicit                                RBTree(const Comparison& comparison, const AllocatorType& allocator = AllocatorType()); 
                                            RBTree(const RBTree& other);
                                            RBTree(RBTree&& other);
                                            RBTree(std::initializer_list<ValueType> values);
    template <typename InputIterator> //TOOD: Add concept
                                            RBTree(InputIterator first, InputIterator last);
    template <typename InputIterator> //Todo: Add concept
                                            RBTree(InputIterator first, InputIterator last, const Comparison& comparison, const AllocatorType& allocator = AllocatorType());

                                            ~RBTree();

    NodeAllocator&                          getNodeAllocator(); 
    const NodeAllocator&                    getNodeAllocator() const; 

    AllocatorType                           getAllocator() const; 

    RBTree&                                 operator =(const RBTree& other);
    RBTree&                                 operator =(RBTree&& other);
    RBTree&                                 operator =(std::initializer_list<ValueType> values);

    Iterator                                begin();
    ConstIterator                           begin() const;

    Iterator                                end();
    ConstIterator                           end() const;

    ReverseIterator                         rbegin();
    ConstReverseIterator                    rbegin() const;

    ReverseIterator                         rend();
    ConstReverseIterator                    rend() const;

    ConstIterator                           cbegin() const;
    ConstIterator                           cend() const;

    ConstReverseIterator                    crbegin() const;
    ConstReverseIterator                    crend() const;

    bool                                    empty() const;

    SizeType                                size() const;
    SizeType                                maxSize() const;

    MappedType&                             operator [](const KeyType& key);
    MappedType&                             operator [](KeyType&& key);
    MappedType&                             at(const KeyType& key);
    const MappedType&                       at(const KeyType& key) const;

    std::pair<Iterator, bool>               insert(const ValueType& value);
    void                                    insert(std::initializer_list<ValueType> values);
    Iterator                                insert(ConstIterator position, const ValueType& value);
    
    Iterator                                erase(ConstIterator position);
    SizeType                                erase(const KeyType& key);
    Iterator                                erase(ConstIterator first, ConstIterator last);
    void                                    erase(const KeyType& first, const KeyType& last);

    void                                    swap(RBTree& tree);

    void                                    clear();

    Comparison                              compareKeys() const;
    //TODO: Look into adding a value comparison mechanism that uses KeyFromValue to determine order

    Iterator                                find(const KeyType& key);
    ConstIterator                           find(const KeyType& key) const;

    SizeType                                count(const KeyType& key) const;
    
    Iterator                                lowerBound(const KeyType& key);                     
    ConstIterator                           lowerBound(const KeyType& key) const;

    Iterator                                upperBound(const KeyType& key);
    ConstIterator                           upperBound(const KeyType& key) const;
    
    std::pair<Iterator, Iterator>           equalRange(const KeyType& key);
    std::pair<ConstIterator, ConstIterator> equalRange(const KeyType& key) const;

protected:
    LinkType                                getNode(); 
    void                                    putNode(LinkType node); 
    
    template<typename ...Args>
    LinkType                                createNode(Args&&... args); 
    void                                    destroyNode(LinkType node); 
    LinkType                                cloneNode(ConstLinkType node); 

    BasePointer&                            root();
    ConstBasePointer                        root() const;

    BasePointer&                            leftmost();
    ConstBasePointer                        leftmost() const;

    BasePointer&                            rightmost();
    ConstBasePointer                        rightmost() const;

    LinkType                                linkBegin();
    ConstLinkType                           linkBegin() const;

    LinkType                                linkEnd();
    ConstLinkType                           linkEnd() const;

    static ConstReference                   value(ConstLinkType node);
    static const KeyType&                   key(ConstLinkType node);

    static LinkType                         left(BasePointer node);
    static ConstLinkType                    left(ConstBasePointer node);

    static LinkType                         right(BasePointer node);
    static ConstLinkType                    right(ConstBasePointer node);

    static ConstReference                   value(ConstBasePointer node);
    static const KeyType&                   key(ConstBasePointer node);

    static BasePointer                      minimum(BasePointer node);
    static ConstBasePointer                 minimum(ConstBasePointer node);

    static BasePointer                      maximum(BasePointer node);
    static ConstBasePointer                 maximum(ConstBasePointer node);

    template <typename T>
    std::pair<Iterator, bool>               insertUnique(T&& value);
    template <typename T>
    Iterator                                insertUnique(ConstIterator position, T&& value);
    template <typename InputIterator> //TODO: add concept for input iterator
    void                                    insertUnique(InputIterator first, InputIterator last);
    
    template <typename T>
    Iterator                                insertEqual(T&& value);
    template <typename T>
    Iterator                                insertEqual(ConstIterator position, T&& value);
    template <typename InputIterator> //TODO: add concept for input iterator
    void                                    insertEqual(InputIterator first, InputIterator last);

private:
    void                                    initialize(); 

    template<typename T>
    Iterator                                insert(ConstBasePointer x, ConstBasePointer y, T&& value);

    template <typename T>
    Iterator                                insertLower(BasePointer x, BasePointer y, T&& value);

    template <typename T>
    Iterator                                insertEqualLower(T&& value);

    LinkType                                copy(ConstLinkType x, LinkType y);

    void                                    erase(LinkType x);
    void                                    auxilliaryErase(ConstIterator position);
    void                                    auxilliaryErase(ConstIterator first, ConstIterator last);

    Iterator                                lowerBound(LinkType x, LinkType y, const KeyType& key);         
    ConstIterator                           lowerBound(ConstLinkType x, ConstLinkType y, const KeyType& key);

    Iterator                                upperBound(LinkType x, LinkType y, const KeyType& key);
    ConstIterator                           upperBound(ConstLinkType x, ConstLinkType y, const KeyType& key);

    static void                             rotateLeft(BasePointer const node, BasePointer& root);
    static void                             rotateRight(BasePointer const node, BasePointer& root);

    static void                             insertAndRebalance(const bool insertLeft, BasePointer node, BasePointer parent, RBTreeNodeBase& header);
    static BasePointer                      rebalanceForErase(BasePointer const node, RBTreeNodeBase& header);

private:
    Comparison                              mComparison;
    RBTreeNodeBase                          mHeader;
    SizeType                                mNodeCount;
    NodeAllocator                           mNodeAllocator;
};

#include <internal/src/rbtree.inl>