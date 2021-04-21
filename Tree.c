//
// Created by 0x0 on 4/8/21.
//

#include "Tree.h"

#include <stdlib.h>
#include <assert.h>

struct Tree
{
    TREE_VALUE_TYPE value;
    Tree *left;
    Tree *right;
};

Tree *Tree_Construct()
{
    Tree *tree = (Tree *)malloc(sizeof(Tree));
    tree->left = NULL;
    tree->right = NULL;
    return tree;
}

void Tree_Destruct(Tree *tree)
{
    assert(tree);
    if (tree->left) Tree_Destruct(tree->left);
    if (tree->right) Tree_Destruct(tree->right);
    free(tree);
}

Tree *Tree_getLeft(Tree *tree)
{
    assert(tree);
    return tree->left;
}

Tree *Tree_getRight(Tree *tree)
{
    assert(tree);
    return tree->right;
}

void Tree_setLeft(Tree *tree, Tree *left)
{
    assert(tree);
    tree->left = left;
}

void Tree_setRight(Tree *tree, Tree *right)
{
    assert(tree);
    tree->right = right;
}

void Tree_setValue(Tree *tree, TREE_VALUE_TYPE value)
{
    assert(tree);
    tree->value = value;
}

TREE_VALUE_TYPE Tree_getValue(Tree *tree)
{
    assert(tree);
    return tree->value;
}
