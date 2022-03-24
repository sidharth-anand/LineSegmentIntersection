#include <gtest/gtest.h>

#include <structures/rbtree.h>


TEST(RBTree, DefaultConstructor)
{
    RBTree<int, int> tree;
    EXPECT_EQ(tree.size(), 0);
}

TEST(RBTree, ComparatorAllocatorConstructor)
{
    RBTree<int, int, std::less<int>, std::pair<int, int>, std::allocator<int>> tree;
    EXPECT_EQ(tree.size(), 0);
}

TEST(RBTree, OtherRBTreeConstructor)
{
    RBTree<int, int> tree1;
    RBTree<int, int> tree2(tree1);
    EXPECT_EQ(tree2.size(), 0);
}

TEST(RBTree, CopyConstructor)
{
    RBTree<int, int> tree1;
    tree1.insert(std::make_pair(1, 1));
    RBTree<int, int> tree2(tree1);
    EXPECT_EQ(tree2.size(), 1);
}

TEST(RBTree, IntializerListConstructor)
{
    RBTree<int, int> tree{{1, 1}, {2, 2}, {3, 3}};
    EXPECT_EQ(tree.size(), 3);
}

TEST(RBTree, InputIteratorConstructor)
{
    RBTree<int, int> tree1{{1, 1}, {2, 2}, {3, 3}};
    RBTree<int, int> tree2(tree1.begin(), tree1.end());
    EXPECT_EQ(tree2.size(), 3);
}

TEST(RBTree, InputIteratorComparatorAllocatorConstructor)
{
    RBTree<int, int> tree1{{1, 1}, {2, 2}, {3, 3}};
    RBTree<int, int, std::less<int>, std::pair<int, int>, std::allocator<int>> tree2(tree1.begin(), tree1.end());
    EXPECT_EQ(tree2.size(), 3);
}

TEST(RBTree, MoveConstructor)
{
    RBTree<int, int> tree1;
    tree1.insert(std::make_pair(1, 1));
    RBTree<int, int> tree2(std::move(tree1));
    EXPECT_EQ(tree2.size(), 1);
}

TEST(RBTree, AssignmentOperator)
{
    RBTree<int, int> tree1;
    tree1.insert(std::make_pair(1, 1));
    RBTree<int, int> tree2;
    tree2 = tree1;
    EXPECT_EQ(tree2.size(), 1);
}

TEST(RBTree, MoveAssignmentOperator)
{
    RBTree<int, int> tree1;
    tree1.insert(std::make_pair(1, 1));
    RBTree<int, int> tree2;
    tree2 = std::move(tree1);
    EXPECT_EQ(tree2.size(), 1);
}

TEST(RBTree, CopyAssignmentOperator)
{
    RBTree<int, int> tree1;
    tree1.insert(std::make_pair(1, 1));
    RBTree<int, int> tree2;
    tree2 = tree1;
    EXPECT_EQ(tree2.size(), 1);
}

TEST(RBTree, MappedTypeOperator)
{
    RBTree<int, int> tree;
    tree.insert(std::make_pair(1, 1));
    tree.insert(std::make_pair(2, 2));
    tree.insert(std::make_pair(3, 3));
    EXPECT_EQ(tree[1], 1);
    EXPECT_EQ(tree[2], 2);
    EXPECT_EQ(tree[3], 3);
}

TEST(RBTree, MappedTypeOperatorTemporaryReference)
{
    RBTree<int, int> tree;
    tree.insert(std::make_pair(1, 1));
    tree.insert(std::make_pair(2, 2));
    tree.insert(std::make_pair(3, 3));
    int x1 = 1;
    int x2 = 2;
    int x3 = 3;
    EXPECT_EQ(tree[x1], 1);
    EXPECT_EQ(tree[x2], 2);
    EXPECT_EQ(tree[x3], 3);
}

TEST(RBTree, AtConst)
{
    RBTree<int, int> tree;
    tree.insert(std::make_pair(1, 1));
    tree.insert(std::make_pair(2, 2));
    tree.insert(std::make_pair(3, 3));
    EXPECT_EQ(tree.at(1), 1);
    EXPECT_EQ(tree.at(2), 2);
    EXPECT_EQ(tree.at(3), 3);
}

TEST(RBTree, AtNonConst)
{
    RBTree<int, int> tree;
    tree.insert(std::make_pair(1, 1));
    tree.insert(std::make_pair(2, 2));
    tree.insert(std::make_pair(3, 3));
    int x1 = 1;
    int x2 = 2;
    int x3 = 3;
    EXPECT_EQ(tree.at(x1), 1);
    EXPECT_EQ(tree.at(x2), 2);
    EXPECT_EQ(tree.at(x3), 3);
}


TEST(RBTree, InsertValueType)
{
    RBTree<int, int> tree;
    tree.insert(std::make_pair(1, 1));
    EXPECT_EQ(tree.size(), 1);
}

TEST(RBTree, InsertInitializerList)
{
    RBTree<int, int> tree;
    tree.insert({std::make_pair(1, 1), std::make_pair(2, 2), std::make_pair(3, 3)});
    EXPECT_EQ(tree.size(), 3);
}

TEST(RBTree, InsertIterator)
{
    RBTree<int, int> tree1;
    tree1.insert({std::make_pair(1, 1), std::make_pair(2, 2), std::make_pair(3, 3)});
    RBTree<int, int> tree2(tree1.begin(), tree1.end());
    EXPECT_EQ(tree2.size(), 3);
}

TEST(RBTree, EraseIteratorPosition)
{
    RBTree<int, int> tree;
    tree.insert({std::make_pair(1, 1), std::make_pair(2, 2), std::make_pair(3, 3)});
    tree.erase(tree.begin());
    EXPECT_EQ(tree.size(), 2);
}

TEST(RBTree, EraseIteratorRange)
{
    RBTree<int, int> tree;
    tree.insert({std::make_pair(1, 1), std::make_pair(2, 2), std::make_pair(3, 3)});
    tree.erase(tree.begin(), tree.end());
    EXPECT_EQ(tree.size(), 0);
}

TEST(RBTree, EraseKeyType)
{
    RBTree<int, int> tree;
    tree.insert({std::make_pair(1, 1), std::make_pair(2, 2), std::make_pair(3, 3)});
    tree.erase(1);
    EXPECT_EQ(tree.size(), 2);
}

TEST(RBTree, Clear)
{
    RBTree<int, int> tree;
    tree.insert({std::make_pair(1, 1), std::make_pair(2, 2), std::make_pair(3, 3)});
    tree.clear();
    EXPECT_EQ(tree.size(), 0);
}

TEST(RBTree, Swap)
{
    RBTree<int, int> tree1;
    tree1.insert({std::make_pair(1, 1), std::make_pair(2, 2)});
    RBTree<int, int> tree2;
    tree2.insert({std::make_pair(3, 3), std::make_pair(4, 4), std::make_pair(5, 5)});
    tree1.swap(tree2);
    EXPECT_EQ(tree1.size(), 3);
    EXPECT_EQ(tree2.size(), 2);
}

TEST(RBTree, FindAndReturnIterator)
{
    RBTree<int, int> tree;
    tree.insert({std::make_pair(1, 1), std::make_pair(2, 2), std::make_pair(3, 3)});
    RBTree<int, int>::Iterator it = tree.find(2);
    EXPECT_EQ(it->first, 2);
    EXPECT_EQ(it->second, 2);
}

TEST(RBTree, FindAndReturnConstIterator)
{
    RBTree<int, int> tree;
    tree.insert({std::make_pair(1, 1), std::make_pair(2, 2), std::make_pair(3, 3)});
    RBTree<int, int>::ConstIterator it = tree.find(2);
    EXPECT_EQ(it->first, 2);
    EXPECT_EQ(it->second, 2);
}

TEST(RBTree, Count)
{
    RBTree<int, int> tree;
    tree.insert({std::make_pair(1, 1), std::make_pair(2, 2), std::make_pair(3, 3)});
    EXPECT_EQ(tree.count(2), 1);
}

TEST(RBTree, LowerBoundIterator)
{
    RBTree<int, int> tree;
    tree.insert({std::make_pair(1, 1), std::make_pair(2, 2), std::make_pair(3, 3)});
    RBTree<int, int>::Iterator it = tree.lowerBound(2);
    EXPECT_EQ(it->first, 2);
    EXPECT_EQ(it->second, 2);
}

TEST(RBTree, LowerBoundConstIterator)
{
    RBTree<int, int> tree;
    tree.insert({std::make_pair(1, 1), std::make_pair(2, 2), std::make_pair(3, 3)});
    RBTree<int, int>::ConstIterator it = tree.lowerBound(2);
    EXPECT_EQ(it->first, 2);
    EXPECT_EQ(it->second, 2);
}

TEST(RBTree, UpperBoundIterator)
{
    RBTree<int, int> tree;
    tree.insert({std::make_pair(1, 1), std::make_pair(2, 2), std::make_pair(3, 3)});
    RBTree<int, int>::Iterator it = tree.upperBound(2);
    EXPECT_EQ(it->first, 3);
    EXPECT_EQ(it->second, 3);
}

TEST(RBTree, UpperBoundConstIterator)
{
    RBTree<int, int> tree;
    tree.insert({std::make_pair(1, 1), std::make_pair(2, 2), std::make_pair(3, 3)});
    RBTree<int, int>::ConstIterator it = tree.upperBound(2);
    EXPECT_EQ(it->first, 3);
    EXPECT_EQ(it->second, 3);
}

TEST(RBTree, EqualRangeIterator)
{
    RBTree<int, int> tree;
    tree.insert({std::make_pair(1, 1), std::make_pair(2, 2), std::make_pair(3, 3)});
    std::pair<RBTree<int, int>::Iterator, RBTree<int, int>::Iterator> range = tree.equalRange(2);
    EXPECT_EQ(range.first->first, 2);
    EXPECT_EQ(range.first->second, 2);
    EXPECT_EQ(range.second->first, 3);
    EXPECT_EQ(range.second->second, 3);
}

TEST(RBTree, EqualRangeConstIterator)
{
    RBTree<int, int> tree;
    tree.insert({std::make_pair(1, 1), std::make_pair(2, 2), std::make_pair(3, 3)});
    std::pair<RBTree<int, int>::ConstIterator, RBTree<int, int>::ConstIterator> range = tree.equalRange(2);
    EXPECT_EQ(range.first->first, 2);
    EXPECT_EQ(range.first->second, 2);
    EXPECT_EQ(range.second->first, 3);
    EXPECT_EQ(range.second->second, 3);
}
