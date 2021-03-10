#include <iostream>
#include <math.h>

using namespace std;

enum Direction 
{
    RIGHT = 1,
    LEFT = 0
};
typedef struct AVLNode
{
    int value = 0;
    int level = 0;
    int levels[2] = {0,0};
    int q = 0;
    struct AVLNode *father = nullptr;
    struct AVLNode *subtree[2] = {nullptr,nullptr};
}AVLNode;

class AVLTree
{
private:
    AVLNode *begin = nullptr;
    void simpleRotation(AVLNode *node,Direction dir);
    void doubleRotation(AVLNode *node,Direction dir);
    void rotation(AVLNode *node);
    void balance(AVLNode *node);
    Direction opposite(Direction dir);
public:
    AVLTree(){};
    ~AVLTree();
    bool add(int v);
    void remove(int v);
    bool has(int v) const;
    AVLNode *getBegin() const;
};