#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Tree.h"

typedef struct Function Function;
typedef struct Lambda Lambda;

struct Function
{
    Lambda *closure;
    Lambda *(*function)(Lambda *, Lambda *);
};

struct Lambda
{
    enum
    {
        FUNCTION,
        VALUE
    } type;

    union
    {
        Function *function;
        void *value;
    } as;
};

#define IS_FUNCTION(lambda) ((lambda).type==FUNCTION)
#define IS_VALUE(lambda) ((lambda).type==VALUE)

#define AS_FUNCTION(lambda) ((lambda).as.function)
#define AS_VALUE(lambda) ((lambda).as.value)

Lambda *Lambda_function(Function *function)
{
    Lambda *lambda = (Lambda *)malloc(sizeof(Lambda));
    lambda->type = FUNCTION;
    lambda->as.function = function;
    return lambda;
}

Lambda *Lambda_value(void *value)
{
    Lambda *lambda = (Lambda *)malloc(sizeof(Lambda));
    lambda->type = VALUE;
    lambda->as.value = value;
    return lambda;
}

Lambda *call(Function *function, Lambda *args)
{
    return function->function(args, function->closure);
}

Lambda *Y(Function *function)
{
    Lambda *f = Lambda_function(function);
    AS_FUNCTION(*f)->closure = f;
    return f;
}

Lambda *Fact(Lambda *n, Lambda *self)
{
    assert(IS_VALUE(*n));
    assert(IS_FUNCTION(*self));
    int64_t v = (int64_t)AS_VALUE(*n);
    if (v == 0)
    {
        Lambda *result = Lambda_value((void *)1);
        return result;
    }
    else
    {
        Lambda *n_1 = call(AS_FUNCTION(*self), Lambda_value((void *)v - 1));
        Lambda *result = Lambda_value((void *)(v * (int64_t)AS_VALUE(*n_1)));
        free(n_1);
        return result;
    }
}

typedef struct TreeAndFun TreeAndFun;

struct TreeAndFun
{
    Tree *tree;
    void (*fun)(Tree *);
};

Lambda *PreOrderRecursionTraverse(Lambda *treeAndFun, Lambda *self)
{
    assert(IS_VALUE(*treeAndFun));
    assert(IS_FUNCTION(*self));

    TreeAndFun *taf = AS_VALUE(*treeAndFun);
    void (*fun)(Tree *) = taf->fun;
    Tree *tree = taf->tree;

    fun(tree);
    if (Tree_getLeft(tree))
    {
        TreeAndFun *new_taf = (TreeAndFun *)malloc(sizeof(TreeAndFun));
        new_taf->tree = Tree_getLeft(tree);
        new_taf->fun = fun;
        Lambda *new_lambda = Lambda_value(new_taf);
        call(AS_FUNCTION(*self), new_lambda);
        free(new_taf);
        free(new_lambda);
    }
    if (Tree_getRight(tree))
    {
        TreeAndFun *new_taf = (TreeAndFun *)malloc(sizeof(TreeAndFun));
        new_taf->tree = Tree_getRight(tree);
        new_taf->fun = fun;
        Lambda *new_lambda = Lambda_value(new_taf);
        call(AS_FUNCTION(*self), new_lambda);
        free(new_taf);
        free(new_lambda);
    }
    return NULL;
}

Lambda *InOrderRecursionTraverse(Lambda *treeAndFun, Lambda *self)
{
    assert(IS_VALUE(*treeAndFun));
    assert(IS_FUNCTION(*self));

    TreeAndFun *taf = AS_VALUE(*treeAndFun);
    void (*fun)(Tree *) = taf->fun;
    Tree *tree = taf->tree;

    if (Tree_getLeft(tree))
    {
        TreeAndFun *new_taf = (TreeAndFun *)malloc(sizeof(TreeAndFun));
        new_taf->tree = Tree_getLeft(tree);
        new_taf->fun = fun;
        Lambda *new_lambda = Lambda_value(new_taf);
        call(AS_FUNCTION(*self), new_lambda);
        free(new_taf);
        free(new_lambda);
    }
    fun(tree);
    if (Tree_getRight(tree))
    {
        TreeAndFun *new_taf = (TreeAndFun *)malloc(sizeof(TreeAndFun));
        new_taf->tree = Tree_getRight(tree);
        new_taf->fun = fun;
        Lambda *new_lambda = Lambda_value(new_taf);
        call(AS_FUNCTION(*self), new_lambda);
        free(new_taf);
        free(new_lambda);
    }
    return NULL;
}

Lambda *PostOrderRecursionTraverse(Lambda *treeAndFun, Lambda *self)
{
    assert(IS_VALUE(*treeAndFun));
    assert(IS_FUNCTION(*self));

    TreeAndFun *taf = AS_VALUE(*treeAndFun);
    void (*fun)(Tree *) = taf->fun;
    Tree *tree = taf->tree;

    if (Tree_getLeft(tree))
    {
        TreeAndFun *new_taf = (TreeAndFun *)malloc(sizeof(TreeAndFun));
        new_taf->tree = Tree_getLeft(tree);
        new_taf->fun = fun;
        Lambda *new_lambda = Lambda_value(new_taf);
        call(AS_FUNCTION(*self), new_lambda);
        free(new_taf);
        free(new_lambda);
    }
    if (Tree_getRight(tree))
    {
        TreeAndFun *new_taf = (TreeAndFun *)malloc(sizeof(TreeAndFun));
        new_taf->tree = Tree_getRight(tree);
        new_taf->fun = fun;
        Lambda *new_lambda = Lambda_value(new_taf);
        call(AS_FUNCTION(*self), new_lambda);
        free(new_taf);
        free(new_lambda);
    }
    fun(tree);
    return NULL;
}

void printNode(Tree *tree)
{
    printf("%d ", Tree_getValue(tree));
}

int main()
{
    Lambda *fact = Y(&(Function){ NULL, Fact });
    Lambda *result = call(AS_FUNCTION(*fact), Lambda_value((void *)5));
    printf("%lld\n", (int64_t)(AS_VALUE(*result)));

    int num = 19;
    Tree *tree[num];
    for (int i = 0; i < num; ++i)
    {
        tree[i] = Tree_Construct();
        Tree_setValue(tree[i], i);
    }
    Tree_setLeft(tree[0], tree[1]);
    Tree_setRight(tree[0], tree[2]);
    Tree_setLeft(tree[1], tree[3]);
    Tree_setRight(tree[1], tree[4]);
    Tree_setLeft(tree[2], tree[5]);
    Tree_setRight(tree[2], tree[6]);
    Tree_setLeft(tree[3], tree[7]);
    Tree_setRight(tree[3], tree[8]);
    Tree_setLeft(tree[4], tree[9]);
    Tree_setRight(tree[4], tree[10]);
    Tree_setLeft(tree[5], tree[11]);
    Tree_setRight(tree[5], tree[12]);
    Tree_setLeft(tree[6], tree[13]);
    Tree_setRight(tree[6], tree[14]);
    Tree_setLeft(tree[7], tree[15]);
    Tree_setRight(tree[7], tree[16]);
    Tree_setLeft(tree[8], tree[17]);
    Tree_setRight(tree[8], tree[18]);

    TreeAndFun *taf = malloc(sizeof(TreeAndFun));
    taf->fun = printNode;
    taf->tree = tree[0];

    Lambda *args = Lambda_value(taf);

    Lambda *preOrderRecursionTraverse = Y(&(Function){ NULL, PreOrderRecursionTraverse });
    Lambda *inOrderRecursionTraverse = Y(&(Function){ NULL, InOrderRecursionTraverse });
    Lambda *postOrderRecursionTraverse = Y(&(Function){ NULL, PostOrderRecursionTraverse });

    call(AS_FUNCTION(*preOrderRecursionTraverse), args);
    printf("\n");
    call(AS_FUNCTION(*inOrderRecursionTraverse), args);
    printf("\n");
    call(AS_FUNCTION(*postOrderRecursionTraverse), args);
    printf("\n");

    return 0;
}
