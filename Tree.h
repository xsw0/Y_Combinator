//
// Created by 0x0 on 4/8/21.
//

#ifndef TREE__TREE_H_
#define TREE__TREE_H_

typedef int TREE_VALUE_TYPE;

typedef struct Tree Tree;
Tree *Tree_Construct();
void Tree_Destruct(Tree *tree);
Tree *Tree_getLeft(Tree *tree);
Tree *Tree_getRight(Tree *tree);
void Tree_setLeft(Tree *tree, Tree *left);
void Tree_setRight(Tree *tree, Tree *right);
void Tree_setValue(Tree *tree, TREE_VALUE_TYPE value);
TREE_VALUE_TYPE Tree_getValue(Tree *tree);

#endif //TREE__TREE_H_
