#pragma once

#include <memory>

template <typename K, typename M, typename C, typename V, typename A, typename S>
RBTree<K, M, C, V, A, S>::RBTree()
    : mNodeAllocator()
    , mHeader()
    , mComparison()
    , mNodeCount(0)
{
    initialize();
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
RBTree<K, M, C, V, A, S>::RBTree(const C& comparison, const A& allocator)
    : mNodeAllocator(allocator)
    , mHeader()
    , mComparison(comparison)
    , mNodeCount(0)
{
    initialize();
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
RBTree<K, M, C, V, A, S>::RBTree(const RBTree& other)
    : mNodeAllocator(other.mNodeAllocator)
    , mHeader()
    , mComparison(other.mComparison)
    , mNodeCount(0)
{
    if (other.root() != nullptr)
    {
        root() = copy(other.linkBegin(), other.linkEnd());
        leftmost() = minimum(root());
        rightmost() = maximum(root());
        mNodeCount = other.mNodeCount;
    }
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
RBTree<K, M, C, V, A, S>::RBTree(RBTree<K, M, C, V, A, S>&& other)
    : mNodeAllocator(other.mNodeAllocator)
    , mComparison(other.mComparison)
    , mNodeCount(0)
    , mHeader()
{
    if (other.root())
    {
        root() = other.root();
        leftmost() = other.leftmost();
        rightmost() = other.rightmost();
        root()->parent = linkEnd();

        other.root() = nullptr;
        other.leftmost() = other.linkEnd();
        other.rightmost() = other.linkEnd();

        mNodeCount = other.mNodeCount;
        other.mNodeCount = 0;
    }
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
RBTree<K, M, C, V, A, S>::RBTree(std::initializer_list<V> values)
    : mNodeAllocator()
    , mHeader()
    , mComparison()
    , mNodeCount(0)
{
    initialize();

    insertUnique(values.begin(), values.end());
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
template <typename InputIterator>
RBTree<K, M, C, V, A, S>::RBTree(InputIterator first, InputIterator last)
    : mNodeAllocator()
    , mHeader()
    , mComparison()
    , mNodeCount(0)
{
    insertUnique(first, last);
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
template <typename InputIterator>
RBTree<K, M, C, V, A, S>::RBTree(InputIterator first, InputIterator last, const C& comparison, const A& allocator)
    : mNodeAllocator(allocator)
    , mHeader()
    , mComparison(comparison)
    , mNodeCount(0)
{
    initialize();
    insertUnique(first, last);
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
RBTree<K, M, C, V, A, S>::~RBTree()
{
    erase(linkBegin());
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::NodeAllocator& RBTree<K, M, C, V, A, S>::getNodeAllocator()
{
    return *static_cast<NodeAllocator*>(&mNodeAllocator);
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
const typename RBTree<K, M, C, V, A, S>::NodeAllocator& RBTree<K, M, C, V, A, S>::getNodeAllocator() const
{
    return *static_cast<const NodeAllocator*>(&mNodeAllocator);
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::AllocatorType RBTree<K, M, C, V, A, S>::getAllocator() const
{
    return RBTree<K, M, C, V, A, S>::AllocatorType(getNodeAllocator());
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
RBTree<K, M, C, V, A, S>& RBTree<K, M, C, V, A, S>::operator =(const RBTree<K, M, C, V, A, S>& other)
{
    if (this != &other)
    {
        clear();
        mComparison = other.mComparison;

        if (other.root())
        {
            root() = copy(other.linkBegin(), other.linkEnd());
            leftmost() = minimum(root());
            rightmost() = maximum(root());
            mNodeCount = other.size();
        }
    }

    return *this;
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
RBTree<K, M, C, V, A, S>& RBTree<K, M, C, V, A, S>::operator =(RBTree<K, M, C, V, A, S>&& other)
{
    clear();
    swap(other);

    return *this;
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
RBTree<K, M, C, V, A, S>& RBTree<K, M, C, V, A, S>::operator =(std::initializer_list<V> values)
{
    clear();
    insert(values.begin(), values.end());

    return *this;
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::Iterator RBTree<K, M, C, V, A, S>::begin()
{
    return Iterator(static_cast<LinkType>(leftmost()));
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::ConstIterator RBTree<K, M, C, V, A, S>::begin() const
{
    return ConstIterator(static_cast<ConstLinkType>(leftmost()));
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::Iterator RBTree<K, M, C, V, A, S>::end()
{
    return Iterator(static_cast<LinkType>(&mHeader));
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::ConstIterator RBTree<K, M, C, V, A, S>::end() const
{
    return ConstIterator(static_cast<ConstLinkType>(&mHeader));
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::ReverseIterator RBTree<K, M, C, V, A, S>::rbegin()
{
    return ReverseIterator(end());
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::ConstReverseIterator RBTree<K, M, C, V, A, S>::rbegin() const
{
    return ConstReverseIterator(end());
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::ReverseIterator RBTree<K, M, C, V, A, S>::rend()
{
    return ReverseIterator(begin());
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::ConstReverseIterator RBTree<K, M, C, V, A, S>::rend() const
{
    return ConstReverseIterator(begin());
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::ConstIterator RBTree<K, M, C, V, A, S>::cbegin() const
{
    return begin();
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::ConstIterator RBTree<K, M, C, V, A, S>::cend() const
{
    return end();
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::ConstReverseIterator RBTree<K, M, C, V, A, S>::crbegin() const
{
    return rbegin();
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::ConstReverseIterator RBTree<K, M, C, V, A, S>::crend() const
{
    return rend();
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
bool RBTree<K, M, C, V, A, S>::empty() const
{
    return mNodeCount == 0;
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::SizeType RBTree<K, M, C, V, A, S>::size() const
{
    return mNodeCount;
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::SizeType RBTree<K, M, C, V, A, S>::maxSize() const
{
    return getNodeAllocator().max_size();
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
M& RBTree<K, M, C, V, A, S>::operator [](const K& key)
{
    Iterator result = lowerBound(key);

    if(result == end() || mComparison(key, (*result).first))
        result = insert(result, std::make_pair(key, M()));
    
    return (*result).second;
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
M& RBTree<K, M, C, V, A, S>::operator [](K&& key)
{
    Iterator result = lowerBound(key);

    if(result == end() || mComparison(key, (*result).first))
        result = insert(result, std::make_pair(std::move(key), M()));
    
    return (*result).second;
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
M& RBTree<K, M, C, V, A, S>::at(const K& key)
{
    Iterator result = lowerBound(key);

    if(result == end() || mComparison(key, (*result).first))
        throw std::out_of_range("RBTree::at");
    
    return (*result).second;
}

template <typename K, typename M, typename C, typename V, typename A, typename S>\
const M& RBTree<K, M, C, V, A, S>::at(const K& key) const
{
    ConstIterator result = lowerBound(key);

    if(result == end() || mComparison(key, (*result).first))
        throw std::out_of_range("RBTree::at");
    
    return (*result).second;
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
std::pair<typename RBTree<K, M, C, V, A, S>::Iterator, bool> RBTree<K, M, C, V, A, S>::insert(const V& value)
{
    return insertUnique(value);
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
void RBTree<K, M, C, V, A, S>::insert(std::initializer_list<V> values)
{
    insert(values.begin(), values.end());
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::Iterator RBTree<K, M, C, V, A, S>::insert(RBTree<K, M, C, V, A, S>::ConstIterator position, const V& value)
{
    return insertUnique(position, value);
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::Iterator RBTree<K, M, C, V, A, S>::erase(RBTree<K, M, C, V, A, S>::ConstIterator position)
{
    ConstIterator result = position;
    ++result;

    auxilliaryErase(position);
    
    return result.constCast();
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::SizeType RBTree<K, M, C, V, A, S>::erase(const K& key)
{
    std::pair<Iterator, Iterator> range = equalRange(key);
    const SizeType oldSize = size();

    erase(range.first, range.second);

    return oldSize - size();
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::Iterator RBTree<K, M, C, V, A, S>::erase(RBTree<K, M, C, V, A, S>::ConstIterator first, RBTree<K, M, C, V, A, S>::ConstIterator last)
{
    auxilliaryErase(first, last);
    return last.constCast();
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
void RBTree<K, M, C, V, A, S>::erase(const K& first, const K& last)
{
    while(first != last)
        erase(*first++);
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
void RBTree<K, M, C, V, A, S>::swap(RBTree<K, M, C, V, A, S>& other)
{
    if (root() == nullptr)
    {
        if (other.root())
        {
            root() = other.root();
            leftmost() = other.leftmost();
            rightmost() = other.rightmost();
            root()->parent = linkEnd();

            other.root() = nullptr;
            other.leftmost() = other.linkEnd();
            other.rightmost() = other.linkEnd();
        }
    } 
    else if (other.root() == nullptr)
    {
        other.root() = root();
        other.leftmost() = leftmost();
        other.rightmost() = rightmost();
        other.root()->parent = &other.linkEnd();

        root() = nullptr;
        leftmost() = linkEnd();
        rightmost() = linkEnd();
    }
    else
    {
        std::swap(root(), other.root());
        std::swap(leftmost(), other.leftmost());
        std::swap(rightmost(), other.rightmost());

        root()->parent = linkEnd();
        other.root()->parent = other.linkEnd();
    }

    std::swap(mNodeCount, other.mNodeCount);
    std::swap(mComparison, other.mComparison);
    std::swap(mNodeAllocator, other.mNodeAllocator);
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
void RBTree<K, M, C, V, A, S>::clear()
{
    erase(linkBegin());
    leftmost() = linkEnd();
    root() = nullptr;
    rightmost() = linkEnd();
    mNodeCount = 0;
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::Iterator RBTree<K, M, C, V, A, S>::find(const K& key)
{
    Iterator result = lowerBound(linkBegin(), linkEnd(), key);
    return (result == end() || mComparison(key, key(result.node))) ? end() : result;
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::ConstIterator RBTree<K, M, C, V, A, S>::find(const K& key) const
{
    ConstIterator result = lowerBound(linkBegin(), linkEnd(), key);
    return (result == end() || mComparison(key, key(result.node))) ? end() : result;
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::SizeType RBTree<K, M, C, V, A, S>::count(const K& key) const
{
    std::pair<ConstIterator, ConstIterator> range = equalRange(key);
    
    return SizeType(std::distance(range.first, range.second));
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::Iterator RBTree<K, M, C, V, A, S>::lowerBound(const K &key)
{
    return lowerBound(linkBegin(), linkEnd(), key);
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::ConstIterator RBTree<K, M, C, V, A, S>::lowerBound(const K &key) const
{
    return lowerBound(linkBegin(), linkEnd(), key);
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::Iterator RBTree<K, M, C, V, A, S>::upperBound(const K& key)
{
    return upperBound(linkBegin(), linkEnd(), key);
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::ConstIterator RBTree<K, M, C, V, A, S>::upperBound(const K& key) const
{
    return upperBound(linkBegin(), linkEnd(), key);
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
C RBTree<K, M, C, V, A, S>::compareKeys() const
{
    return mComparison;
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
std::pair<typename RBTree<K, M, C, V, A, S>::Iterator, typename RBTree<K, M, C, V, A, S>::Iterator> RBTree<K, M, C, V, A, S>::equalRange(const K& k)
{
    LinkType x = linkBegin();
    LinkType y = linkEnd();

    while(x)
    {
        if (mComparison(key(x), k))
            x = right(x);
        else if (mComparison(k, key(x)))
        {
            y = x;
            x = left(x);
        }
        else
        {
            LinkType a(x);
            LinkType b(y);

            y = x;
            x = left(x);

            a = right(a);

            return std::pair<Iterator, Iterator>(lowerBound(x, y, k), upperBound(a, b, k));
        }
    }

    return std::pair<Iterator, Iterator>(Iterator(y), Iterator(y));
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
std::pair<typename RBTree<K, M, C, V, A, S>::ConstIterator, typename RBTree<K, M, C, V, A, S>::ConstIterator> RBTree<K, M, C, V, A, S>::equalRange(const K& k) const
{
    ConstLinkType x = linkBegin();
    ConstLinkType y = linkEnd();

    while(x)
    {
        if (mComparison(key(x), k))
            x = right(x);
        else if (mComparison(k, key(x)))
        {
            y = x;
            x = left(x);
        }
        else
        {
            ConstLinkType a(x);
            ConstLinkType b(y);

            y = x;
            x = left(x);

            a = right(a);

            return std::pair<ConstIterator, ConstIterator>(lowerBound(x, y, k), upperBound(a, b, k));
        }
    }

    return std::pair<ConstIterator, ConstIterator>(ConstIterator(y), ConstIterator(y));
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::LinkType RBTree<K, M, C, V, A, S>::getNode()
{
    return mNodeAllocator.allocate(1);
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
void RBTree<K, M, C, V, A, S>::putNode(RBTree<K, M, C, V, A, S>::LinkType node)
{
    mNodeAllocator.deallocate(node, 1);
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
template <typename... Args>
typename RBTree<K, M, C, V, A, S>::LinkType RBTree<K, M, C, V, A, S>::createNode(Args&&... args)
{
    LinkType temp = getNode();

    try
    {
        std::construct_at(temp, std::forward<Args>(args)...);
    }
    catch(const std::exception& e)
    {
        putNode(temp);
        throw e;
    }
    
    return temp;
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
void RBTree<K, M, C, V, A, S>::destroyNode(RBTree<K, M, C, V, A, S>::LinkType node)
{
    std::destroy_at(node);
    putNode(node);
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::LinkType RBTree<K, M, C, V, A, S>::cloneNode(RBTree<K, M, C, V, A, S>::ConstLinkType node)
{
    LinkType temp = createNode(node->value);
    temp->color = node->color;
    temp->left = nullptr;
    temp->right = nullptr;

    return temp;
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::BasePointer& RBTree<K, M, C, V, A, S>::root()
{
    return mHeader.parent;
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::ConstBasePointer RBTree<K, M, C, V, A, S>::root() const
{
    return mHeader.parent;
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::BasePointer& RBTree<K, M, C, V, A, S>::leftmost()
{
    return mHeader.left;
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::ConstBasePointer RBTree<K, M, C, V, A, S>::leftmost() const
{
    return mHeader.left;
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::BasePointer& RBTree<K, M, C, V, A, S>::rightmost()
{
    return mHeader.right;
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::ConstBasePointer RBTree<K, M, C, V, A, S>::rightmost() const
{
    return mHeader.right;
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::LinkType RBTree<K, M, C, V, A, S>::linkBegin()
{
    return static_cast<LinkType>(mHeader.parent);
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::ConstLinkType RBTree<K, M, C, V, A, S>::linkBegin() const
{
    return static_cast<ConstLinkType>(mHeader.parent);
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::LinkType RBTree<K, M, C, V, A, S>::linkEnd()
{
    return static_cast<LinkType>(&mHeader);
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::ConstLinkType RBTree<K, M, C, V, A, S>::linkEnd() const
{
    return static_cast<ConstLinkType>(&mHeader);
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::ConstReference RBTree<K, M, C, V, A, S>::value(RBTree<K, M, C, V, A, S>::ConstLinkType node)
{
    return node->value;
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
const K& RBTree<K, M, C, V, A, S>::key(RBTree<K, M, C, V, A, S>::ConstLinkType node)
{
    //TODO: what to do if ValueType is not a pair?
    return S()(value(node));
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::LinkType RBTree<K, M, C, V, A, S>::left(RBTree<K, M, C, V, A, S>::BasePointer node)
{
    return static_cast<LinkType>(node->left);
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::ConstLinkType RBTree<K, M, C, V, A, S>::left(RBTree<K, M, C, V, A, S>::ConstBasePointer node)
{
    return static_cast<ConstLinkType>(node->left);
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::LinkType RBTree<K, M, C, V, A, S>::right(RBTree<K, M, C, V, A, S>::BasePointer node)
{
    return static_cast<LinkType>(node->right);
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::ConstLinkType RBTree<K, M, C, V, A, S>::right(RBTree<K, M, C, V, A, S>::ConstBasePointer node)
{
    return static_cast<ConstLinkType>(node->right);
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::ConstReference RBTree<K, M, C, V, A, S>::value(RBTree<K, M, C, V, A, S>::ConstBasePointer node)
{
    return static_cast<ConstLinkType>(node)->value;
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
const K& RBTree<K, M, C, V, A, S>::key(RBTree<K, M, C, V, A, S>::ConstBasePointer node)
{
    //TODO: what to do if ValueType is not a pair?
    return S()(value(node));
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::BasePointer RBTree<K, M, C, V, A, S>::minimum(RBTree<K, M, C, V, A, S>::BasePointer node)
{
    return RBTreeNodeBase::minimum(node);
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::ConstBasePointer RBTree<K, M, C, V, A, S>::minimum(RBTree<K, M, C, V, A, S>::ConstBasePointer node)
{
    return RBTreeNodeBase::minimum(node);
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::BasePointer RBTree<K, M, C, V, A, S>::maximum(RBTree<K, M, C, V, A, S>::BasePointer node)
{
    return RBTreeNodeBase::maximum(node);
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::ConstBasePointer RBTree<K, M, C, V, A, S>::maximum(RBTree<K, M, C, V, A, S>::ConstBasePointer node)
{
    return RBTreeNodeBase::maximum(node);
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
template <typename T>
std::pair<typename RBTree<K, M, C, V, A, S>::Iterator, bool> RBTree<K, M, C, V, A, S>::insertUnique(T&& value)
{
    LinkType x = linkBegin();
    LinkType y = linkEnd();

    bool comparison = true;

    while(x)
    {
        y = x;
        comparison = mComparison(S()(value), key(x));
        x = comparison ? left(x) : right(x);
    }

    Iterator j = Iterator(y);

    if(comparison)
    {
        if (j == begin())
            return std::pair<Iterator, bool>(insert(x, y, std::forward<T>(value)), true);
        else 
            --j;
    }

    if (mComparison(key(j.node), S()(value)))
        return std::pair<Iterator, bool>(insert(x, y, std::forward<T>(value)), true);

    return std::pair<Iterator, bool>(j, false);
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
template <typename T>
typename RBTree<K, M, C, V, A, S>::Iterator RBTree<K, M, C, V, A, S>::insertEqual(T&& value)
{
    LinkType x = linkBegin();
    LinkType y = linkEnd();

    while (x)
    {
        y = x;
        x = mComparison(s(value), key(x)) ? left(x) : right(x);
    }

    return insert(x, y, std::forward<T>(value));
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
template <typename T>
typename RBTree<K, M, C, V, A, S>::Iterator RBTree<K, M, C, V, A, S>::insertUnique(RBTree<K, M, C, V, A, S>::ConstIterator position, T&& value)
{
    if (position.node == linkEnd())
    {
        if (size() > 0 && mComparison(key(rightmost()), S()(value)))
            return insert(nullptr, rightmost(), std::forward<T>(value));
        else
            return insertUnique(std::forward<T>(value)).first;
    }
    else if (mComparison(S()(value), key(position.node)))
    {
        ConstIterator before = position;
        
        if (position.node == leftmost())
            return insert(leftmost(), leftmost(), std::forward<T>(value));
        else if (mComparison(key((--before).node), S()(value)))
        {
            if (right(before.node) == nullptr)
                return  insert(nullptr, before.node, std::forward<T>(value));
            else
                return insert(position.node, position.node, std::forward<T>(value));
        }
        else
            return insertUnique(std::forward<T>(value)).first;
    }
    else if (mComparison(key(position.node), S()(value)))
    {
        ConstIterator after = position;
        if (position.node == rightmost())
            return insert(nullptr, rightmost(), std::forward<T>(value));
        else if (mComparison(S()(value), key((++after).node)))
        {
            if (right(position.node) == nullptr)
                return insert(nullptr, position.node, std::forward<T>(value));
            else
                return insert(after.node, after.node, std::forward<T>(value));
        }
        else
            return insertUnique(std::forward<T>(value)).first;
    }
    
    return position.constCast();
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
template <typename T>
typename RBTree<K, M, C, V, A, S>::Iterator RBTree<K, M, C, V, A, S>::insertEqual(RBTree<K, M, C, V, A, S>::ConstIterator position, T&& value)
{
    if (position.node == linkEnd())
    {
        if (size() > 0 && !mComparison(KeyFromValue(value), key(rightmost())))
            return insert(nullptr, rightmost(), std::forward<T>(value));
        else
            return insertEqual(std::forward<T>(value)).first;
    }
    else if (mComparison(S()(value), key(position.node)))
    {
        ConstIterator before = position;
        
        if (position.node == leftmost())
            return insert(leftmost(), leftmost(), std::forward<T>(value));
        else if (!mComparison(S()(value), key(--before).node))
        {
            if (right(before.node) == nullptr)
                return  insert(nullptr, before.node, std::forward<T>(value));
            else
                return insert(position.node, position.node, std::forward<T>(value));
        }
        else
            return insertEqual(std::forward<T>(value));
    }
    else
    {
        ConstIterator after = position;
        if (position.node == rightmost())
            return insert(nullptr, rightmost(), std::forward<T>(value));
        else if (mComparison(S()(value), key(++after).node))
        {
            if (right(position.node) == nullptr)
                return insert(nullptr, position.node, std::forward<T>(value));
            else
                return insert(after.node, after.node, std::forward<T>(value));
        }
        else
            return insertEqualLower(std::forward<T>(value));
    }
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
template <typename InputIterator>
void RBTree<K, M, C, V, A, S>::insertUnique(InputIterator first, InputIterator last)
{
    for (; first != last; ++first)
        insertUnique(end(), *first);
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
template <typename InputIterator>
void RBTree<K, M, C, V, A, S>::insertEqual(InputIterator first, InputIterator last)
{
    for (; first != last; ++first)
        insertEqual(end(), *first);
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
void RBTree<K, M, C, V, A, S>::initialize()
{
    mHeader.color = RBTreeColor::Red;
    mHeader.parent = nullptr;
    mHeader.left = &mHeader;
    mHeader.right = &mHeader;
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
template <typename T>
typename RBTree<K, M, C, V, A, S>::Iterator RBTree<K, M, C, V, A, S>::insert(RBTree<K, M, C, V, A, S>::ConstBasePointer x, RBTree<K, M, C, V, A, S>::ConstBasePointer y, T&& value)
{
    bool insertLeft = (x || y == linkEnd() || mComparison(S()(value), key(y)));
    LinkType z = createNode(std::forward<T>(value));

    insertAndRebalance(insertLeft, z, const_cast<BasePointer>(y), mHeader);
    mNodeCount++;

    return Iterator(z);
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
template <typename T>
typename RBTree<K, M, C, V, A, S>::Iterator RBTree<K, M, C, V, A, S>::insertLower(RBTree<K, M, C, V, A, S>::BasePointer x, RBTree<K, M, C, V, A, S>::BasePointer y, T&& value)
{
    bool insertLeft = (x || y = linkEnd() || mCompare(S()(value), key(y)));
    LinkType z = createNode(std::forward<T>(value));

    insertAndRebalance(insertLeft, z, y, mHeader);
    mNodeCount++;

    return Iterator(z);
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
template <typename T>
typename RBTree<K, M, C, V, A, S>::Iterator RBTree<K, M, C, V, A, S>::insertEqualLower(T&& value)
{
    LinkType x = linkBegin();
    LinkType y = linkEnd();

    while(x)
    {
        y = x;
        x = mComparison(key(x), S()(value)) ? left(x) : right(x);
    }

    return insertLower(x, y, std::forward<T>(value));
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::LinkType RBTree<K, M, C, V, A, S>::copy(RBTree<K, M, C, V, A, S>::ConstLinkType x, RBTree<K, M, C, V, A, S>::LinkType y)
{
    LinkType top = cloneNode(x);
    top->parent = y;

    try
    {
        if(x->right)
            top->right = copy(right(x), top);
        y = top;
        x = left(x);

        while(x)
        {
            LinkType node = cloneNode(x);
            y->left = node;
            node->parent = y;

            if(x->right)
                node->right = copy(right(x), node);
            y = node;
            x = left(x);
        }
    }
    catch(const std::exception& e)
    {
        erase(top);
        throw e;
    }
    
    return top;
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
void RBTree<K, M, C, V, A, S>::erase(RBTree<K, M, C, V, A, S>::LinkType link)
{
    while(link)
    {
        erase(right(link));
        LinkType y = left(link);
        destroyNode(link);
        link = y;
    }
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
void RBTree<K, M, C, V, A, S>::auxilliaryErase(RBTree<K, M, C, V, A, S>::ConstIterator position)
{
    LinkType y = static_cast<LinkType>(rebalanceForErase(const_cast<BasePointer>(position.node), mHeader));
    destroyNode(y);

    mNodeCount--;
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
void RBTree<K, M, C, V, A, S>::auxilliaryErase(RBTree<K, M, C, V, A, S>::ConstIterator first, RBTree<K, M, C, V, A, S>::ConstIterator last)
{
    if (first == begin() && last == end())
        clear();
    else
        while (first != last)
            erase(first++);
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::Iterator RBTree<K, M, C, V, A, S>::lowerBound(RBTree<K, M, C, V, A, S>::LinkType x, RBTree<K, M, C, V, A, S>::LinkType y, const K& k)
{
    while (x)
    {
        if (mComparison(k, key(x)))
            x = right(x);
        else
        {
            y = x;
            x = left(x);
        }
    }

    return Iterator(y);
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::ConstIterator RBTree<K, M, C, V, A, S>::lowerBound(RBTree<K, M, C, V, A, S>::ConstLinkType x, RBTree<K, M, C, V, A, S>::ConstLinkType y, const K& k)
{
    while (x)
    {
        if (mComparison(k, key(x)))
            x = right(x);
        else
        {
            y = x;
            x = left(x);
        }
    }

    return ConstIterator(y);
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::Iterator RBTree<K, M, C, V, A, S>::upperBound(RBTree<K, M, C, V, A, S>::LinkType x, RBTree<K, M, C, V, A, S>::LinkType y, const K& k)
{
    while (x)
    {
        if (mComparison(k, key(x)))
        {
            y = x;
            x = left(x);
        }
        else
            x = right(x);
    }

    return Iterator(y);
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::ConstIterator RBTree<K, M, C, V, A, S>::upperBound(RBTree<K, M, C, V, A, S>::ConstLinkType x, RBTree<K, M, C, V, A, S>::ConstLinkType y, const K& k)
{
    while (x)
    {
        if (mComparison(k, key(x)))
        {
            y = x;
            x = left(x);
        }
        else
            x = right(x);
    }

    return ConstIterator(y);
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
void RBTree<K, M, C, V, A, S>::rotateLeft(RBTree<K, M, C, V, A, S>::BasePointer const node, RBTree<K, M, C, V, A, S>::BasePointer& treeRoot)
{
    BasePointer const right = node->right;

    node->right = right->left;
    if (right->left)
        right->left->parent = node;
    right->parent = node->parent;

    if(node == treeRoot)
        treeRoot = right;
    else if(node == node->parent->left)
        node->parent->left = right;
    else
        node->parent->right = right;

    right->left = node;
    node->parent = right;
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
void RBTree<K, M, C, V, A, S>::rotateRight(RBTree<K, M, C, V, A, S>::BasePointer const node, RBTree<K, M, C, V, A, S>::BasePointer& treeRoot)
{
    BasePointer const left = node->left;

    node->left = left->right;
    if (left->right)
        left->right->parent = node;
    left->parent = node->parent;

    if(node == treeRoot)
        treeRoot = left;
    else if(node == node->parent->right)
        node->parent->right = left;
    else
        node->parent->left = left;

    left->right = node;
    node->parent = left;
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
void RBTree<K, M, C, V, A, S>::insertAndRebalance(const bool insertLeft, RBTree<K, M, C, V, A, S>::BasePointer node, RBTree<K, M, C, V, A, S>::BasePointer parent, RBTreeNodeBase& header)
{
    BasePointer& treeRoot = header.parent;

    node->parent = parent;
    node->left = nullptr;
    node->right = nullptr;
    node->color = RBTreeColor::Red;

    if(insertLeft)
    {
        parent->left = node;

        if (parent == &header)
        {
            header.parent = node;
            header.right = node;
        }
        else if (parent == header.left)
        {
            header.left = node;
        }
    }
    else
    {
        parent->right = node;

        if(parent == header.right)
            header.right = node;
    }

    while (node != treeRoot && node->parent->color == RBTreeColor::Red)
    {
        BasePointer const nodeGrandParent = node->parent->parent;

        if(node->parent == nodeGrandParent->left)
        {
            BasePointer const right = nodeGrandParent->right;
            if(right && right->color == RBTreeColor::Red)
            {
                node->parent->color = RBTreeColor::Black;
                right->color = RBTreeColor::Black;
                nodeGrandParent->color = RBTreeColor::Red;
                node = nodeGrandParent;
            }
            else
            {
                if(node == node->parent->right)
                {
                    node = node->parent;
                    rotateLeft(node, treeRoot);
                }

                node->parent->color = RBTreeColor::Black;
                nodeGrandParent->color = RBTreeColor::Red;
                rotateRight(nodeGrandParent, treeRoot);
            }
        }
        else
        {
            BasePointer const left = nodeGrandParent->left;
            if(left && left->color == RBTreeColor::Red)
            {
                node->parent->color = RBTreeColor::Black;
                left->color = RBTreeColor::Black;
                nodeGrandParent->color = RBTreeColor::Red;
                node = nodeGrandParent;
            }
            else
            {
                if(node == node->parent->left)
                {
                    node = node->parent;
                    rotateRight(node, treeRoot);
                }

                node->parent->color = RBTreeColor::Black;
                nodeGrandParent->color = RBTreeColor::Red;
                rotateLeft(nodeGrandParent, treeRoot);
            }
        }
    }

    treeRoot->color = RBTreeColor::Black;
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
typename RBTree<K, M, C, V, A, S>::BasePointer RBTree<K, M, C, V, A, S>::rebalanceForErase(RBTree<K, M, C, V, A, S>::BasePointer const target, RBTreeNodeBase& header)
{
    BasePointer& treeRoot = header.parent;
    BasePointer& treeLeftmost = header.left;
    BasePointer& treeRightmost = header.right;

    BasePointer result = target;
    BasePointer node = nullptr;
    BasePointer nodeParent = nullptr;

    if(result->left == nullptr)
        node = result->right;
    else
    {
        if (node->right == nullptr)
            node = result->left;
        else
        {
            result = result->right;
            while (node->left != nullptr)
                result = result->left;
            node = result->right;
        }
    }

    if(result != target)
    {
        target->left->parent = result;
        result->left = target->left;

        if(result != target->right)
        {
            nodeParent = result->parent;
            if(node)
                node->parent = result->parent;
            result->parent->left = node;

            result->right = target->right;
            target->right->parent = result;
        }
        else
        {
            nodeParent = result;
        }

        if (treeRoot == target)
            treeRoot = result;
        else if (target->parent->left == target)
            target->parent->left = result;
        else
            target->parent->right = result;

        result->parent = target->parent;
        std::swap(result->color, target->color);
        result = target;
    }
    else
    {
        nodeParent = result->parent;
        if(node)
            node->parent = result->parent;
        
        if(treeRoot == target)
            treeRoot = node;
        else
        {
            if(target->parent->left == target)
                target->parent->left = node;
            else
                target->parent->right = node;
        }

        if(treeLeftmost == target)
        {
            if(target->right == nullptr)
                treeLeftmost = target->parent;
            else
                treeLeftmost = minimum(node);
        }

        if (treeRightmost == target)
        {
            if(target->left == nullptr)
                treeRightmost = target->parent;
            else
                treeRightmost = maximum(node);
        }
    }

    if(result->color == RBTreeColor::Black)
    {
        while (node != treeRoot && (node == nullptr || node->color == RBTreeColor::Black))
        {
            if(node == nodeParent->left)
            {
                BasePointer right = nodeParent->right;
                if(right && right->color == RBTreeColor::Red)
                {
                    right->color = RBTreeColor::Black;
                    nodeParent->color = RBTreeColor::Red;
                    rotateLeft(nodeParent, treeRoot);
                    right = nodeParent->right;
                }

                if((right->left == nullptr || right->left->color == RBTreeColor::Black) && (right->right == nullptr || right->right->color == RBTreeColor::Black))
                {
                    right->color = RBTreeColor::Red;
                    node = nodeParent;
                    nodeParent = nodeParent->parent;
                }
                else
                {
                    if(right->right == nullptr || right->right->color == RBTreeColor::Black)
                    {
                        if(right->left)
                            right->left->color = RBTreeColor::Black;
                        right->color = RBTreeColor::Red;
                        rotateRight(right, treeRoot);
                        right = nodeParent->right;
                    }

                    right->color = nodeParent->color;
                    nodeParent->color = RBTreeColor::Black;

                    if(right->right)
                        right->right->color = RBTreeColor::Black;
                    
                    rotateLeft(nodeParent, treeRoot);
                    break;
                }
            }
            else
            {
                BasePointer left = nodeParent->left;
                if(left && left->color == RBTreeColor::Red)
                {
                    left->color = RBTreeColor::Black;
                    nodeParent->color = RBTreeColor::Red;
                    rotateRight(nodeParent, treeRoot);
                    left = nodeParent->left;
                }

                if((left->left == nullptr || left->left->color == RBTreeColor::Black) && (left->right == nullptr || left->right->color == RBTreeColor::Black))
                {
                    left->color = RBTreeColor::Red;
                    node = nodeParent;
                    nodeParent = nodeParent->parent;
                }
                else
                {
                    if(left->left == nullptr || left->left->color == RBTreeColor::Black)
                    {
                        if(left->right)
                            left->right->color = RBTreeColor::Black;
                        left->color = RBTreeColor::Red;
                        rotateLeft(left, treeRoot);
                        left = nodeParent->left;
                    }

                    left->color = nodeParent->color;
                    nodeParent->color = RBTreeColor::Black;

                    if(left->left)
                        left->left->color = RBTreeColor::Black;
                    
                    rotateRight(nodeParent, treeRoot);
                    break;
                }
            }
        }
        
        if (node)
            node->color = RBTreeColor::Black;
    }

    return result;
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
bool operator ==(const RBTree<K, M, C, V, A, S>& a, const RBTree<K, M, C, V, A, S>& b)
{
    return a.size() == b.size() && std::equal(a.begin(), a.end(), b.begin());
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
bool operator <(const RBTree<K, M, C, V, A, S>& a, RBTree<K, M, C, V, A, S>& b)
{
    return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
}

template <typename K, typename M, typename C, typename V, typename A, typename S>
bool operator !=(const RBTree<K, M, C, V, A, S>& a, RBTree<K, M, C, V, A, S>& b)
{
    return !(a == b);
} 

template <typename K, typename M, typename C, typename V, typename A, typename S>
bool operator >(const RBTree<K, M, C, V, A, S>& a, RBTree<K, M, C, V, A, S>& b)
{
    return b < a;
} 

template <typename K, typename M, typename C, typename V, typename A, typename S>
bool operator <=(const RBTree<K, M, C, V, A, S>& a, RBTree<K, M, C, V, A, S>& b)
{
    return !(b < a);
} 

template <typename K, typename M, typename C, typename V, typename A, typename S>
bool operator >=(const RBTree<K, M, C, V, A, S>& a, RBTree<K, M, C, V, A, S>& b)
{
    return !(a < b);
} 

template <typename K, typename M, typename C, typename V, typename A, typename S>
void swap(RBTree<K, M, C, V, A, S>& a, RBTree<K, M, C, V, A, S>& b)
{
    a.swap(b);
} 