#include <iostream>
#include <string>

#include "rbtree.h"

int main()
{
    RBTree<int, std::string> tree = {{1, "asd"}, {3, "qwe"}, {2, "zxc"}};
    tree.insert({0, "g"});
    tree[-1] = "x";
    tree.insert(std::make_pair<int, std::string>(4, "y"));

    for(auto node : tree)
        std::cout << node.first << " " << node.second << "\n";

    std::cout << "\n";
    std::cout << tree[3]  << "\n";

    tree[1] = "ert";
    std::cout << tree[1] << "\n";

    return 0;
}

