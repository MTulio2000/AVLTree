#include "avl.h"

bool AVLTree::has(int v) const
{
    AVLNode *act = this->begin;
    int type,found = 0;
    while(act&&!found)
    {
        found = (act->value == v);
        type = act->value>v?1:0;
        act = act->subtree[type];
    }
    return found;    
}

Direction AVLTree::opposite(Direction dir)
{
    return dir==RIGHT?LEFT:RIGHT;
}

bool AVLTree::add(int v)
{
    bool add = true;
    AVLNode *newNode = new AVLNode();
    newNode->value = v;
    if(!this->begin)
        this->begin = newNode;
    else
    {
        Direction dir;
        AVLNode *act,*next = this->begin;
        do
        {
            act = next;
            add = !(act->value==v);
            dir = act->value<v?RIGHT:LEFT;
            next = act->subtree[dir];
        }while(next&&add);

        if(add)
        {
            act->subtree[dir] = newNode;
            newNode->father = act;
            balance(this->begin);
        }
    }
    return add;
}

void AVLTree::balance(AVLNode *node)
{
    if(node)
    {
        balance(node->subtree[RIGHT]);
        balance(node->subtree[LEFT]);
        
        if(!node->subtree[RIGHT])
            node->levels[RIGHT] = 0;
        else
            node->levels[RIGHT] = max(node->subtree[RIGHT]->levels[RIGHT],node->subtree[RIGHT]->levels[LEFT])+1;
        if(!node->subtree[LEFT])
            node->levels[LEFT] = 0;
        else
            node->levels[LEFT] = max(node->subtree[LEFT]->levels[RIGHT],node->subtree[LEFT]->levels[LEFT])+1;

        node->level = max(node->levels[LEFT],node->levels[RIGHT]);
        node->q = node->levels[RIGHT]-node->levels[LEFT];

        if(pow(node->q,2)>1)
        {
            rotation(node);
            balance(node);
        }
    }
}

void AVLTree::rotation(AVLNode *node)
{
    Direction dir = node->q>0?RIGHT:LEFT;
    Direction opposite = node->subtree[dir]->q>0?RIGHT:LEFT;
    if(dir==opposite)
        simpleRotation(node,dir);
    else
        doubleRotation(node,dir);
}

void AVLTree::simpleRotation(AVLNode *node,Direction dir)
{
    Direction opposite = this->opposite(dir);
    AVLNode *father = node->father,*child = node->subtree[dir];
    node->subtree[dir] = child->subtree[opposite];
    if(node->subtree[dir])
        node->subtree[dir]->father = node;
    child->subtree[opposite] = node;
    child->father = father;
    node->father = child;
    if(father)
        father->subtree[father->value<child->value?RIGHT:LEFT] = child;
    else
        this->begin = child;
}

void AVLTree::doubleRotation(AVLNode *node,Direction dir)
{
    Direction opposite = this->opposite(dir);
    AVLNode * child = node->subtree[dir]->subtree[opposite];
    simpleRotation(node->subtree[dir],opposite);
    node->subtree[dir] = child;
    simpleRotation(node,dir);
}

AVLNode* AVLTree::getBegin() const
{
    return this->begin;
}

void AVLTree::remove(int v)
{
    AVLNode *aux,*node = this->begin;
    Direction dir;
    while(node)
    {
        if(node->value==v)
        {
            if(node == begin)
                begin = node->subtree[RIGHT];
            if(node->father)
                node->father->subtree[dir] = node->subtree[RIGHT];
            aux = node->subtree[RIGHT];
            while(aux->subtree[LEFT])
                aux = aux->subtree[LEFT];
            aux->subtree[LEFT] = node->subtree[LEFT];
            node->subtree[LEFT]->father = aux;
            node->subtree[RIGHT]->father = node->father;
            cout << node->subtree[RIGHT]->value<<endl;
            aux = node->subtree[LEFT];
            while(aux->father)
            {
                aux = aux->father;
                balance(aux);
            }
            delete node;
            break;
        }
        dir = (node->value<v)?RIGHT:LEFT;
        node = node->subtree[dir];
    }
}
