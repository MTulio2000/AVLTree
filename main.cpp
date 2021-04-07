#include "avl.h"
using namespace std;

void print(AVLNode *node) {
    if(!node)return;
    print(node->subtree[LEFT]);
    cout << "--------------------------------"<< endl;
    cout << "Node Value: "  << node->value    << endl;
    if(node->father)
        cout << "- Origem: "  << node->father->value   << endl;
    if (node->subtree[LEFT] != NULL)
        cout << "- Left: "  << node->subtree[LEFT]->value << endl;
    if (node->subtree[RIGHT] != NULL)
        cout << "- Right: " << node->subtree[RIGHT]->value<< endl;
    cout << "--------------------------------"<< endl;
    print(node->subtree[RIGHT]);
}

int main()
{
    AVLTree *avl = new AVLTree;
    srand(time(NULL));
    for(int i = 0; i < 10;i++)
        avl->add(i);
    print(avl->getBegin());
    avl->remove(3);
    cout << "#########################"<<endl;
    print(avl->getBegin());
    return 0;
}
