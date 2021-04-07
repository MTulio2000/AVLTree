# AVLTree
Binary search using AVL tree

In this first version, we are using recursive function to balance the tree and without removal option, but in a few days, I'll upload the new solution with a good code.

To use this code you have to create a new AVLTree object, see below:

``` C++
AVLTree *tree = new AVLTree();
```

Adding/removing a new element is very easy, you can do it like this:

``` C++
tree->add(/*Number*/ 10);
tree->remove(/*Number*/ 10);
```

### For the future

> I'll try to develop the balance function without recursion
